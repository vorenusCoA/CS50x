def main():

    # Ask the user for a credit card number to check
    creditCard = int(input("Number: "))

    if checkSumOK(creditCard):
        ccList = []

        while creditCard:
            ccList.append(creditCard % 10)
            creditCard = int(creditCard / 10)

        qDigits = len(ccList)
        # The first digit is the last element
        firstDigit = ccList[qDigits - 1]
        secondDigit = ccList[qDigits - 2]

        # Check for American Express (34 or 37)
        if qDigits == 15 and firstDigit == 3 and (secondDigit == 4 or secondDigit == 7):
            print("AMEX")

        # Check for Visa (4)
        elif firstDigit == 4 and (qDigits == 13 or qDigits == 16):
            print("VISA")

        # Check for Master Card (51, 52, 53, 54, or 55)
        elif qDigits == 16 and firstDigit == 5 and (secondDigit == 1 or secondDigit == 2 or secondDigit == 3 or secondDigit == 4
                                                    or secondDigit == 5):
            print("MASTERCARD")
        else:
            print("INVALID")

    else:
        print("INVALID")


def checkSumOK(creditCard):

    # We put each element in its corresponding array
    evenList = []
    oddList = []
    index = 0
    while creditCard:
        digit = creditCard % 10
        if index % 2 == 0:
            evenList.append(digit)
        else:
            oddList.append(digit)

        creditCard = int(creditCard / 10)
        index += 1

    # Multiply by 2 each element of the odd array
    for i in range(len(oddList)):
        oddList[i] *= 2

    # Sum the digits of all the elements in the odd array
    oddSum = 0
    for i in range(len(oddList)):
        # if the element has 2 digits we have to sum both
        if oddList[i] >= 10:
            oddSum += oddList[i] % 10  # second digit
            oddSum += 1  # first digit is alway 1
        else:
            oddSum += oddList[i]

    # Sum the digits of all the elements in the even array
    evenSum = 0
    for i in range(len(evenList)):
        evenSum += evenList[i]

    # Now we sum both totals and if the last digit is 0 we are OK
    total = oddSum + evenSum
    if total % 10 == 0:
        return True
    else:
        return False


# Execute the main function
main()