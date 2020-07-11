# Promp the user to enter the text to analize
text = input("Text: ")

# Count letters, words and sentences
# It is important to use float so we don´t loose info in the final division
qLetters = 0
qWords = 1  # Since we count spaces we have to add an extra 1 for the last word
qSentences = 0
textLength = len(text)
for i in range(textLength):
    # Letters
    if text[i].isalpha():
        qLetters += 1
    elif text[i] == " ":  # space (Words)
        qWords += 1
    elif text[i] == "!" or text[i] == "." or text[i] == "?":  # ! . ? (Sentences)
        qSentences += 1

# Calculate de grade with Coleman-Liau formula
grade = 0.0588 * (qLetters * 100 / qWords) - 0.296 * (qSentences * 100 / qWords) - 15.8

if round(grade) >= 16:
    print("Grade 16+")
elif round(grade) < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(round(grade)))
