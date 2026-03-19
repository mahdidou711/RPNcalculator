# RPN Calculator

> A stack-based expression evaluator written in C — supports standard arithmetic, math functions, and single-variable plotting.

![Language](https://img.shields.io/badge/language-C99-blue?style=flat-square)
![Build](https://img.shields.io/github/actions/workflow/status/mahdidou711/RPNcalculator/build.yml?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-green?style=flat-square)
![Commits](https://img.shields.io/github/commit-activity/t/mahdidou711/RPNcalculator?style=flat-square)

---

## Overview

This project implements a [Reverse Polish Notation (RPN)](https://en.wikipedia.org/wiki/Reverse_Polish_notation) calculator in C. It also includes a **shunting-yard** module to accept standard infix expressions and convert them to postfix before evaluation.

**Modules:**

| File | Role |
|------|------|
| `stack.c` | Push/pop stack operations |
| `token.c` | Token types: number, operator, function, variable |
| `Cutter.c` | Lexer — splits input string into tokens |
| `eval.c` | RPN evaluator — processes token list using the stack |
| `shunting_yard.c` | Infix → postfix conversion (Dijkstra's algorithm) |
| `main.c` | CLI entry point |

---

## Supported Operations

**Binary operators:** `+` `-` `*` `/` `^`

**Math functions:** `sin` `cos` `exp` `sqrt` `ln`

**Variable:** `x` — assign a value at runtime, or sweep over a range to generate plot data.

---

## Build

### Requirements

- CMake ≥ 3.10
- GCC or Clang with C99 support
- `libm` (standard on Linux/macOS)

### Linux / macOS

```bash
mkdir build && cd build
cmake ..
cmake --build .
./calculatrice_RPN
```

### Windows (VS Code + CMake Tools)

1. Install extensions: **CMake Tools** and **C/C++** (Microsoft).
2. Open the project folder in VS Code.
3. Select a kit (GCC via MinGW, or MSVC).
4. Click **Build** in the status bar, or `Ctrl+Shift+P` → `CMake: Build`.
5. Run the generated `calculatrice_RPN.exe` from the `build/` folder.

### Manual (no CMake)

```bash
gcc src/stack.c src/token.c src/Cutter.c src/eval.c src/shunting_yard.c src/main.c \
    -Iinclude -lm -o calculatrice_RPN
```

---

## Usage

### RPN mode

```
Entrez une expression postfixee (ex: 3 4 + 2 *):
> 3 4 + 2 *
Résultat = 14
```

Step-by-step for `3 4 + 2 *`:

| Step | Token | Stack |
|------|-------|-------|
| 1 | `3` | [3] |
| 2 | `4` | [3, 4] |
| 3 | `+` | [7] |
| 4 | `2` | [7, 2] |
| 5 | `*` | [14] |

### With variable x

```
> x 2 ^ 3 +
Entrez la valeur de x : 2
Résultat = 7
```

### Plot mode (sweep over x)

If the expression contains `x`, the program can generate a data file for plotting:

```
x     f(x)
-10   97
-9.9  101.01
...
10    103
```

Import into Python/Matplotlib or Gnuplot to visualize.

---

## Project Structure

```
RPNcalculator/
├── include/
│   ├── stack.h
│   ├── token.h
│   ├── parser.h
│   └── eval.h
├── SRC/
│   ├── stack.c
│   ├── token.c
│   ├── Cutter.c
│   ├── eval.c
│   ├── shunting_yard.c
│   └── main.c
├── .github/
│   └── workflows/
│       └── build.yml
├── CMakeLists.txt
├── .gitignore
└── LICENSE
```

---

## Known Limitations

- Only one variable (`x`) is supported.
- No error recovery: malformed input may cause undefined behavior (planned: input validation).
- No interactive history or readline support.

---

## Author

**Bouama Mehdi** — M1 E3A-SATIE, Université Paris-Saclay  
[github.com/mahdidou711](https://github.com/mahdidou711)

## License

[MIT](LICENSE)
