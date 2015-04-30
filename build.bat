@echo off

set IncludeFlags=-I C:\Qt5.4.1\5.4\msvc2013_64\include\ -I C:\Qt5.4.1\5.4\msvc2013_64\include\QtWidgets\ -I C:\Qt5.4.1\5.4\msvc2013_64\include\QtCore\

set LinkerFlags=C:\Qt5.4.1\5.4\msvc2013_64\lib\Qt5Widgets.lib C:\Qt5.4.1\5.4\msvc2013_64\lib\Qt5Core.lib

cl %IncludeFlags% qtodo.cpp %LinkerFlags%


qtodo.exe
