@echo off
setlocal enabledelayedexpansion

rem Encuentra la ruta del directorio actual del script
set "SCRIPT_DIR=%~dp0"

rem Puedes definir una variable para el archivo ejecutable
set "PROGRAM_FILE=tu_programa.exe"

rem Ejecuta el programa desde el directorio del script
cd /d !SCRIPT_DIR!
!SCRIPT_DIR!!PROGRAM_FILE!

endlocal
