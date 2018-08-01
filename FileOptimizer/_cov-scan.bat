del /f /s /q cov-int
cov-analysis-win64-2017.07\bin\cov-build --dir cov-int msbuild FileOptimizer.cbproj /t:build /p:Config=Debug /p:Platform=Win32 > _cov-scan.log
"\Archivos de programa\7-Zip\7z.exe" a -mm=Deflate -mx=9 -mfb=258 -mpass=15 -mmt=off -tzip cov-int\cov-int.zip -r cov-int\
\curl.exe --insecure --form token=y9TeJb2O4tn2Cf4DB-j3Nw --form email=nikkho@gmail.com --form file=@cov-int\cov-int.zip --form version="13.10" --form description="" https://scan.coverity.com/builds?project=Nikkhonikkho