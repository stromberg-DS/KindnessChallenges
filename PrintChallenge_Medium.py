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
QUOTES = 0
EASY = 1
MEDIUM = 2
HARD = 3

##############
#Change this to adjust what difficulty level you want
DIFFICULTY_LEVEL = MEDIUM
##############

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
###For DS PC
# pathName = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\"
###
pathName = "C:\\Users\\Visitors\\OneDrive\\KindnessChallenges\\"
quotePath = pathName + "Quotes\\"
easyPath = pathName + "Challenges\\1_Easy\\"
medPath = pathName + "Challenges\\2_Medium\\"
hardPath = pathName + "Challenges\\3_Hard\\"
currentPath = [quotePath, easyPath, medPath, hardPath]

quoteList = os.listdir(quotePath)
easyList = os.listdir(easyPath)
medList = os.listdir(medPath)
hardList = os.listdir(hardPath)
currentList = [quoteList, easyList, medList, hardList]

print(len(quoteList), " Quotes")
print(quoteList)
print()
print(len(easyList), " Easy")
print(easyList)
print()
print(len(medList), " Medium")
print(medList)
print()
print(len(hardList), " Hard")
print(hardList)

textTypeFolder = ["Challenges\\", "Quotes\\"]
difficultyFolder = ["1_Easy\\", "2_Medium\\", "3_Hard\\"]
numFilesInFolder = [11, 12, 6]

os.startfile(pathName + "Challenges\\StartupPrint.txt", "print")

while True:
    input("Press enter")
    currentTime = time.time()

    if (time.time() - lastFocusTime) > 2:
        print("Focus Time!")
        lastFocusTime = time.time()
    
    rndMax = random.randrange(0, len(currentList[DIFFICULTY_LEVEL]))
    filename = currentList[DIFFICULTY_LEVEL][rndMax]
    print(currentPath[DIFFICULTY_LEVEL] + filename)
    os.startfile(currentPath[DIFFICULTY_LEVEL] + filename, "print")
  
