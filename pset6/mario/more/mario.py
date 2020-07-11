# Ask the user for a height between 1-8
while True:
    n = input("Height: ")
    try:
        n = int(n)
        if n >= 1 and n <= 8:
            break
    except:
        continue


# Print the piramids
for i in range(n):

    # Print the left spaces
    for j in range(n - 1 - i):
        print(" ", end="")

    # Print the left hashes
    for j in range(i + 1):
        print("#", end="")

    # Print the gap
    for j in range(2):
        print(" ", end="")

    # Print right hashes
    for j in range(i + 1):
        print("#", end="")

    # Change of line
    print()