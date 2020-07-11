import sys
import csv

# Check numbers of arguments
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

# Read the database file
with open(sys.argv[1], newline='') as f:
    reader = csv.reader(f)
    database = list(reader)

# The sequences we will have to look for
patterns = []
for i in range(1, len(database[0])):
    patterns.append(database[0][i])

# Read the DNA sequence
with open(sys.argv[2]) as f:
    dnaSequence = f.read()

# Here we store the max numbers of each sequence
maxNumbersPatters = []

# For each pattern we have to look the max number of repetitions
for pattern in patterns:
    patternLength = len(pattern)
    qPattern = 0
    maxQPattern = 0
    previousPattern = ""
    index = 0
    while index < len(dnaSequence) - patternLength:
        piceOfDNA = dnaSequence[index: index + patternLength]
        if pattern == piceOfDNA:
            if qPattern == 0:
                previousPattern = piceOfDNA
            if previousPattern == piceOfDNA:
                qPattern += 1
                # Forward the cursor
                index += len(piceOfDNA)
                if maxQPattern < qPattern:
                    maxQPattern = qPattern
        else:
            qPattern = 0
            index += 1

    maxNumbersPatters.append(maxQPattern)

# Iterate rows (skip row 1 - "titles")
for i in range(1, len(database)):
    match = True
    # Iterate columns (skip column 1 - "names")
    for j in range(1, len(database[i])):
        if int(database[i][j]) != maxNumbersPatters[j - 1]:
            match = False
            break
    if match:
        print(database[i][0])
        sys.exit(0)

print("No match")