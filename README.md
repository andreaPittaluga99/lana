# lana
Lana is a linear algebra library I built to better understand the theory I'm studying in uni.

You can find the course syllabus [here](https://corsi.unige.it/off.f/2026/ins/93652).

## Build

Requires C++20 and CMake. To build it, just run:

```sh
cmake -S . -B build
cmake --build build
```

## Tests

I'm using GoogleTest (CMake fetches it automatically). Run them with:

```sh
ctest --test-dir build --output-on-failure
```
