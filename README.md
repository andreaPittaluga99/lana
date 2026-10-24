# lana
Lana is a linear algebra library I'm building to better understand the theory I'm studying in uni.

You can find the course syllabus [here](https://corsi.unige.it/off.f/2026/ins/93652).
I'm primarily following the lecture notes, but I'm also using this [book](https://mml-book.github.io/book/mml-book.pdf) as a recommended supplementary resource.

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
