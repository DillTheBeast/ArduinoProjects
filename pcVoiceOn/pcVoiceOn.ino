/**
  ******************************************************************************
  * @file    vr_sample_control_led.ino
  * @author  JiapengLi
  * @brief   This file provides a demostration on 
              how to control led by using VoiceRecognitionModule
  ******************************************************************************
  * @note:
        voice control led
  ******************************************************************************
  * @section  HISTORY
    
    2013/06/13    Initial version.
  */
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <Servo.h>

/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/

VR myVR(2, 3);

uint8_t records[7];
uint8_t buf[64];

int servoPin = 13; // Change the name of the pin variable
Servo servo;       // Use Servo type for the servo motor

#define onRecord (0)
#define offRecord (1)
#define callRecord (2)

#define IDLE_STATE 0
#define WAIT_FOR_JARVIS_STATE 1
#define WAIT_FOR_ACTION_STATE 2

int currentState = IDLE_STATE;
unsigned long jarvisTime = 0;
bool jarvisSaid = false;

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
  pinMode(servoPin, OUTPUT); // Use the servoPin for pin initialization
  servo.attach(servoPin);    // Attach the servo motor to the correct pin
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)onRecord) >= 0){
    Serial.println("onRecord loaded");
  }
  
  if(myVR.load((uint8_t)offRecord) >= 0){
    Serial.println("offRecord loaded");
  }

  if(myVR.load((uint8_t)callRecord) >= 0){
    Serial.println("caseRecord loaded");
  }
}

void loop()
{
  int ret;

  switch (currentState)
  {
  case IDLE_STATE:
    ret = myVR.recognize(buf, 50);
    if (ret > 0)
    {
      if (buf[1] == callRecord)
      {
        currentState = WAIT_FOR_JARVIS_STATE;
        jarvisTime = millis();
        jarvisSaid = false;
      }
      printVR(buf);
    }
    break;

  case WAIT_FOR_JARVIS_STATE:
    // Wait for "Jarvis"
    if (millis() - jarvisTime >= 3000)
    {
      currentState = IDLE_STATE;
    }

    ret = myVR.recognize(buf, 50);
    if (ret > 0)
    {
      if (buf[1] == onRecord && !jarvisSaid)
      {
        //Move servo to turn on
        servo.write(120);
        delay(1000);
        servo.write(0);
        currentState = IDLE_STATE;
        jarvisSaid = true;
      }
      printVR(buf);
    }
    break;
  }
}