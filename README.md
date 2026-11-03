# Qt Todo demo

[![CI](https://github.com/mateusz-fejcher7/qt-cicd-demo/actions/workflows/ci.yml/badge.svg)](https://github.com/mateusz-fejcher7/qt-cicd-demo/actions/workflows/ci.yml)

A small todo app built with Qt Quick (QML) and C++, using Qt 6.12.

## Build

```sh
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/path/to/Qt/6.12.0/<platform>
cmake --build build
```

Requires Qt 6.8 or newer (Qt 6.12 LTS recommended), CMake 3.21+ and Ninja.
