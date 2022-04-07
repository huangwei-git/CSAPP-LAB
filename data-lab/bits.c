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
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    int a = n << 3;
    a = x >> a;
    a = a & 0xff;
  return a;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    int a = ~1;//构造0xfffffffe
    int b = 31 + (~n + 1);//左移31-n位
    int c = a << b;//获得高n位为1，其余位为0的数
    int d = ~c;
    int e = x >> n;
    int res = e & d;
    return res;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    // x & [01][01][01][01]... 获取右边子问题的返回值
    // (x >> 1) & [01][01][01][01]... 获取左边子问题的返回值，移位是为了对阶
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    // x & [0011][0011]... 获取右边子问题的返回值
    // 显然，第一步合并后，两个1bit相加结果需要2bit存储，因此用11取返回值
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x07070707) + ((x >> 4) & 0x07070707);
    x = (x & 0x000f000f) + ((x >> 8) & 0x000f000f);
    x = (x & 0x0000001f) + ((x >> 16) & 0x0000001f);  
    return x;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  // 通过逻辑与01010101... 获取右边子问题的返回值
  // x >> 1逻辑与01010101... 获取左边子问题的返回值
  // 为什么不x & 101010...获取左边? 为了对其子问题的解
  x = (x & 0x55555555) | ((x >> 1) & 0x55555555);
  x = (x & 0x11111111) | ((x >> 2) & 0x11111111);
  x = (x & 0x01010101) | ((x >> 4) & 0x01010101);
  x = (x & 0x00010001) | ((x >> 8) & 0x00010001);
  x = (x & 0x00000001) | ((x >> 16) & 0x00000001);
  return x^1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {

  int a = x >> 31;  
  int b = x >> n + (~1 + 1);
  int c = a ^ b;
  return !c;
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
    int a = x >> 31;
    int b = a & ((1 << n) + (~1 + 1));
    return (x + b) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return !(x >> 31) & !!(x & (~x + 1));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;
  int xy = x + (~y + 1);
  int sxy = (xy >> 31) & 1;
  return (sx^sy)&sx | (!sx^sy)&(sxy) | !(xy&(~xy + 1));
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    int a = 0;
    a = (!!(x >> 16)) << 4;
    a = a + (!!(x >> (a + 8)) << 3);
    a = a + (!!(x >> (a + 4)) << 2);
    a = a + (!!(x >> (a + 2)) << 1);
    a = a + !!(x >> (a + 1));
    return a;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xff;
    unsigned frac = uf & 0x7fffff;
    if( exp == 0xff && frac != 0) return uf;
    else return uf^(1 << 31);
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
    int signbit,exp,fracbit,c;
    unsigned temp;
    if(!x)
    return x;
    signbit = (x >> 31) & 0x01;
    if(signbit)
    x = ~x + 1;
    fracbit = 31;//第一位1的位置初始化位31，从前往后找
    temp = x;
    while(!(temp & 0x80000000))//找到第一个1的位置，同时把尾数移至高23位
    {
         temp <<= 1;
         fracbit--;
    }
    temp = temp << 1;//最前面的1省略
    exp = 127 + fracbit;
    c = 0;
    // 保留前23位，更具后9位进行舍入操作
    if((temp & 0x1ff) > 0x100) c = 1;// 后9位大于5
    if((temp & 0x3ff) == 0x300) c = 1;// 后9位等于5且第十位等于1
    return (signbit << 31)+(exp << 23)+(temp >> 9) + c;
}
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
    int signbit = uf >> 31;
    int exp = (uf >> 23) & 0xff;
    int frac = uf & 0x7fffff;
    if(exp == 0 && frac < 0x7fffff)// x为非规格化数，尾数*2不溢出
	frac <<= 1;
    else if(exp ==0 && frac==0x7fffff){// x为非规格化数，尾数*2溢出
	exp = 1;
	frac = 0x7ffffE;
    }
    else if(exp == 0xfe){// *2后上溢
	exp = 0xff;
	frac = 0;
    }
    else if(exp==0xff)// 上溢或NAN
	return uf;
    else// 规格化数
	exp += 1;
    return (signbit << 31) | (exp << 23) | frac;
}
