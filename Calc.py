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
    for i in range(1, len(terms) - 1):
        new = checkOp(terms[i], terms[i-1], terms[i+1])
        
    return new

def multipleOps(terms):
    new = None  # Initialize new to None
    for i in range(1, len(terms) - 1):
        result = checkOp(terms[i], terms[i-1], terms[i+1])
        if result is not None:
            if new is None:
                new = str(result)  # Convert result to string
            else:
                new = str(new)  # Convert new to string
                new = checkOp(terms[i], new, terms[i+1])  # Chain operations
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
    xLeft = False
    if("x" in leftTerms):
        xLeft = True
        leftOpCount -= 1
    else:
        xLeft = False
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

print(solve("x + 5 + 2 + 31 - 2 = 2 * 5"))