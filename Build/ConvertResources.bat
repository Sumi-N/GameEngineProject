call SetEnvironment.bat

"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe" ..\Tool\GeometryBuilder\GeometryBuilder.vcxproj -property:Configuration=Release;Platform=x64
"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe" ..\Tool\ShaderBuilder\ShaderBuilder.vcxproj -property:Configuration=Release;Platform=x64
"C:\Program Files\Microsoft Visual Studio\2022\Community\Msbuild\Current\Bin\MSBuild.exe" ..\Tool\TextureBuilder\TextureBuilder.vcxproj -property:Configuration=Release;Platform=x64

%OUTPUT_DIRECTORY_RELEASE%\GeometryBuilder\GeometryBuilder.exe
%OUTPUT_DIRECTORY_RELEASE%\ShaderBuilder\ShaderBuilder.exe
%OUTPUT_DIRECTORY_RELEASE%\TextureBuilder\TextureBuilder.exe