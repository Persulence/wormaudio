#!/usr/bin/env sh

input_dir=$(realpath -s "$1")
output_dir=$(realpath -s "$2")
jar_name=$3
build_dir="$input_dir/build"

cd "$input_dir" || exit

mkdir -p build

javac -d ./build ./*.java

cd "$output_dir" || exit
rm -f "$jar_name"
jar cvf "$jar_name" -C "$build_dir" .

#cp "$jar_name" ../../../java_test/