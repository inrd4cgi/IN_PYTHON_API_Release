@echo off

rem if "h" == "h" goto begin
rem mshta vbscript:createobject("wscript.shell").run("""%~nx0"" h",0)(window.close)&&exit
rem :begin

set PATH=
set PYTHONPATH=
set PATH=D:\DEV\Github\IN_PYTHON_API\env\win64\python3.7\Lib\site-packages\PySide2;%PATH%
set PATH=D:\DEV\Github\IN_PYTHON_API\env\win64\python3.7\..\..\..\lib\python3_win64;%PATH%
set PYTHONPATH=D:\DEV\Github\IN_PYTHON_API\env\win64\python3.7\Lib\site-packages;%PYTHONPATH%
set PYTHONPATH=D:\DEV\Github\IN_PYTHON_API\src;%PYTHONPATH%
set PYTHONPATH=D:\DEV\Github\IN_PYTHON_API\env\win64\python3.7\Lib;%PYTHONPATH%


call D:\DEV\Github\IN_PYTHON_API\env\win64\python3.7\python.exe -c "exec(\"import IN_RUN_SERVER\nIN_RUN_SERVER.run_server()\")" %*

