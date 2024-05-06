import os
import random

difficultyFolder = ["1_Easy\\", "2_Medium\\", "3_Hard\\"]
numFilesInFolder = [11, 12, 6]

difficulty = random.randint(0,2)
filename = random.randint(1, numFilesInFolder[difficulty])

pathName = "C:\\Users\\dstromberg\\Documents\\Code\\SciKi\\KindnessChallenges\\Challenges\\"

print(difficulty)
print(filename)

os.startfile(pathName + difficultyFolder[difficulty] + str(filename) + ".txt", "print")
