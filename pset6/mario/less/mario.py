# Ask the user for a height between 1-8
while True:
    n = input("Height: ")
    try:
        n = int(n)
        if n >= 1 and n <= 8:
            break
    except:
        continue

# Print the piramid
for i in range(n):

    for j in range(n - 1 - i):
        print(" ", end="")

    for j in range(i + 1):
        print("#", end="")

    # Change of line
    print()
