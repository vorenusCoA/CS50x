# Ask the user for a positive price
while True:
    price = input("Change owed: ")
    try:
        price = float(price)
        if price >= 0:
            break
    except:
        continue

# Converting dollars into cents
cents = int(price * 100)

# Coins used
qCoins = 0
while cents > 0:
    if cents >= 25:
        cents = cents - 25
    elif cents >= 10:
        cents = cents - 10
    elif cents >= 5:
        cents = cents - 5
    else:
        cents -= 1

    qCoins += 1

print(str(qCoins))
