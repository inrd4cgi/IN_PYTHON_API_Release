@echo off

call %~dp0\..\..\bin\windows_x64\protoc.exe -I=%~dp0\..\proto --python_out=%~dp0\..\dist\python %~dp0\..\proto\IN.proto
