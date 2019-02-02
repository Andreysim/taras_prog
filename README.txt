Windows build:
	1. Install Qt with components:
		- Qt/Qt x.x.x/MinGW y.y.y
		- Qt/Tools/MinGW y.y.y
	2. Open mingw_build.bat with text editor and replace QTDIR and MINGW_BIN_DIR variables with your paths.
	   Also you can change installation diriectory if you change INSTALL_DIR variable (by default 'Program').
	3. Run mingw_build.bat
	
To build from QtCreator:
	- open .pro file
	- in project build options uncheck 'shadow build'
	- switch to relese configuration
	- run build (on success executable is placed in 'bin' diriectory)