#!/usr/bin/env sh

input_dir=$(realpath -s "$1")
output_dir=$(realpath -s "$2")
jar_name=$3
build_dir="$input_dir/build"

javac_command="$JAVA_HOME/bin/javac"
jar_command="$JAVA_HOME/bin/jar"

cd "$input_dir" || exit 1

mkdir -p build
find ./build -name "*.class" -exec rm {} \;
"$javac_command" -d ./build ./*.java

cd "$output_dir" || exit 1
rm -f "$jar_name"
"$jar_command" cvf "$jar_name" -C "$build_dir" . || exit 1

#cp "$jar_name" ../../../java_test/