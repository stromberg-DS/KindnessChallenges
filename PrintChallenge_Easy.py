#Could make this work more seemlessly using the os library to
#   find the files, count them, etc to make the program more flexible.
#   More info here: https://realpython.com/working-with-files-in-python/


import threading
import os
from os import system
import random
import pygetwindow as gw
import time
import pyautogui as pag

timeToPrint = False
QUOTES = 0
EASY = 1
MEDIUM = 2
HARD = 3

##############
#Change this to adjust what difficulty level you want
DIFFICULTY_LEVEL = EASY
##############

# Wait for Enter key press
def waitForInput():
    global timeToPrint
    while True:
        input("Press Enter")
        timeToPrint = True
        print("Sending to Printer!")

# Reset computer focus to python window
def resetWindowFocus():
    while True:
        time.sleep(5)
        python_window = gw.getWindowsWithTitle(WINDOW_NAME)[0]
        if python_window.isActive == False:
            python_window.minimize()
            python_window.restore()
            print("Refocused the python window at:", time.strftime("%H:%M:%S"))


        
        
# Send random file to the printer
def printChallenge():
    global timeToPrint
    while True:
        if timeToPrint:
            rndMax = random.randrange(0, len(currentList[DIFFICULTY_LEVEL]))
            filename = currentList[DIFFICULTY_LEVEL][rndMax]
            print(currentPath[DIFFICULTY_LEVEL] + filename)
            # os.startfile(currentPath[DIFFICULTY_LEVEL] + filename, "print")
            timeToPrint = False




#Name the window for reference later
WINDOW_NAME = "Random Acts of Kindness"
system("title " + WINDOW_NAME)    

# All of these paths go to a OneDrive folder that I have set up
#     This way, I can easily update the challenges remotely and
#     all of the computers will pull from the updated folder.
#     NOTE: Make sure to swap all single backslashes (\)
#     for double backslashes (\\). Make sure you have two tacked
#     onto the end  ("...Challenges\\")

###For DS PC
pathName = "C:\\Users\\dstromberg\\OneDrive\\KindnessChallenges\\"
###

# pathName = "C:\\Users\\Visitors\\OneDrive\\KindnessChallenges\\"
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

# os.startfile(pathName + "Challenges\\StartupPrint.txt", "print")

# Start Threading
input_thread = threading.Thread(target=waitForInput)
focus_thread = threading.Thread(target=resetWindowFocus)
print_thread = threading.Thread(target=printChallenge)

input_thread.start()
focus_thread.start()
print_thread.start()

# Join threads
input_thread.join()
focus_thread.join()
print_thread.join()

    

  
