@echo off
del /f /q %1.sql > nul
del /f /q %2 > nul
echo PRAGMA optimize(0xfffe); > %1.sql
sqlite3.exe %1 .dump >> %1.sql
sqlite3.exe %2 < %1.sql
del /f /q %1.sql > nul
del /f /q %1.sql > nul