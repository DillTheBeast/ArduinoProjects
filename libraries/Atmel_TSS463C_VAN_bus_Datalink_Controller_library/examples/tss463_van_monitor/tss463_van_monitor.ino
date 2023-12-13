#include <SPI.h>
#include <itss46x.h>
#include <tss46x_van.h>

#include <tss463.h>
#include <tss461_intel.h>
#include <tss46x_with_serial.h>

uint8_t VAN_PIN = 7;

TSSPinSetup* pinSetup;

SPIClass* spi;
ITss46x* vanSender;
TSS46X_VAN* VANInterface;

uint8_t vanMessageLength;
uint8_t vanMessage[32];

uint8_t headerByte = 0x80;
uint8_t check = 0x00;

char incomingByte;

void InitTss461()
{
     // instantiate the VAN message sender for a TSS461
    pinSetup = new TSSPinSetup();

    #ifdef ARDUINO_ARCH_STM32
    pinSetup->TSS_ALE_PIN   = PB13;
    pinSetup->TSS_WRITE_PIN = PB15;
    pinSetup->TSS_CS_PIN    = PB12;
    pinSetup->TSS_READ_PIN  = PA8;
    pinSetup->TSS_RESET_PIN = PB14;

    pinSetup->TSS_AD0_PIN   = PA0;
    pinSetup->TSS_AD1_PIN   = PA1;
    pinSetup->TSS_AD2_PIN   = PA2;
    pinSetup->TSS_AD3_PIN   = PA3;
    pinSetup->TSS_AD4_PIN   = PA4;
    pinSetup->TSS_AD5_PIN   = PA5;
    pinSetup->TSS_AD6_PIN   = PA6;
    pinSetup->TSS_AD7_PIN   = PA7;
    #endif
    vanSender = new Tss461Intel(pinSetup);
}

void InitTss463()
{
      // initialize SPI
    spi = new SPIClass();

    #ifdef ARDUINO_ARCH_AVR
        // start spi on Arduino boards
        spi->begin();
    #endif

    #ifdef ARDUINO_ARCH_ESP32
        // You can select which pins to use as SPI on ESP32 boards by passing the SCK, MISO, MOSI, SS as arguments (in this order) to the spi->begin() method
        const uint8_t SCK_PIN = 25;
        const uint8_t MISO_PIN = 5;
        const uint8_t MOSI_PIN = 33;
        VAN_PIN = 32;

        spi->begin(SCK_PIN, MISO_PIN, MOSI_PIN, VAN_PIN);
    #endif

    // instantiate the VAN message sender for a TSS463
    vanSender = new Tss463(VAN_PIN, spi);
}

void InitTssSerial()
{
    // This "VAN message sender" just prints the values of the TSS registers to the Serial port, included as an example for an abstract sender
    vanSender = new Tss46xWithSerial(Serial);
}

void setup()
{
    Serial.begin(500000);
    delay(3000);
    Serial.println("Arduino VAN bus monitor using TSS463C");

    InitTss463();
    //InitTss461();
    //InitTssSerial();

    VANInterface = new TSS46X_VAN(vanSender, VAN_125KBPS);
    VANInterface->begin();

    // IMPORTANT - it does matter in which order the channels are set up for the various request types
    // This is because how priority among different channels is taken into consideration (see Page 46 in documentation for further info)

    // if you would like to try out VAN reading then enable the following channel setups
    //van_setup_channel(0); //#1 reply request message
    van_setup_channel(1); //#2 receive message
    //van_setup_channel(2); //#3 reply request without transmission message
    //van_setup_channel(3); //#4 deferred reply request detection message
}

void van_setup_channel(int channel)
{
    switch (channel)
    {
        case 0:
            VANInterface->set_channel_for_reply_request_message_without_transmission(channel, 0x00, 30);
            break;
        case 1:
            VANInterface->set_channel_for_receive_message(channel, 0x00, 30, 0);
            break;
        case 2:
            VANInterface->set_channel_for_reply_request_message_without_transmission(channel, 0x00, 30);
            break;
        case 3:
            VANInterface->set_channel_for_reply_request_detection_message(channel, 0x00, 30);
            break;
        default:
            break;
    }
}

void ShowPopupMessage(int messageId)
{
    uint8_t packet[16] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, messageId, 0xFF, 0xFF, 0xFF, 0xFF,0xFF,0xFF };
    VANInterface->set_channel_for_transmit_message(4, 0x524, packet, 16, 0);
}

void SendExternalTemperature(int temperature)
{
    uint8_t packet[7] = { 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, temperature * 2  + 0x50};
    VANInterface->set_channel_for_transmit_message(5, 0x8A4, packet, 7, 0);
}

/*
    The message id 0x564 is asked by the multifunction display. If we remove the display the message dissappears.
    With the help of method we can query the info from the BSI without having the display in the car.
    We need to ask periodically.
*/
void QueryCarStatusWithTripInfo()
{
    VANInterface->set_channel_for_reply_request_message(7, 0x564, 29, 1);
}

/*
    The display asks for the presence of the CD changer.
    With the help of this method we can fool the display that there is a CD changer installed.
    We need to set this periodically.
*/
void AnswerToCDC()
{
    headerByte = (headerByte == 0x87) ? 0x80 : headerByte + 1;

    uint8_t status = 0xC3; //playing
    uint8_t cartridge = 0x16;
    uint8_t minutes = 0x01;
    uint8_t seconds = 0x56;
    uint8_t trackNo = 0x17;
    uint8_t cdNo = 0x02;
    uint8_t trackCount = 0x21;

    uint8_t packet[12] = { headerByte, 0x00, status, cartridge, minutes, seconds, trackNo, cdNo, trackCount, 0x3f, 0x01, headerByte };
    VANInterface->set_channel_for_immediate_reply_message(8, 0x4EC, packet, 12);
}

void TripButtonPressed()
{
    uint8_t packetTrip[2] = { 0x12, 0x08 };
    VANInterface->set_channel_for_transmit_message(3, 0x8C4, packetTrip, 2, 1);
    //0E 8C 4C 12 08 45 72
}

void AnswerToTripData(uint8_t tripButton)
{
    headerByte = (headerByte == 0x87) ? 0x80 : headerByte + 1;

    uint8_t packet[27] = { headerByte, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, tripButton, 0x00, 0x36, 0x06, 0x00, 0x00, 0xFF, 0xFF, 0x0D, 0x29, 0x00, 0x40, 0xFF, 0xFF, 0xFF, 0xFF, headerByte };
    VANInterface->set_channel_for_immediate_reply_message(8, 0x564, packet, 27);
}

void loop() {

    if (Serial.available()>0)
    {
        int inChar = Serial.read();
        switch (inChar)
        {
            case 'd': {
                // note that the display remembers which message was shown last
                // so if you send the same messageId multiple times, it will be displayed only for the first time
                Serial.println("Send 09");
                ShowPopupMessage(0x09);
                break;
            }
            case 'f': {
                Serial.println("Send 18");
                ShowPopupMessage(0x18);
                break;
            }
            case 'e': {
                Serial.println("Send 15");
                ShowPopupMessage(0x15);
                break;
            }
            case 't': {
                Serial.println("Send temp");
                SendExternalTemperature(10);
                break;
            }
            case 'p': {
                Serial.println("Read");
                VANInterface->read_message(1, &vanMessageLength, vanMessage);

                char tmp[3];

                for (size_t i = 0; i < vanMessageLength; i++)
                {
                    snprintf(tmp, 3, "%02X", vanMessage[i]);
                    Serial.print(" ");
                    Serial.print(tmp);
                }
                Serial.println();
                VANInterface->reactivate_channel(1);
                break;
            }
            case 'q': {
                QueryCarStatusWithTripInfo();
                break;
            }
            case 'a': {
                AnswerToCDC();
                break;
            }
            case 'r': {
                TripButtonPressed();
                AnswerToTripData(0x51);
                delay(20);

                TripButtonPressed();
                AnswerToTripData(0x50);
                break;
            }
            default:
                break;
        }
    }

    //if you would like to try out VAN reading then enable the following loop

    //
    /*
    for (uint8_t channel = 0; channel < 4; channel++)
    {
        MessageLengthAndStatusRegister messageAvailable = VANInterface->message_available(channel);
        if (messageAvailable.data.CHRx || messageAvailable.data.CHTx) //|| messageAvailable.data.CHER)
        {
            VANInterface->read_message(channel, &vanMessageLength, vanMessage);

            if (vanMessage[0] == 0x00)
            {
                continue;
            }

            Serial.print("Channel: ");
            Serial.print(channel, DEC);
            Serial.print(": ");

            char tmp[3];

            for (size_t i = 0; i < vanMessageLength; i++)
            {
                snprintf(tmp, 3, "%02X", vanMessage[i]);
                Serial.print(" ");
                Serial.print(tmp);
            }
            Serial.println();

            VANInterface->reactivate_channel(channel);
        }
    }
    //*/
}
