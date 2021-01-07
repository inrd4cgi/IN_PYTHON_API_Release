@echo off

SET CURR_DIR=%~dp0
set INAP_ROOT=%CURR_DIR%\..\..

"%INAP_ROOT%\env\win64\python2.7\python.exe" %INAP_ROOT%\src\setup\stop_all_services.py
