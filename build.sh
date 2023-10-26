#! /usr/bin/bash

# executable name
output="Piton"

# Specify the source and include directories
src_dir="src"
include_dir="include"

# Create a build directory if it doesnt exist
build_dir="build"
mkdir -p "$build_dir"

# Source files and object files
source_files="$src_dir/*.c"
object_files=""
for file in $source_files;
do
    o_file="$build_dir/$(basename "$file" .c).o"
    object_files="$object_files $o_file"
done

# Compiler and flags
cc="gcc"
cflags="-Wall -Wextra -I$include_dir -c"

# Compile source files and object files
for file in $source_files;
do
    o_file="$build_dir/$(basename "$file" .c).o"
    $cc $cflags $file -o $o_file
done

# Link object files to create the final executable
$cc $object_files -o "$output"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
fi
