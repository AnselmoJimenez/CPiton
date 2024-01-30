#! /usr/bin/bash

# executable name
output="Piton"

# Create a build directory if it doesnt exist
build_dir="build"
mkdir -p "$build_dir"

# Source files and object files
source_files="src/*.c"
include_files="include/*.h"

# Compiler and flags
cc="gcc"
cflags="-Wall -Wextra"

echo "Compiling source files"
object_files=""
for file in $(basename -s .c $source_files);
do
    # Logging
    echo "  $cc -c src/$file.c -o $build_dir/$file.o -Iinclude"

    $cc -c src/$file.c -o $build_dir/$file.o -Iinclude
    object_files="$object_files $build_dir/$file.o"
done

# Link all object files
echo "Linking object files"
echo "  $cc $object_files -o $output"
$cc $object_files -o $output

if [ $? -eq 0 ]; 
then
    echo "COMPILATION SUCCESSFUL"
else
    echo "COMPILATION FAILED"
fi