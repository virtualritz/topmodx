rem run in the cmd prompt or powershell by typing .\makeall-win32.bat
@echo on
cd include
qmake
mingw32-make
cd ..
qmake
lupdate topmod.pro
lrelease topmod.pro
mingw32-make