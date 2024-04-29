#Functions for all operations
def add(x, y):
    return x + y
def sub(x, y):
    return x - y
def mul(x, y):
    return x * y
def div(x, y):
    return x / y


def checkOp(op, last, next):
    if "x" not in last and "x" not in next:
        if op == "+":
            return add(int(last), int(next))
        elif op == "-":
            return sub(int(last), int(next))
        elif op == "*":
            return mul(int(last), int(next))
        elif op == "/":
            return div(int(last), int(next))
        
def oneOp(terms):
    for i in range(len(terms)):
        try:
            new = checkOp(terms[i], terms[i-1], terms[i+1])
            if "x" in terms[i]:
                if terms[i] == "x":
                    print("Just x")
                elif "x" in terms[i]:
                    print("x is " + terms[i])
        except Exception as e:
            print(e)
            
    return new

def multipleOps(terms):
    new = None
    print(terms)
    for i in range(len(terms)):
        try:
            result = checkOp(terms[i], terms[i-1], terms[i+1])
            if result is not None:
                if new is None:
                    new = str(result)
                else:
                    new = str(new)
                    new = checkOp(terms[i], new, terms[i+1])
                    
            if "x" in terms[i]:
                if terms[i] == "x":
                    print("Just x")
                else:
                    print("x is " + terms[i])
        except Exception as e:
            print(e)
    return new

def solve(equation):
    leftSide, rightSide = equation.split("=")
    # Split left side into its components
    leftTerms = leftSide.split()
    rightTerms = rightSide.split()
    print(leftTerms)
    print(rightTerms)
    leftOpCount = sum(1 for term in leftTerms if term in ['+', '-', '*', '/'])
    rightOpCount = sum(1 for term in rightTerms if term in ['+', '-', '*', '/'])
    
    #Finding if x is in left or right side
    xLeft = any("x" in term for term in leftTerms)
    if xLeft:
        leftOpCount -= 1
    else:
        rightOpCount -= 1
        
    if(leftOpCount <= 1):
        left = oneOp(leftTerms)
    else:
        left = multipleOps(leftTerms)
        
    if(rightOpCount <= 1):
        right = oneOp(rightTerms)
    else:
        right = multipleOps(rightTerms)
        
    if(xLeft):
        #Left side has x
        if left < 0:
            right = right + left
        else :
            right = right - left
        
        left = 0
    else:
        #Right side has x
        if right < 0:
            left = left + right
        else :
            left = left - right
            
        right = 0
        
    end = add (left, right)
    return "x = " + str(end)

print(solve("3x + 5 + 2 + 31 - 2 = 2 * 5"))