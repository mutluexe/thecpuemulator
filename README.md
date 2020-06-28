# The Cpu Emulator 

CSE216 Computer Organization Homework

## Usage

First compile the file emulator.c

```
gcc emulator.c -o emulator
```

Then run it by passing the program.txt as an argument

```
./emulator program.txt
```

## Matrix Multiplication

### Matrices

The matrices that I'm multiplying
```
| 13 7 |                  | 17 9 21 3 |
| 8  5 |        and       | 6 11  8 5 | 2x4
| 9  3 | 3x2 
```

### Values
```
m -> row number of the first matrix
n -> column number of the first matrix (as well as row number of the second matrix)
p -> column number of the second matrix
m0 -> maximum value of m
n0 -> maximum value of n
p0 -> maximum value of p
```
### Formulas

To work with 2D arrays on 1D stack we need some formulas to find the index of the matrices.

Our first formula is `m * n0 + n`. For example if we are trying to find index of `(1,1)` on 2x2 matrix, this formula will give us `3` which is the index of the value that we want from memory.

For better understanding:

```
| 1 2 |         
| 3 4 | 2x2 
```

This matrix will be look like this on 1D memory,

```
0 => | 1 |
1 => | 2 |
2 => | 3 |
3 => | 4 | 
```
Index of the `(1,1)` value which is `4` in this case will be `3`.

On the otherhand, we should have another matrix for multiplication and they will be consecutive values on the stack so we should have different formula for finding index of the second matrix which is `(m0 * n0) + (n * p0) + p` in this case.

### Addresses

Addresses of some values
```
100 => SUM
101 => m
102 => n
103 => p
104 => m0
105 => n0
106 => p0
```

### Explanation 

On code, until `line 29`, I store the values to the memory.

From `line 29 to 36`, I'm initializing the `m,n,p` values. Which we will increment them later.

Until `line 42`, I assign `m0,n0,p0` values. 

From `line 43 to 51`, Im pushing the values to the stack but in reverse order. So when I pop it, I'll have the value that I want. 

We should more focus on instructions that we are using on `line 51 to 53`. We are using these `POP, SWAP, LOADI` combination a lot. We need these becase we pushed the "memory addresses" to the stack, so when we call `POP` instruction, on `AC` register we have the memory address of the value that we want. But we actually want the value so we call `SWAP` instruction and now `AX` register has memory address. After than we call `LOADI` instruction so now we have the value we want on `AC` register.

Until `line 64`, we are calculating the first formula, and we store the value at memory address `201`.

After until `line 92`, we are calculating the second formula, be careful that we have used memory `202` for `n * p0` part of second formula.

From `line 93 to 97`, we multiplied the values that we got, and wrote result to the address `100` which is `SUM`.

Until `line 98 to 101`, we call `n` and we check the value if we exceed after adding 1 to it. We add 1 because there is no such functionality to check "less than or equal to" on our `CMPM` instruction.

On lines between `102 to 104`, we check whether `n` value exceeded or not. If it isn't we call `RETURN` instruction; it simply pop the last element on the stack and assign our program counter `PC` to the value `43`. 

Until now on; As you can guess, we are iterating through `n` which is columns of the first matrix and row of the second matrix, multiplying them and storing to the sum value. If we exceeded we are jumping to `line 105` and displaying the value.

From `line 107 to 114`, first we reset the values of the `SUM` and `n` then we are incrementing the value of the p and starting iterating through other rows of the second matrix.

After than we are checking if we exceed `p0` value. If we are not we call `RETURN` instruction. 

If we exceeded than we are resetting the `p` value and to print new line; we are calling the `DASC` instruction after loading `10` to the `AC` register.

From `line 122 to 125` we are incrementing the `m` value to start multiplying remaining rows of the first matrix.

And last, again we check whether we exceed `m0` value or not, if we exceeded; multiplication is complete and we are done.
