/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  2. Performs right shifts arithmetically. This means add 1s to the most significant bits if it is a negative number
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // 0101 ^ 1100 = 1001
  // 0101 & 1100 = 0100 get all matched 1s
  // ~0101 & ~1100 = 1010 & 0011 = 0010 get all matched 0s
  // get all unmatched bits: ~0100 & ~0010 = 1011 & 1101 = 1001 --> XOR
  return ~(x & y) & ~(~x & ~y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // minimum two's complement integer: 0x80000000 --> -2^31
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  // maximum two's complement number: 0x7fffffff, ~0x7fffffff = 0x80000000, 0x7fffffff + 1 = 0x80000000
  // check if ~x is equal to x + 1; 
  // if x >= 0: if x != 0x7fffffff, then x + 1 must be no larger than 0x7fffffff (positive value) while its bitwise NOT is negative. When x == 0x7fffffff, then x + 1 and ~x are both 0x80000000 (negative value)
  // if x < 0: x + 1 is no larger than 0 while ~x is positive
  // exception: 0xffffffff --> 0xffffffff + 1 = 0, ~0xffffffff = 0
  // TODO: solve the execption

  // int val1 = x + 1;
  // int val2 = ~x;
  // int val3 = val1 ^ x;
  // int val4 = !(~(x + 1)^x);
  // int val5 = ~x;
  // printf("x: %x, val1: %d, val2: %d, val3: %d, %d, %d\n", x, val1, val2, val3, val4, val5);

  // check if x + 1 is equal to ~x: if x + 1 == ~x, then all bits of (x + 1)^x are 1, which means ~(x + 1)^x is 0
  // if x + 1 is not equal to ~x, then ~(x + 1)^x must contain 1, whose value is not 0
  // => !(~(x + 1)^x) == 1 means x + 1 == ~x
  // 1: is max, 0: is not max; &
  // x + 1 is equal to ~x and ~x is not 0
  return (!(~(x + 1)^x)) & (!(~x));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1 (odd bits from left to right)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // return 0xAAAAAAAA & x == 0xAAAAAAAA  --> val1 = 0xAAAAAAAA & x, return !(~(~val1 ^ 0xAAAAAAAA))
  int val1;
  int val2;
  // important: construct 0xAAAAAAAA by left shift
  val1 = (0xAA << 8) + 0xAA;   // 0xAAAA
  val1 = (val1 << 16) + val1;   // 0xAAAA00
  val2 = x & val1;
  return !(~(~val2 ^ val1));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // 1 --> 0xfffffffe - 1 --> 0x00000001 + 1 - 1 --> -1
  // 48 = 0x00000030 --> 0xffffffcf - 1 --> 0x00000030 + 1 - 1 --> -48
  // 0x00000000 --> 0xffffffff - 1 --> 0x00000000 + 1 - 1 --> -0
  // 0x80000000 --> 0x7fffffff - 1 --> 0x80000000 + 1 - 1 --> -max?
  printf("val = %x\n", x);
  return (~x) - 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' (48) to '9' (57))
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // TODO
  // 00110000 <= x <= 00111001, 0000, 0001, 0010, 0011, 0100, 0101, 0111, 1000, 1001; not allowed: 1010, 1011, 1100, 1101, 1110, 1111
  // first 4 bits are 0011; last 4 bits are no more than 1001
  int val1;
  int val2;
  int val3;
  val3 = (x >> 4);
  // extract 5th to 8th bits (count from right to left)
  // first 4 bits 0011 ^ 0xC = 1111, ~1111 = 0, else > 0
  // 0x000000 0011 ^ 0x0000000 1100 
  val1 = ~((x >> 4) ^ 0xC); // expect to be 0
  // extract 2th to 4th bits (count from right to left)
  // first bit is 0, or first bit is 1 and the following 2 bits are 00 (100 ^ 011 = 111) --> 0xxx, 100x
  val2 = ~((x >> 3) & 0x1) & !(~((x >> 1) ^ 0x3)); // expect to be 1
  // printf("x = %x, val1 = %x, val2 = %x, val3 = %x\n", x, val1, val2, val3);
  return !(val1 + ~val2);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // if x == 0, return z; else return y
  int val1 = !(!x);
  val1 = (val1 << 1) + val1;  // 00 or 11
  val1 = (val1 << 2) + val1;  // 0000 or 1111
  val1 = (val1 << 4) + val1;  // 00000000 or 11111111
  val1 = (val1 << 8) + val1;  // 0x0000 or 0xffff
  val1 = (val1 << 16) + val1; // 0x00000000 or 0xffffffff
  return (val1 & y) + (~val1 & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // int val1 = x ^ y;
  // find the location i of the first 1 in val1 from right to left
  // compare bit value of x at location i and y at location i
  return 2;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return 2;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}
