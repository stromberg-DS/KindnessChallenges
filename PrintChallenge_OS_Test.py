#Could make this work more seemlessly using the os library to
#   find the files, count them, etc to make the program more flexible.
#   More info here: https://realpython.com/working-with-files-in-python/


import threading
import os
from os import system
import random
import pygetwindow as gw
import time

timeToPrint = False

def waitForInput():
    input("Press Enter")
    print("Sending to Printer!")
    timeToPrint = True
    
#Name the window for reference later
system("title " + "Random Acts of Kindness")    

lastFocusTime = time.time()
print(time.time())

# All of these paths go to a OneDrive folder that I have set up
#     This way, I can easily update the challenges remotely and
#     all of the computers will pull from the updated folder.
#     NOTE: Make sure to swap all single backslashes (\)
#     for double backslashes (\\). Make sure you have two tacked
#     onto the end  ("...Challenges\\")
pathName = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\Challenges\\"
easyPath = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\Challenges\\1_Easy"
medPath = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\Challenges\\2_Medium"
hardPath = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\Challenges\\3_Hard"
quotePath = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\Quotes"


textTypeFolder = ["Challenges\\", "Quotes\\"]
difficultyFolder = ["1_Easy\\", "2_Medium\\", "3_Hard\\"]
numFilesInFolder = [11, 12, 6]

os.startfile(pathName + "StartupPrint.txt", "print")

while True:
    input("Press enter")
    currentTime = time.time()

    if (time.time() - lastFocusTime) > 2:
        print("Focus Time!")
        lastFocusTime = time.time()
    

    difficulty = random.randint(0,2)
    filename = random.randint(1, numFilesInFolder[difficulty])

    print(difficulty)
    print(filename)

    os.startfile(pathName + difficultyFolder[difficulty] + str(filename) + ".txt", "print")    
