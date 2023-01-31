Data-Collection-Kit README and Guide
------------------------------------------
To use the data collection kit, it must first be run in Administrator mode 
so that the forensic tools have the adequate permissions to be run.
This can be done by 
    right-clicking Data-Collection-Kit.bat
    clicking "Run as Administrator"
    enter the Administrator password, or choose yes to run as Administrator

Once the program has started, you should be greeted with a simple menu 
displaying the current program status and options for running the collection kit.
It should look like this:

====================STATUS=====================
OS Architecture is 64 bit
RAM Collection will be run in the Collection Kit
Artifact Triage Collection will be run in the Collection Kit
RAM Collection Output Path: C:\Users\lolip\Desktop\DataCollectionKit\DESKTOP-E5CUI82\ram\RAMCollection.raw
Triage Collection Output Path: C:\Users\lolip\Desktop\DataCollectionKit\DESKTOP-E5CUI82\triage\triageCollection.zip
====================OPTIONS====================
1. RAM Dump Options
2. Artifact Triage Options
3. Change OS Architecture
4. Run Collection Kit
5. Exit Without Running
===============================================
Enter Number to Select Option:

The OS Architecture is detected by the program when it is run, however it can be changed,
if needed, by inputting 3 into the prompt and hitting enter.
By default, the program will create folders to output its collection data to
the same directory the script is being run from.
This can be changed by going into the options for each tool.

To run the program, ensure that all tools have been configured to your desired settings.
Inputting 4 and hitting enter will run the chosen tools with their configured settings.
Once this is done, the data collection kit window will freeze after some brief output and
a window for each tool will pop up and run.

Inutting 5 at the menu and hitting enter will close the program without running any tools
or creating any folders.


Inputting 1 and hitting enter will take you to the options for the RAM Dump tool.
The menu displayed will look like this:

====================STATUS=====================
RAM Collection will be run in the Collection Kit
Output Directory: C:\Users\lolip\Desktop\DataCollectionKit\DESKTOP-E5CUI82\ram\
Output Filename: RAMCollection.raw
====================OPTIONS====================
1. Enable/Disable ram Collection in Collection Kit
2. Change Output Path
3. Change Output Filename
4. Return to Menu
===============================================
Enter Number to Select Option:

Here the options for configuring this tool are available. 
Inputting 1 and hitting enter will turn the tool on or off depending on its current status.
This will be reflected in the status section of the menu.
Inputting 2 and hitting enter will allow the file path of the tool output to be reconfigured.
The output path will always be proceeded by folders named after the hostname of the computer 
and ram to signify the computer and tool used. 
Inputting 3 and hitting enter will allow the filename for the collection output to be reconfigured.
The file extension is not enforced on this input. The default extension is .raw, omitting this will
create the same output without a file extension.
Finally, inputting 4 and hitting enter will bring you back to the main program menu.

Once back at the main program menu, inputting 2 and hitting enter will take you to the 
triage collection tool configuration menu. The menu and its options are identical to the
RAM collection tool configuration menu. It looks like this:

====================STATUS=====================
Triage Collection will be run in the Collection Kit
Output Directory: C:\Users\lolip\Desktop\DataCollectionKit\DESKTOP-E5CUI82\triage\
Output Filename: triageCollection.zip
====================OPTIONS====================
1. Enable/Disable Triage Collection in Collection Kit
2. Change Output Path
3. Change Output Filename
4. Return to Menu
===============================================
Enter Number to Select Option:

Here the options for configuring this tool are available. 
Inputting 1 and hitting enter will turn the tool on or off depending on its current status.
This will be reflected in the status section of the menu.
Inputting 2 and hitting enter will allow the file path of the tool output to be reconfigured.
The output path will always be proceeded by folders named after the hostname of the computer 
and triage to signify the computer and tool used. 
Inputting 3 and hitting enter will allow the filename for the collection output to be reconfigured.
The file extension is not enforced on this input. The default extension is .raw, omitting this will
create the same output without a file extension.
Finally, inputting 4 and hitting enter will bring you back to the main program menu.