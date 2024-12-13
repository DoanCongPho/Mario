## mario

Install [MSYS2](https://www.msys2.org/), then install
dependencies in the MinGW64 environment:

```shell
pacman -S mingw-w64-x86_64-{cmake,libxml2,zlib,ninja} zlib-devel
```

Afterward, build the program:

```shell
mkdir build/
cd build/

cmake -G Ninja ..
ninja
```

The target program will be `mario.exe` in your build directory.