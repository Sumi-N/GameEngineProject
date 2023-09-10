call SetEnvironment.bat

"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe" ..\MyGame\CustomGame.vcxproj -property:Configuration=Release;Platform=x64

%OUTPUT_DIRECTORY_RELEASE%\CustomGame.exe