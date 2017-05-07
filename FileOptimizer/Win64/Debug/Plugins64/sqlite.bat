@echo off
del %1.sql > nul
del %2 > nul
sqlite3.exe %1 .dump > %1.sql
sqlite3.exe %2 < %1.sql
del %1.sql > nul
rem sqlite3.exe %2 "PRAGMA optimize(0xfffe); VACUUM;"
del %1.sql > nul