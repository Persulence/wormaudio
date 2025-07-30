BIN=/opt/msvc/bin/x64 source ./msvcenv-native.sh

install_dir=$(realpath "./install")

cmake -G Ninja \
  -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DDISABLE_WARNINGS=ON \
  -DCMAKE_C_COMPILER=clang-cl \
  -DCMAKE_CXX_COMPILER=clang-cl \
  -DCMAKE_SYSTEM_NAME=Windows \
  --install-prefix "$install_dir" \
  ../..
