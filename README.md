# clic

Clic or Command Line Interface Calculator, is a tool for doing calculations with large numbers.

Our goal is to create an interpreted programming language that doesn't have limitations on number size. This can be useful for writing quick scripts that work on problems in number theory, astronomy, cryptography, statistics or any practical purpose you can find for dealing with large numbers.

# installation

You will need:

git

cmake

g++

Build Instructions:

(skip first step if given a tar.gz)

    git clone https://github.com/wetbadger/clic.git
    
    cd clic
    mkdir build
    cd build
    cmake ..
    cmake --build .
    make
    
run with:
    
    ./clic
    
