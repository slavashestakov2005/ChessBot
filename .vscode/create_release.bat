if exist .build_cpp_release (
    rmdir /s /q .build_cpp_release
)
mkdir .build_cpp_release
cd .build_cpp_release
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make bot_ui

cd ..
if exist .release (
    rmdir /s /q .release
)
mkdir .release
copy .build_cpp_release\bot_ui.exe .release\chessbot.exe
rmdir /s /q .build_cpp_release
set DLLPath=C:\\Users\Public\C++Dlls
copy "%DLLPath%\libgcc_s_seh-1.dll" .release\libgcc_s_seh-1.dll
copy "%DLLPath%\libstdc++-6.dll" ".release\libstdc++-6.dll"
copy "%DLLPath%\libwinpthread-1.dll" ".release\libwinpthread-1.dll"
copy "%DLLPath%\openal32.dll" .release\openal32.dll
copy "%DLLPath%\sfml-audio-2.dll" .release\sfml-audio-2.dll
copy "%DLLPath%\sfml-graphics-2.dll" .release\sfml-graphics-2.dll
copy "%DLLPath%\sfml-system-2.dll" .release\sfml-system-2.dll
copy "%DLLPath%\sfml-window-2.dll" .release\sfml-window-2.dll
xcopy /E data .release\data\

cd .release
zip -r archive.zip *
cd ..
