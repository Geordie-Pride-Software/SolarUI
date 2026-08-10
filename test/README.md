# SolarUI Test

`test.cpp` is a smoke test for SolarUI. It uses only `#include "SolarUI.h"`
(no internal headers) — the DLL exports everything it needs: every
element type (Button, Label, Slider, Checkbox) and the input feed
functions.

It opens a real window with a Button, Label, Slider, and Checkbox,
all wired up to real mouse/keyboard input.

## 1. Build the DLL

From the `SolarUI` project root (not this `test/` folder):

```
cmake -S . -B build_dll -G "Ninja" -DSOLARUI_BUILD_SHARED=ON
cmake --build build_dll
```

If you've already got a configured `build_dll` folder from before, you
only need the second line — it'll pick up any source changes and
rebuild incrementally.

This produces two files you need:

- `bin/libSolarUI.dll` — the actual runtime DLL
- `build_dll/libSolarUI.dll.a` — the import library, needed at link time

## 2. Copy both into this folder

From the project root:

```
cp bin/libSolarUI.dll test/libSolarUI.dll
cp build_dll/libSolarUI.dll.a test/libSolarUI.dll.a
```

Both files need to sit next to `test.cpp` — the `.dll.a` for linking,
and the `.dll` for `test.exe` to actually load at runtime.

## 3. Compile

From inside `test/`:

```
g++ -std=c++11 -I../src/external/freeglut-3.0.0/include test.cpp libSolarUI.dll.a -L../src/external/freeglut-3.0.0/lib/x64 -lfreeglut -lopengl32 -lglu32 -lgdi32 -lwinmm -o test.exe
```

You'll also need `freeglut.dll` in this folder to actually run
`test.exe` — grab the **64-bit** one from
`src/external/freeglut-3.0.0/bin/x64/freeglut.dll` (not the one in
`bin/` without `x64/` — that one's 32-bit and will fail to launch with
a `0xc000007b` error if mixed with everything else being 64-bit).

## 4. Run

```
./test.exe
```

Esc quits.

## One-liner

Steps 2 and 3 combined, run from the project root:

```
cp bin/libSolarUI.dll test/libSolarUI.dll && cp build_dll/libSolarUI.dll.a test/libSolarUI.dll.a && cd test && g++ -std=c++11 -I../src/external/freeglut-3.0.0/include test.cpp libSolarUI.dll.a -L../src/external/freeglut-3.0.0/lib/x64 -lfreeglut -lopengl32 -lglu32 -lgdi32 -lwinmm -o test.exe
```

## Notes

- This only builds against a **static** `SolarUI` won't work here —
  it needs the shared DLL, since `test.cpp` only includes the public
  `SolarUI.h` header and relies on the DLL exporting everything.
- If `test.exe` fails to launch with `0xc000007b`, it's almost always
  an architecture mismatch between one of the DLLs sitting next to it
  (32-bit vs 64-bit) — check with `file *.dll` in this folder, they
  should all say `x86-64`.