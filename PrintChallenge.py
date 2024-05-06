#Could make this work more seemlessly using the os library to
#   find the files, count them, etc to make the program more flexible.
#   More info here: https://realpython.com/working-with-files-in-python/


import os
import random

while True:
    input("Press enter")
    textTypeFolder = ["Challenges\\", "Quotes\\"]
    difficultyFolder = ["1_Easy\\", "2_Medium\\", "3_Hard\\"]
    numFilesInFolder = [11, 12, 6]

    difficulty = random.randint(0,2)
    filename = random.randint(1, numFilesInFolder[difficulty])

    pathName = "C:\\Users\\dstromberg\\Documents\\Code\\SciKi\\KindnessChallenges\\Challenges\\"

    print(difficulty)
    print(filename)

    os.startfile(pathName + difficultyFolder[difficulty] + str(filename) + ".txt", "print")
    #o s.startfile(pathName + difficultyFolder[difficulty] + str(filename) + ".txt", "print")
    