# Calculator

A console application that functions as a calculator. It handles very large numbers (results up to about 10⁷ digits). The main goal of the project was to practice manual memory management.

---

## 1. Running the Program

- The program is a plain console app—an executable named `kalk.exe`. You can launch it by double-clicking the file.
- Alternatively, run it from the command line by typing:
  ```
  kalk.exe
  ```
- You can also start it from any IDE that supports console executables.
- In the same folder as the executable, there should be an input file named `in.txt`.

Optional argument:
- If you run
  ```
  kalk.exe 1
  ```
  then each operation’s result will be written into its own file (`out1.txt`, `out2.txt`, …).
- Otherwise, all answers go into a single file named `out.txt`.

---

## 2. Handling Invalid Input

The program checks each input token to see if it’s a valid number in the specified base. If it’s not, the output for that operation is  
```
NaN
```

It also guards against division by zero:
```
DIVISION_BY_ZERO
```

Leading zeros (except for the number “0” itself) are treated as an error:
```
TRAILING_ZEROES
```

When performing subtraction, if you try to subtract a larger number from a smaller one, it outputs:
```
SUBTRACTING_BIGGER_NUMBER_FROM_SMALLER
```

In every error case, the program does **not** abort; it prints the error message and moves on to the next operation in the input file.

---

## 3a. Input Format

All input is read from `in.txt`. Two modes are supported:

1. **Arithmetic operation**  
   ```
   <operator> <base>
   <number1>
   <number2>
   
   <more operations…>
   ```
   - `<operator>` ∈ { +, *, /, %, ^, − }  (supports exponentiation “^” and subtraction “−”)
   - `<base>` is an integer in [2 – 19]

2. **Base conversion**  
   ```
   <input_base> <output_base>
   <number>
   
   <more conversions…>
   ```
   - Both bases are integers in [2 – 19].

Note: While the program generally handles LF line endings, it prefers Windows-style CRLF.

---

## 3b. Output Format

By default, results go to `out.txt`. If you pass the argument `1` to the executable, each operation is written to its own file (`out1.txt`, `out2.txt`, etc.).

The format mirrors the input block:

1. **Arithmetic operation**  
   ```
   <operator> <base>
   <number1>
   <number2>
   <result>
   
   <more results…>
   ```

2. **Base conversion**  
   ```
   <input_base> <output_base>
   <number>
   <result>
   
   <more results…>
   ```

---

## 4. Compilation

Compile the program with GCC using optimization level 3:
```
gcc -O3 -o kalk kalk.c
```

---

## 5. Program Structure

1. Declare initial variables (including several `FILE*`) and open the necessary files.
2. In a loop (until an empty line is encountered):
   - Read the line describing either an arithmetic operation with its base or two bases for conversion.
   - Determine whether to perform an arithmetic operation or a base conversion.
   - Read the required number(s).
   - Execute the requested operation.
3. Clean up all allocated memory and close files before exiting.
