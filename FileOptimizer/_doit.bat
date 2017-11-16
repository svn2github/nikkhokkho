rem \ficheros\util\upx -9 --best --lzma --overlay=strip --ultra-brute Win32\Release\FileOptimizer.exe
del *.zip
del *.7z
del *.7z.exe
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
cd Win32\Release\Plugins32\
..\..\..\_Tools\PatchPE64.exe "\Archivos de programa\Borland\NSIS\MakeNSIS.exe"
..\..\..\_Tools\PatchPE64.exe "\Archivos de programa\Borland\NSIS\Bin\makensis.exe"
..\..\..\_Tools\PatchPE64.exe guetzli.exe
..\..\..\_Tools\PatchPE64.exe mutool.exe
..\..\..\_Tools\PatchPE64.exe mozjpegtran.exe
cd ..\..\..\
cd Win32\Release\Plugins64\
..\..\..\_Tools\PatchPE64.exe guetzli.exe
..\..\..\_Tools\PatchPE64.exe mutool.exe
..\..\..\_Tools\PatchPE64.exe mozjpegtran.exe
cd ..\..\..\
Win64\Release\FileOptimizer .\Win32\Release
Win32\Debug\Plugins32\petrim /stripfixups:Y .\Win32\Release\*.exe /r
Win32\Debug\Plugins32\petrim .\Win32\Release\*.* /r
"\Archivos de programa\7-Zip\7z" a -t7z -mx=9 -mfb=273 -mmt=off -myx9 -m0=lzma2:d512m:fb273 FileOptimizerSource.7z *.cbproj *.bat *.txt *.chm *.mes *.res *.ico *.cpp *.h Source\*.* Source\gifsicle\*.* Source\gifsicle\src\*.* Source\gifsicle\include\*.* Source\gifsicle\include\lcdf\*.* Source\gifsicle\include\lcdfgif\*.* Source\jpegoptim\*.* Source\jpegoptim\libjpeg\*.* Source\jpegoptim\win32\*.* Source\jsmin\*.* Source\mp4v2\*.* Source\mp4v2\include\*.* Source\mp4v2\libplatform\*.* Source\mp4v2\libutil\*.* Source\mp4v2\src\*.* Source\mp4v2\util\*.* Source\mp4v2\vstudio10.0\*.* Source\sqlite\*.* Resource\*.* Resource\Icon\*.* Help\*.* Help\Images\*.* Setup\*.*
cd Win32\Release
rem "\Archivos de programa\7-Zip\7z" a -mm=Deflate -mx=9 -mfb=258 -mpass=15 -mmt=off -tzip ..\..\FileOptimizerFull.zip FileOptimizer32.exe FileOptimizer64.exe FileOptimizer.chm Plugins32\*.* Plugins64\*.*
\FICHEROS\UTIL\UPX -9 --best --lzma --ultra-brute --crp-ms=999999 "\Archivos de programa\7-Zip\*.sfx"
"\Archivos de programa\7-Zip\7z" a -t7z -mx=9 -mfb=273 -mmt=off -myx9 -m0=lzma2:d512m:fb273 -sfx7z.sfx ..\..\FileOptimizerFull.7z.exe FileOptimizer32.exe FileOptimizer64.exe FileOptimizer.chm Plugins32\*.* Plugins64\*.*
cd ..\..\Setup
"\Archivos de programa\Borland\NSIS\MakeNSIS.exe" FileOptimizerSetup.nsi
cd ..
Win64\Release\FileOptimizer .\FileOptimizerFull.7z.exe
Win64\Release\FileOptimizer .\FileOptimizerSource.7z
:end