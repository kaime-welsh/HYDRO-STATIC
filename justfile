configure:
    cmake -B build -S .

build:
    cmake --build build

run: build
    ./build/HYDRO-STATIC
