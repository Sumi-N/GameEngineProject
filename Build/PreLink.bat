set EXTERNAL_DIRECTORY=%~dp0..\External

if not exist "%EXTERNAL_DIRECTORY%\glfw\build\" (
    cmake -G "Visual Studio 17 2022" -A x64 -S %EXTERNAL_DIRECTORY%\glfw -B %EXTERNAL_DIRECTORY%\glfw\build\
)

if not exist "%EXTERNAL_DIRECTORY%\glfw\build\src\Release\" (
    cmake --build %EXTERNAL_DIRECTORY%\glfw\build --config Release
) 

if not exist "%EXTERNAL_DIRECTORY%\External\yaml-cpp\build\" (
    cmake -G "Visual Studio 17 2022" -A x64 -S %EXTERNAL_DIRECTORY%\yaml-cpp\ -B %EXTERNAL_DIRECTORY%\yaml-cpp\build
)

if not exist "%EXTERNAL_DIRECTORY%\External\yaml-cpp\build\Debug\" (
    cmake --build %EXTERNAL_DIRECTORY%\yaml-cpp\build --config Debug
)

if not exist "%EXTERNAL_DIRECTORY%\External\yaml-cpp\build\Release\" (
    cmake --build %EXTERNAL_DIRECTORY%\yaml-cpp\build --config Release
)