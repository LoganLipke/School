@echo off
setlocal enabledelayedexpansion

reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set OS=32 || set OS=64

set /A ramCollect=1
set ramFilePath=%~dp0%ComputerName%\ram\
set ramFile=RAMCollection.raw

set /A triageCollect=1
set triageFilePath=%~dp0%ComputerName%\triage\
set triageFile=triageCollection.zip

:runMenu
cls
echo ====================STATUS=====================
echo OS Architecture is %OS% bit
if %ramCollect% == 1 (
    echo RAM Collection will be run in the Collection Kit 
) else (
    echo RAM Collection will not be run in the Collection Kit
)
if %triageCollect% == 1 (
    echo Artifact Triage Collection will be run in the Collection Kit 
) else (
    echo Artifact Triage Collection will not be run in the Collection Kit
)
echo RAM Collection Output Path: %ramFilePath%%ramFile%
echo Triage Collection Output Path: %triageFilePath%%triageFile%
echo ====================OPTIONS====================
echo 1. RAM Dump Options
echo 2. Artifact Triage Options
echo 3. Change OS Architecture
echo 4. Run Collection Kit
echo 5. Exit Without Running
echo ===============================================

set /p option=Enter Number to Select Option: 

if %option%==1 ( goto :RAM )
if %option%==2 ( goto :Triage )
if %option%==3 ( 
    if %OS%==32 set OS=64
    if %OS%==64 set OS=32
)
if %option%==4 ( goto :Run )
if %option%==5 ( exit)

goto :runMenu

@REM: RAM CONFIGURATION MENU ===============================================================
:RAM
cls
echo ====================STATUS=====================
if %ramCollect% == 1 (
    echo RAM Collection will be run in the Collection Kit 
) else (
    echo RAM Collection will not be run in the Collection Kit
)
echo Output Directory: %ramFilePath%
echo Output Filename: %ramFile%
echo ====================OPTIONS====================
echo 1. Enable/Disable ram Collection in Collection Kit
echo 2. Change Output Path
echo 3. Change Output Filename
echo 4. Return to Menu
echo ===============================================

set /p option=Enter Number to Select Option: 

if %option%==1 (
    if %ramCollect%==1 ( 
        set ramCollect=0
    ) else (
        set ramCollect=1
    )
)

if %option%==2 (
    set "newRamFilePath="
    set /p newRamFilePath=Enter new path for ram Collection output or blank for default: 
    if "!newRamFilePath!" == "" ( 
        set ramFilePath=%~dp0%ComputerName%\ram\
    ) else (
        set ramFilePath=!newRamFilePath!\%ComputerName%\ram\
    )
)

if %option%==3 (
    set "newRamFile="
    set /p newRamFile=Enter new path for ram Collection output or blank for default: 
    if "!newRamFile!" == "" ( 
        set ramFile=RAMCollection.raw
    ) else (
        set ramFile=!newRamFile!
    )
)

if %option%==4 ( goto :runMenu )

goto :RAM

@REM: TRIAGE CONFIGURATION MENU ===============================================================
:Triage
cls
echo ====================STATUS=====================
if %triageCollect% == 1 (
    echo Triage Collection will be run in the Collection Kit 
) else (
    echo Triage Collection will not be run in the Collection Kit
)
echo Output Directory: %triageFilePath%
echo Output Filename: %triageFile%
echo ====================OPTIONS====================
echo 1. Enable/Disable Triage Collection in Collection Kit
echo 2. Change Output Path
echo 3. Change Output Filename
echo 4. Return to Menu
echo ===============================================

set /p option=Enter Number to Select Option: 

if %option%==1 (
    if %triageCollect%==1 ( 
        set triageCollect=0
    ) else (
        set triageCollect=1
    )
)

if %option%==2 (
    set "newtriageFilePath="
    set /p newtriageFilePath=Enter new path for Triage Collection output or blank for default: 
    if "!newtriageFilePath!" == "" ( 
        set triageFilePath=%~dp0%ComputerName%\triage\
    ) else (
        set triageFilePath=!newtriageFilePath!\%ComputerName%\triage\
    )
)

if %option%==3 (
    set "newtriageFile="
    set /p newtriageFile=Enter new path for Triage Collection output or blank for default: 
    if "!newtriageFile!" == "" ( 
        set triageFile=triageCollection.zip
    ) else (
        set triageFile=!newtriageFile!
    )
)

if %option%==4 ( goto :runMenu )

goto :Triage

@REM: RUN COLLECTION KIT ===============================================================
:Run
cls
if %ramCollect%==1 (
    if %OS%==64 (
        set ramToolPath=%~dp0%Tools\WinPmem\winpmem_mini_x64_rc2.exe
    )
    if %OS%==32 (
        set ramToolPath=%~dp0%Tools\WinPmem\winpmem_mini_x86.exe
    )

    echo Checking for existing output folders...
    if exist %ramFilePath% (
        echo Folder found, starting collection...
    ) else (
        echo Folder not found, creating output folders...
        mkdir %ramFilePath%
    )

    set ramCommand=!ramToolPath! %ramFilePath%%ramFile%
    echo Dumping and collecting RAM Contents...
    echo !ramCommand!
    start "RAM Collection" !ramCommand!
)

if %triageCollect%==1 (
    if %OS%==64 (
        set triageToolPath=%~dp0%Tools\CyLR\CyLR_win-x64\CyLR.exe
    )
    if %OS%==32 (
        set triageToolPath=%~dp0%Tools\CyLR\CyLR_win-x86\CyLR.exe
    )

    
    echo Checking for existing output folders...
    if exist %triageFilePath% (
        echo Folder found, starting collection...
    ) else (
        echo Folder not found, creating output folders...
        mkdir %triageFilePath%
    )

    set triageCommand=!triageToolPath! -od %triageFilePath% -of %triageFile% -l %triageFilePath%CyLR.log -v
    echo Performing System Triage...
    echo !triageCommand!
    start "System Triage" !triageCommand!
)

pause
exit