/*
 * CS:APP Data Lab
 *
 * <Maeneka Grewal, 204901948>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code
must conform to the following style:

int Funct(arg1, arg2, ...) {
    /* brief description of how your implementation works */
    int var1 = Expr1;
    ...
    int varM = ExprM;

    varJ = ExprJ;
    ...
    varN = ExprN;
    return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.


You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 */
int pow2plus1(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    return (1 << x) + 1;
}

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 */
int pow2plus4(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    int result = (1 << x);
    result += 4;
    return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.  This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc (data lab checker) compiler (described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc. Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function. If there are any inconsistencies
between the maximum ops in the writeup and in this file, consider
this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    /* exploits the fact that you negate using ~ and have to add one because if it is a negative number it would be 1... and if it's positive it is 0... (ex: 5 is 0000........0101 and negated is 1111......1010. The way negative numbers work is you add on the numbers to the most significant bit. So the negated number is -6. Ipso facto add one. Or the other way, -5 is 1..........1011. Negated is 0000......0100. That is 4. Add 1!*/
    return ~x + 1;
}
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    /* Uses negation twice and the 'or' operator to do an 'opposite' &, and then essentially reversed the & by negative that. It's DeMorgan's Law I think */
    int negx = ~x;
    int negy = ~y;
    return ~(negx|negy);

}
/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
    /*Look at each set of 8 bytes and compare with 170, which is 1010 1010 in binary, so anding it will preserve the odd numbered bits that are 1. If there are no odd bits that are 1, oz will be 0. 0 is 'false' so !oz is true and returns 1. The function wants us to return 0 so !! it. If there are bits that are 1, oz will be any other number. Any other number is 'true' so !oz is false and returns 0. But we want 1. So !! it.*/
    int oz = (x | x >> 8 | x >> 16 | x >> 24) & 170; //naming: oz stands for One or Zero
    return !!oz;;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    /*First shift to get either -1 if it was negative, or 0 if it was positive. Then get the bottom number by 1 << n which is essentially 2^n. You then have to subtract one from the bottom, since we need to round towards 0. But we can't use -, so ~0 is the same thing as -1. When you and it with the MSB you either get 0 or the (bottom - 1) number. Add this to account for rounding, because positive numbers naturally round to 0 but negative numbers do not. Then you can do >> n, which is dividing by 2^n and get your properly rounded number */
    int shift = x >> 31;
    int bottom = (1 << n);
    int and = shift & (bottom + (~0));
    int num = x + and;
    int div = num >> n;
    return div;
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    /*When both numbers are positive and the sum is negative, overflow occured. When both numbers are negative and the sum is positive, overflow occured. Obtain MSB of the numbers and their sums by shifting 31. If both are negative or positive, then ~(msbX ^ msbY) would give -1. If they differ in sign, it would 0. When you and it, you'd get 0 which you reverse with a ! to get true, because it is true. And the reverse if it is false.*/
    int msbX = x >> 31;
    int msbY = y >> 31;
    int msbSum = (x+y) >> 31;
    int checkBoth = ~(msbX ^ msbY);
    int comp = checkBoth & (msbSum ^ msbX);
    return !comp;
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    /*If x is bigger and both x and y are negative, the whichBigger will be still be negative. If both x and y are positive and whichBigger comes out negative, y is bigger. That line is essentially subtracting y but not accounting for the one. If they are equal, you have to negate it at the end.*/
    int msbX = x >> 31;
    int msbY = y >> 31;
    int whichBigger = (x + ~y) >> 31;
    int eq = (!(msbX ^ msbY)) & whichBigger;
    return !(eq | (msbX & !msbY));
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
    /* Doing n << 3 is the same as n * 2^3 aka n * 8, so this tells you exactly how many bits you need to shift to get to your specific 8 bit slot. Then 255 is 1111 1111 and you shift that to your slot. For example if you're replace byte 1, it would be 0......... 1111 1111 0000 0000. Then you negate this so that you have a 32-bit word of 1s everywhere and 0's in your 'slot'. You & this with the number so that your number is also empty with 0's in the 'slot'. Shift your replacing byte to that slot, and then or them together so that they combine.*/
    int shift = n << 3;
    int converter = (255 << shift);
    int ones = ~converter;
    int ready = x & ones;
    int inplace = c << shift;
    int replaced = inplace | ready;
    return replaced;
}
/*
 * tc2sm - Convert from two's complement to sign-magnitude
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
    int sign = x >> 31;
    //printf("Sign: %d\n", sign);
    int msb = sign << 31;
    //printf("MSB: %d\n", msb);
    int ored = x ^ sign;
    //printf("Ored: %d\n", ored);
    int neg = ~sign + 1;
    //printf("Neg: %d\n", neg);
    //printf("Pos: %d\n", pos);
    int sm = msb + ored + neg;
    return sm;
}

/*int main()
{
    int n = 34;
    int m = 34;
    int q = 0x7;
    int neg = negate(n);
    int and = bitAnd(n, m);
    int odd = anyOddBit(q);
    int div = divpwr2(n, m);
    int add = addOK(n, m);
    int great = isGreater(n,m);
    int repl = replaceByte(0x12345678, 0, 0xab);
    int sm = tc2sm(-5);
    printf("Negate function: %d\n", neg);
    printf("BitAnd function: %d\n", and);
    printf("AnyOddBit function: %d\n", odd);
    printf("DivPwr2 function: %d\n", div);
    printf("AddOK function: %d\n", add);
    printf("IsGreater function: %d\n", great);
    printf("ReplaceByte function: %d\n", repl);
    printf("Tc2Sm function: %d\n", sm);
}*/

