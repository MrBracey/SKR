# Microsoft Developer Studio Project File - Name="scarabeo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=scarabeo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "scarabeo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "scarabeo.mak" CFG="scarabeo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "scarabeo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "scarabeo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "scarabeo - Win32 inglese_R" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "scarabeo - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "ITALIA" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_ITALIA" /d "_SET2"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib /nologo /subsystem:windows /map /machine:I386 /out:"Release/scarabit.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=copy                       .\italia\*.bmp                       .\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "scarabeo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "ITALIA" /FR /Fp"Debug/serial.pch" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_ITALIA" /d "_SET2"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=copy                       .\italia\*.bmp                       .\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "scarabeo - Win32 inglese_R"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "scarabeo___Win32_inglese_R"
# PROP BASE Intermediate_Dir "scarabeo___Win32_inglese_R"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "scarabeo___Win32_inglese_R"
# PROP Intermediate_Dir "scarabeo___Win32_inglese_R"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_IRISH" /d "_SET2"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/scarabit.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/scaraben.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=copy                       .\world\*.bmp                       .\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "scarabeo - Win32 Release"
# Name "scarabeo - Win32 Debug"
# Name "scarabeo - Win32 inglese_R"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\errori.cpp
# End Source File
# Begin Source File

SOURCE=.\grafica.cpp
# End Source File
# Begin Source File

SOURCE=.\inits.cpp
# End Source File
# Begin Source File

SOURCE=.\LemmiMachine.cpp
# End Source File
# Begin Source File

SOURCE=.\procedure.cpp
# End Source File
# Begin Source File

SOURCE=.\scarabeo.cpp
# End Source File
# Begin Source File

SOURCE=.\supercomputer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\scarabeo.h
# End Source File
# Begin Source File

SOURCE=.\supercomputer.h
# End Source File
# Begin Source File

SOURCE=.\tessing.h
# End Source File
# Begin Source File

SOURCE=.\tessita.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cifre\app1.ico
# End Source File
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bitmap15.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00023.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00023_B.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00024.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00024_B.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00025.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00026.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00026_B.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00027.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00027_B.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00028.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00029.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp0025_B.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\computer.bmp
# End Source File
# Begin Source File

SOURCE=.\firma.bmp
# End Source File
# Begin Source File

SOURCE=.\firmata.bmp
# End Source File
# Begin Source File

SOURCE=.\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\cifre\man.bmp
# End Source File
# Begin Source File

SOURCE=.\cifre\scarabeo.bmp
# End Source File
# Begin Source File

SOURCE=.\scarabeo.rc
# End Source File
# Begin Source File

SOURCE=.\scarabeo.voc.it
# End Source File
# Begin Source File

SOURCE=.\scrabble.bmp
# End Source File
# Begin Source File

SOURCE=.\scrabblebasta.bmp
# End Source File
# Begin Source File

SOURCE=.\scrabblebello.bmp
# End Source File
# Begin Source File

SOURCE=.\scrabblebn.bmp
# End Source File
# Begin Source File

SOURCE=.\scrabblelum.bmp
# End Source File
# Begin Source File

SOURCE=.\scrabblenuovo.bmp
# End Source File
# Begin Source File

SOURCE=.\scrabbleombra.bmp
# End Source File
# Begin Source File

SOURCE=.\scrabblepassaggio.bmp
# End Source File
# Begin Source File

SOURCE=.\standard.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\appo.txt
# End Source File
# Begin Source File

SOURCE=.\errori.asp
# End Source File
# Begin Source File

SOURCE=".\FREQUENZE INGLESI.TXT"
# End Source File
# Begin Source File

SOURCE=".\FREQUENZE ITALIA.TXT"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
