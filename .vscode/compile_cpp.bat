set FileName=%1
if not exist .build_cpp (
    mkdir .build_cpp
    cd .build_cpp
    cmake -G "MinGW Makefiles" ..
) else (
    cd .build_cpp
)

make bot_ui
start cmd /k "bot_ui & echo. & pause & exit"
