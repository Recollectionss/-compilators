#!/bin/bash
set -e

echo "Starting build..."

# Go to the project folder
cd /project/dragon-tiger

cat > fibonacci.tig <<EOF
let
  function fibonacci(n : int) : int =
    if n < 3 then 1
    else fibonacci(n - 1) + fibonacci(n - 2)
in
  for i := 1 to 8 do
    (print_int(fibonacci(i)); print("\n"))
end
EOF


echo "Running compiler..."

# Compile the Tiger file to an object file
src/driver/dtiger -o fibonacci.o fibonacci.tig

echo "Linking..."

clang++ fibonacci.o src/runtime/posix/libruntime.a -o fibonacci -no-pie

echo "Running compiled program:"

# Run the compiled program
./fibonacci
