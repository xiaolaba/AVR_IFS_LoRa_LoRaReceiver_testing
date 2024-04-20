 
@echo off 
set path=
 
set MCU=ATmega328PB
set ac=C:\avr8-gnu-toolchain-win32_x86
 
path %ac%\bin;%ac%\utils\bin;%path%;
 
avr-gcc.exe -dumpversion
 
:::: avrdude terminal only
avrdude -c usbtiny -p %MCU% -t
 
pause
:end
