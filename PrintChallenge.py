#Could make this work more seemlessly using the os library to
#   find the files, count them, etc to make the program more flexible.
#   More info here: https://realpython.com/working-with-files-in-python/


import threading
import os
from os import system
import random
import pygetwindow as gw
import time

system("title " + "Random Acts of Kindness")

lastFocusTime = time.time()
print(time.time())

#Update the path below so it goes to the real location of your
#   challenges folder. Make sure to swap all single backslashes (\)
#   for double backslashes (\\). Make sure you have two tacked
#   onto the end  ("...Challenges\\")
pathName = "C:\\Users\\Visitors\\OneDrive\\KindnessChallenges\\Challenges\\"

# Use below for DS laptop
##pathName = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\Challenges\\"

textTypeFolder = ["Challenges\\", "Quotes\\"]
difficultyFolder = ["1_Easy\\", "2_Medium\\", "3_Hard\\"]
numFilesInFolder = [11, 12, 6]

os.startfile(pathName + "StartupPrint.txt", "print")

while True:
    input("Press enter")
    currentTime = time.time()

##    if (time.time() - lastFocusTime) > 2:
##        print("Focus Time!")
##        lastFocusTime = time.time()
##    

    difficulty = random.randint(0,2)
    filename = random.randint(1, numFilesInFolder[difficulty])

    print(difficulty)
    print(filename)

    os.startfile(pathName + difficultyFolder[difficulty] + str(filename) + ".txt", "print")    
