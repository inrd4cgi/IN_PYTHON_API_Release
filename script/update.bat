@echo off

cd "%~dp0.."
git stash
git clean -fd
git pull origin master
git stash pop
pause
