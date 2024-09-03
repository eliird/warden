:: Create a build directory
mkdir build
cd build

:: Run CMake to generate build files
cmake ../

:: Build the project using the default generator
cmake --build . --config Release

:: Move the compiled executable (warden.exe) to the parent directory
move Release\warden.exe ../

:: Go back to the parent directory
cd ..
