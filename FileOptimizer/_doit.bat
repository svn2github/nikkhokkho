rem \ficheros\util\upx -9 --best --lzma --overlay=strip --ultra-brute Win32\Release\FileOptimizer.exe
del *.zip
del *.7z
rem del FileOptimizerFull.7z.exe
del FileOptimizerSetup.exe
del Win32\Release\FileOptimizer32.exe
del Win32\Release\FileOptimizer64.exe
del Win32\Release\FileOptimizer.chm
del /f /s /q Win32\Release\Plugins32\*.*
del /f /s /q Win32\Release\Plugins64\*.*
del /f /s /q Win32\Release\*.ini
del /f /s /q Win32\Release\*.obj
del /f /s /q Win32\Release\*.#*
del /f /s /q Win32\Release\*.tds
copy Help\FileOptimizer.chm Win32\Release\FileOptimizer.chm
copy Win32\Release\FileOptimizer.exe Win32\Release\FileOptimizer32.exe
copy Win64\Release\FileOptimizer.exe Win32\Release\FileOptimizer64.exe
del /f /q Win32\Release\FileOptimizer.exe
xcopy /e /s Win32\Debug\Plugins32\*.* Win32\Release\Plugins32\*.*
xcopy /e /s Win64\Debug\Plugins64\*.* Win32\Release\Plugins64\*.*
Win64\Release\FileOptimizer .\Win32\Release
Win32\Debug\Plugins32\petrim /stripfixups:Y .\Win32\Release\*.exe /r
Win32\Debug\Plugins32\petrim .\Win32\Release\*.* /r
rem "%HOMEPATH%\Archivos de programa\7-Zip\7z" a -mm=Deflate -mx=9 -mfb=258 -mpass=15 -mmt=off -tzip FileOptimizerSource.zip *.cbproj *.bat *.txt *.chm *.mes *.res *.ico *.cpp *.h Source\*.* Source\gifsicle\*.* Source\jpegoptim\*.* Source\libjpeg\*.* Source\jpegoptim\win32\*.* Source\gifsicle\src\*.* Source\gifsicle\include\*.* Source\gifsicle\include\lcdf\*.* Source\gifsicle\include\lcdfgif\*.* Resource\*.* Help\*.* Help\Images\*.*
"%HOMEPATH%\Archivos de programa\7-Zip\7z" a -mx=9 -mfb=273 -mmt=off -myx9 FileOptimizerSource.7z *.cbproj *.bat *.txt *.chm *.mes *.res *.ico *.cpp *.h Source\*.* Source\gifsicle\*.* Source\jpegoptim\*.* Source\libjpeg\*.* Source\jpegoptim\win32\*.* Source\gifsicle\src\*.* Source\gifsicle\include\*.* Source\gifsicle\include\lcdf\*.* Source\gifsicle\include\lcdfgif\*.* Source\jsmin\*.* Resource\*.* Help\*.* Help\Images\*.* Setup\*.*
cd Win32\Release
"%HOMEPATH%\Archivos de programa\7-Zip\7z" a -mm=Deflate -mx=9 -mfb=258 -mpass=15 -mmt=off -tzip ..\..\FileOptimizerFull.zip FileOptimizer32.exe FileOptimizer64.exe FileOptimizer.chm Plugins32\*.* Plugins64\*.*
rem "%HOMEPATH%\Archivos de programa\7-Zip\7z" a -mx=9 -mfb=273 -mmt=off -sfx7z.sfx ..\..\FileOptimizerFull.7z.exe FileOptimizer32.exe FileOptimizer64.exe FileOptimizer.chm Plugins32\*.* Plugins64\*.*
cd ..\..\Setup
"%HOMEPATH%\Archivos de programa\Borland\NSIS\MakeNSIS.exe" FileOptimizerSetup.nsi
cd ..
Win32\Release\FileOptimizer32 .\FileOptimizerFull.zip
Win32\Release\FileOptimizer32 .\FileOptimizerSource.zip
:end