# Random Acts of Kindness Generators
###### Developed by Daniel Stromberg for Explora's "Science of Kindness" exhibition, 2024
![Three different difficulty of Kind Act Generators](https://github.com/stromberg-DS/KindnessChallenges/blob/master/Graphics/RndActGens.JPEG)

## General Info
The Random Acts of Kindness Generators are three separate stations that provide visitors with a kind act for them to do. When visitors hold down the button, the path on the front of the generator slowly lights up. After the light gets to the end, the generator prints out a reciept with a kind act for the person to accomplish. After they have completed their task—or at least hopefully comitted to it—visitors use their finger to poke the receipt into the grid of holes on the wall. The grid is a record of all of the kind acts people have committed to. There are three separate generators set to three different difficulty levels: easy, medium, difficult. The list of kind acts was crowd sourced throughout all of Explora's staff along with the difficulty levels.

## Parts of the exhibit

### [Mini PC](https://www.amazon.com/gp/product/B0CL6B13QD/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)
A mini windows PC is mounted inside the generator cabinet. It runs python code to wait for a button press and print a random challenge 

### [Receipt Printer](https://www.amazon.com/Koncept-TM-T88V-Interfaces-Universal-Microfiber/dp/B0CLS9VHM2/ref=sr_1_1_sspa?crid=1K0WYS5S1CMJQ&dib=eyJ2IjoiMSJ9.gDELpm9SOKbOuFCkR4FHhotAlWmNDOj1BsFV3DE5Tq2QZZvg-u5bV9oQSGHZVyoq3qcDtjDeejJElge2W5S_DO3kSB_DbZ4UmbKI8O_KLy9IyJmwQlQalUkWPidN15bYMG2K8RFfAYK778K0bD8xNLGPLRI3tX9NhGaJzsd4xotI_JizgncwBDjns64jDgJ9NrcCmTcI0WBj-Ls0aigzvpL977Nw0zXf0JYw12zda88.M8xUR9U69abk6ttpETuuGNvyxxvu8LikDN9Ux606cxc&dib_tag=se&keywords=tm-t88v&qid=1718749629&sprefix=%2Caps%2C163&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1)
This is an Epson TM-T88V POS reciept printer. The benefit of this printer is it will cut the reciept after printing. Much better than relying on visitors to tear off their own reciepts.

### Microcontroller
The microcontroller detects the button press and lights up the "neon" LED strip. After the strip has lit up most of the way, it simulates a "return" keypress into the computer. In our case, I decided to use a Particle Photon 2, but an Arduino Pro Micro would also be a good choice. The Arduino Pro Micro is a good choice since it can simulate a keyboard and/or mouse.

### "Neon" LED strips
We used a 6mm x 12mm "neon" LED strip inlayed into the wood for the light up path. The strips from Amazon were a hair too short for the paths, so we ordered [Mini 5mm led strips](https://www.superlightingled.com/mini-5mm-ws2812-smd-2020-rgb-led-addressable-strip-light-1-meter-p-6049.html) and [neon diffusers](https://www.superlightingled.com/slender-silicone-light-diffuser-for-8mm-led-strips-0612mm-120-side-emitting-p-3549.html) to make our own length of strips.

## Setup
### Installing Printer Drivers
1. Go to the [epson driver page](https://epson.com/Support/Point-of-Sale/Thermal-Printers/Epson-TM-T88V-Series/s/SPT_C31CA85011?review-filter=Windows+10+64-bit) for the TM-T88V
2. Download "Advanced Printer Driver v5.13+" and unzip it.
3. Follow the instructions in the PDF. Start with the printer off/unplugged.
4. Turn on the printer and see if it connects.
5. Go to Start>Epson Advanced Printer Driver 5>Epson APD5 Utility for TM-T88V
6. Change an printer settings there/add any logos. Below only needs to be done once per printer:
   * Add Explora BW Bar logo (Explora, X Studio, Brillante)
   * Change print density to 130%
   * Change the print speed to level 8
   * Pick which logo prints (under "Automatic Paper Cut" settings)
8. Go to printers and open printer properties. Under "General," go to preferences. Under "Feed and Cut" add 0.5 inch to the end of the document.
9. Make the printer print upside-down. I don't remember where this is exactly. It is in one of the printer preferences boxes and I will update this later.

### Printing from Python
  * [Install Python](https://www.python.org/downloads/)
  * Open "PrintChallenge.py" in a text editor or in IDLE editor.
  * Go to *pathName* and update the path with the real location of your "Challenges" folder.
  * Replace all backslashes(\) with double backslashes (\\). "\u" is an escape character or something, so things like "\User" make it mad.
  * Make sure there are double backslashes on the end ("...Challenges\\")
  * Very basic printing from Python looks like this:
    * import os
    * os.startfile("C:\\Users\\BobSmith\\TestPrint.txt", "print")

### Keeping Python window in focus
  * Install pygetwindow - in command line, type "pip install pygetwindow"
  * In the python code, it will refocus the window by minimizing it and unminimizing it if it is out of focus.

### Getting Python code to run on startup
[Taken from here - a couple answers down](https://stackoverflow.com/questions/4438020/how-to-start-a-python-file-while-windows-starts)
  * Type **Win+R**
  * Type **shell:startup**
  * Copy your Python file into the startup directory
  * Make sure to copy the correct file for the PC you are using (easy, medium, difficult)
  * It should run the next time it starts up

### Windows auto login without password
  * Go to **Start>Run**
  * Type **Regedit.exe**, press enter
  * Go to **HKEY_LOCALMACHINE\SOFTWARE\Microsoft\WindowsNT\CurrentVersion\Winlogon** subkey in the registry
  * Go to **Edit>New>String Value**, type in **AutoAdminLogon** (this may already exist)
  * in the **Edit String** dialog box, type **1** and hit **OK**
  * Double click **DefaultUserName** (or make a new **String Value**), then typ in the username to login with and press OK. For our PCs, "Visitors" is the login we will use.
***
  * Next 2 only necessary if you require a password to login.
    * Create a new **String Value** (like above) with the name **DefaultPassword** and press OK.
    * Double click **DefaultPassword**, in **Edit String**, type in the password. Press OK.
***
  * Close Registry Editor and restart the computer. It should auto login now.
  * **Note:** I created a non-admin account on the PCs that do not require a password to login.

### Onedrive setup on PCs
  * The three PCs are all signed into the same microsoft account.
  * The different difficulties of challenges are stored in 3 folders in OneDrive.
  * This allows each computer to pull from the same set of challenges, and allows changes to be made easily to any challenges.

### Remote acces to PCs
  * All PCs have [Rust Desk](https://rustdesk.com/) installed on them.
  * This way, we can remotely sign into the computers without needing to open up each cabinet.

### Other
  * It is probably helpful to turn off as many notifications as possible. The Python code does refocus the window occasionally, but it's a bit nicer if it doesn't have to.
