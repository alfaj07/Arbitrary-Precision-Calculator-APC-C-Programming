# Arbitrary Precision Calculator (APC)

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

An **Arbitrary Precision Calculator** (Bignum Calculator) implemented in C. Standard primitive integer types in C (`int`, `long`, `long long`) are bounded by 32-bit or 64-bit limits and quickly overflow when computing large numerical values. 

This project overcomes hardware-level integer size constraints by representing numbers dynamically using **Doubly Linked Lists (`Dlist`)**, allowing arithmetic calculations on numbers with virtually unlimited digits without precision loss or overflow.

---

## 🚀 Features

- **Arbitrary Length Arithmetic**: Perform operations on numbers with hundreds or thousands of digits.
- **Doubly Linked List Data Structure**: Stores individual digits in bidirectional nodes, enabling efficient traversal from both most-significant and least-significant ends.
- **Supported Operations**:
  - ➕ **Addition (`+`)**: Supports large positive and negative numbers with carry propagation.
  - ➖ **Subtraction (`-`)**: Handles borrow logic, magnitude comparison, and sign determination.
  - ✖️ **Multiplication (`*`)**: Arbitrary precision product calculation.
  - ➗ **Division (`/`)**: Computes integer quotient using repeated subtraction logic.
  - ⚡ **Exponentiation (`^`)**: Computes powers ($A^B$) for large base and exponent values.
- **Full Sign & Negative Number Handling**: Accurately computes expressions involving signed numbers (e.g., `-123 + 456`, `123 - (-456)`, `(-10) * (-20)`).
- **Safe Memory Management**: Automatically deallocates dynamically allocated list nodes upon completion to prevent memory leaks.

---

## 📁 Project Structure

| File | Description |
| :--- | :--- |
| [`main.c`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/main.c) | Main driver program: parses input expressions, routes operators, manages signs, and prints results |
| [`apc.h`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/apc.h) | Header file defining `Dlist` structure, function prototypes, and status macros |
| [`apc.c`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/apc.c) | Core Doubly Linked List helper utilities (`dl_insert_first`, `dl_delete_first`, `dl_delete_list`, `print_list`) |
| [`add.c`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/add.c) | Arbitrary precision addition implementation |
| [`sub.c`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/sub.c) | Arbitrary precision subtraction implementation |
| [`mul.c`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/mul.c) | Arbitrary precision multiplication implementation |
| [`div.c`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/div.c) | Arbitrary precision division implementation |
| [`power.c`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/power.c) | Arbitrary precision power/exponentiation implementation |
| [`makefile`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/makefile) | Makefile for automated compilation and cleaning |
| [`LICENSE`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/LICENSE) | MIT License file |

---

## 🛠️ Build & Installation

### Prerequisites
- **GCC Compiler** (`gcc` supporting C11 standard)
- **Make** utility (optional, for automated build)

### Compilation

#### Using `make`:
```bash
make
```
This builds all source files into the executable `apc` (or `apc.exe` on Windows).

To clean object files and executables:
```bash
make clean
```

#### Manual Compilation with `gcc`:
```bash
# On Linux / macOS
gcc -Wall -Wextra -std=c11 *.c -o apc

# On Windows (MinGW)
gcc -Wall -Wextra -std=c11 *.c -o apc.exe
```

---

## 💻 Usage & Examples

Run the executable and provide an arithmetic expression when prompted:

```bash
./apc
```
*(On Windows: `./apc.exe` or `apc.exe`)*

### Example Prompts:

```text
Enter expression (example: 123+456 or 135-65 or 12*5 or 10/2 or 5^2): 
```

#### 1. Large Number Addition
```text
Enter expression: 999999999999999999999999999999+1
1000000000000000000000000000000
```

#### 2. Large Number Subtraction
```text
Enter expression: 1000000000000000000000000000000-1
999999999999999999999999999999
```

#### 3. Large Multiplication
```text
Enter expression: 123456789123456789*987654321987654321
121932631356500531347203169112635269
```

#### 4. Large Division
```text
Enter expression: 100000000000000000000/2
50000000000000000000
```

#### 5. Exponentiation
```text
Enter expression: 2^64
18446744073709551616
```

#### 6. Negative Number Operations
```text
Enter expression: -123456789+23456789
-100000000
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE) - see the [`LICENSE`](file:///d:/Coaching/project/MD_Alfaj_Ahmed%2826011f_051%29%28APC%29/LICENSE) file for details.

---

## 👤 Author

**MD Alfaj Ahmed**
