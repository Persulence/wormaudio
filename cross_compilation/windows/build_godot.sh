BIN=/opt/msvc/bin/x64 source ./msvcenv-native.sh
cmake --build build --target build_godot
cmake --install build
