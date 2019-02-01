@echo OFF

setlocal
setlocal EnableDelayedExpansion

:: Replace with your Qt and mingw paths
set "QTDIR=D:\Programs\Qt\5.12.0\mingw73_64"
set "MINGW_BIN_DIR=D:\Programs\Qt\Tools\mingw730_64\bin"

:: Where to install
set "INSTALL_DIR=Program"

set "PATH=%PATH%;%QTDIR%\bin;%MINGW_BIN_DIR%"

if exist "%INSTALL_DIR%" (
	rmdir /S /Q "%INSTALL_DIR%"
)

call :check_for_commands qmake mingw32-make

if %errorlevel% neq 0 (
	goto:error
)

if exist Makefile (
	mingw32-make distclean
)

:: Prepare Makefile
qmake TarasProg.pro -spec win32-g++

if %errorlevel% neq 0 (
	echo Failed to qmake project
	goto:error
)

:: Compile and link
mingw32-make

if %errorlevel% neq 0 (
	echo Failed to build program
	goto:error
)

:: Install prog and all needed files
mkdir "%INSTALL_DIR%" && copy bin\taras_program.exe "%INSTALL_DIR%" && windeployqt --no-translations --release "%INSTALL_DIR%\taras_program.exe"

if %errorlevel% neq 0 (
	echo Failed to deploy program
	goto:error
)

goto:eof

:check_for_commands
for %%G in ( %* ) do (
	where /Q %%G
	if !errorlevel! neq 0 (
		echo %%G command not found
		goto:error
	)
)

goto:eof

:error
exit /B 1

:eof
exit /B 0
