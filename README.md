# POK Lab 01 — C++ string library

- **Team:** Sviatoslav Mandzyuk
- **Variant:** 1 (the sole variant for Task 1: string library)
- **Additional tasks:** additional operators; complete C API binding.

## Implemented

`my_str_t` is a manually managed dynamic string that keeps the invariant
`data_m[size_m] == '\0'`, while `capacity_m` excludes the terminating null byte.
The implementation uses `new[]`/`delete[]`; it does not use `malloc`, `realloc`,
`strlen`, or standard-library string manipulation routines in the library.

The first two additional tasks are included:

1. Move construction/assignment, `+`, `+=`, `*`, and `*=`. Repetition reserves
   the final capacity once before copying.
2. A C-compatible, opaque-handle binding in `mystring_c.h` / `mystring_c.cpp`.
   It maps C++ exceptions to `my_str_status` values and never lets an exception
   cross the C ABI boundary.

Implementation files identify their author where required by the assignment: **Sviatoslav Mandzyuk**.

## Build and test

Requirements: CMake 3.16+, a C++20 compiler, and a C compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/c_api_demo
```

`tests.cpp` exercises the C++ API and the C binding. `c_api_demo.c` verifies
that the public C header is accepted by a C compiler and demonstrates its use.

## LMS submission text

```text
Здав роботу на GitHub: https://github.com/mandziuk911/pok-lab01-strings
Склад команди: Sviatoslav Mandzyuk
Варіант: 1 (єдиний варіант для Завдання 1)
Додаткові завдання: реалізувати додаткові оператори; створити C API binding для цієї бібліотеки.
```
