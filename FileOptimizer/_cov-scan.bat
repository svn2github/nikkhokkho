cov-analysis-win64-2017.07\bin\cov-build --dir cov-int msbuild FileOptimizer.cbproj /t:build /p:Config=Debug > _cov-scan.log

rem <a href="https://scan.coverity.com/projects/nikkhonikkho"><img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/15215/badge.svg"/></a>