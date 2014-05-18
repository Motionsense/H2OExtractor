# Microsoft Developer Studio Project File - Name="H2OExtractor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=H2OExtractor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "H2OExtractor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "H2OExtractor.mak" CFG="H2OExtractor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "H2OExtractor - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "H2OExtractor - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "H2OExtractor - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386

!ELSEIF  "$(CFG)" == "H2OExtractor - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /debug /machine:I386

!ENDIF 

# Begin Target

# Name "H2OExtractor - Win32 Release"
# Name "H2OExtractor - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\version.rc
# End Source File
# End Group
# Begin Group "H2O"

# PROP Default_Filter ""
# Begin Group "header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Archive.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveComment.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveCompressedFileData.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveCompressedStringChunk.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveCompressedStringDesc.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveDirectoryNameChunk.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveDirectoryNameDesc.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveFile.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveFileNameChunk.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveFileNameDesc.h
# End Source File
# Begin Source File

SOURCE=.\Source\ArchiveHeader.h
# End Source File
# End Group
# Begin Group "source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Archive.cpp
# End Source File
# End Group
# End Group
# Begin Group "Main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\H2OExtractor.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\H2OExtractor.h
# End Source File
# Begin Source File

SOURCE=.\Source\predefine.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Group "Blast"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Utils\Blast\blast.c
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\Blast\blast.h
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\Blast\blastHandler.c
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\Blast\blastHandler.h
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\Blast\crc32.c
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\Blast\crc32.h
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\Blast\README.md
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\Blast\types.h
# End Source File
# End Group
# Begin Group "dirent"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Utils\dirent\ChangeLog
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\dirent\dirent.h
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\dirent\README.md
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\Utils\DebugUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\DebugUtils.h
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\FileUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\FileUtils.h
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\GeneralUtils.hpp
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\StringUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Utils\StringUtils.h
# End Source File
# Begin Source File

SOURCE=.\Source\Types.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\README.md
# End Source File
# End Target
# End Project
