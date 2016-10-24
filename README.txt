These need to be installed before you start.
============================================
Cmake
arduino sdk

Some values need to be set in the SourceMe before continuing
============================================================
PUTTY_DIR # This is the directory that the putty.exe file is in
          # This is only needed if you use the make monitor command
COM_PORT  # This is the port that arduino is connected to
          # This is only needed if you use the make upload command

Then run "source SourceMe"

In have included a makefile that will run the compilation and upload procedure.
===============================================================================
make clean # This will delete the previoius build directory
make build # This will build the current source code
make uplod # This will build if it hasn't yet, then upload to the arduino
make monitor # This will open a putty session to monitor the serial bus

