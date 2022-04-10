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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
  int a = x & ~y;
  int b = ~x & y;
  return ~(~a & ~b);
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
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	/*
	 * For unsigned:
	 * ~x = 2^w - 1 - x
	 * replace x with Tmax:
	 * 2^w - 1 - 2^w-1 + 1 = 2^w-1 = Tmax + 1
	 */

	int a = ~x;
	int b = x + 1;
	int zero = a ^ b;

	// 0 if x is all 1
	int x_ = ~x;
	// 0 if x is all 1, or 1
	int t = !!x_;
	
	return (!zero) & t;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // AND two odd bits each time
  int x_8 = (x >> 16) & x;
  int x_4 = (x_8 >> 8) & x_8;
  int x_2 = (x_4 >> 4) & x_4;
  int x_1 = (x_2 >> 2) & x_2;
  return (x_1 & 2) >> 1;
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
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // check if x has only these bits
  int x_same = x & 0x3F;
  int zero = x_same ^ x;

	// check if x has 0x30 set
	int x_3 = x & 0x30;
	int zero_3 = x_3 ^ 0x30;

  // least significant 4 bits
  int ls4 = x & 0xF;
  int no_carry = ls4 + 6;
  int zero_ = no_carry & 0x10;

	// assume x = 0
	int x_0 = !!x;
  return (!(zero | zero_ | zero_3)) & x_0;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // 1 if x is true, or 0
  int x_ = !!x;
  // all 1 if x is true, or all 0
  int x_true = ~x_ + 1;
  // all 1 if x is false, or all 0
  int x_false = ~x_true;
  return (y & x_true) | (x_false & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	// all 0 if x is greater than 0, else all 1
	int zero_x_pos = x >> 31;
	int zero_y_pos = y >> 31;
	int zero_x_neg = !zero_x_pos;
	int zero_y_neg = !zero_y_pos;
	
	int equal = !(x ^ y);
	int neg_pos = !(zero_x_neg | zero_y_pos);
	
	int sub = y + ~x + 1;
	int zero_sub_pos = sub >> 31;
	int neg_neg = !(zero_x_neg | zero_y_neg | zero_sub_pos);
	int pos_pos = !(zero_x_pos | zero_y_pos | zero_sub_pos);

  return equal | neg_pos | neg_neg | pos_pos;
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
	// OR all bits to one bit
	x = (x >> 16) | x;
	x = (x >> 8) | x;
	x = (x >> 4) | x;
	x = (x >> 2) | x;
	x = (x >> 1) | x;
  return (x & 1) ^ 1;
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
    // fill = x < 0 ? ~x : x;
    unsigned fill = x ^ (x >> 31);
	fill = (fill >> 1) | fill;
	fill = (fill >> 2) | fill;
	fill = (fill >> 4) | fill;
	fill = (fill >> 8) | fill;
	fill = (fill >> 16) | fill;

	// add up all bits

	// mask_16 = 0101...
	unsigned mask_16 = 0x55;
	mask_16 = (mask_16 << 8) | mask_16;
	mask_16 = (mask_16 << 16) | mask_16;
	unsigned a_16 = mask_16 & fill;
	unsigned b_16 = (fill & ~mask_16) >> 1;
	unsigned sum = a_16 + b_16;

	// mask_8 = 0011...
	unsigned mask_8 = 0x33;
	mask_8 = (mask_8 << 8) | mask_8;
	mask_8 = (mask_8 << 16) | mask_8;
	unsigned a_8 = sum & mask_8;
	unsigned b_8 = (sum & ~mask_8) >> 2;
	sum = a_8 + b_8;

	// mask_4 = 00001111...
	unsigned mask_4 = 0x0F;
	mask_4 = (mask_4 << 8) | mask_4;
	mask_4 = (mask_4 << 16) | mask_4;
	unsigned a_4 = sum & mask_4;
	unsigned b_4 = (sum & ~mask_4) >> 4;
	sum = a_4 + b_4;

	// mask_2 = 0x00FF00FF
	unsigned mask_2 = 0xFF;
	mask_2 = (mask_2 << 16) | mask_2;
	unsigned a_2 = sum & mask_2;
	unsigned b_2 = (sum & ~mask_2) >> 8;
	sum = a_2 + b_2;
	
	// mask_1 should be 0x0000FFFF, but sum won't be greater than 16
	unsigned mask_1 = 0xFF;
	unsigned a_1 = sum & mask_1;
	unsigned b_1 = (sum & ~mask_1) >> 16;
	sum = a_1 + b_1;
	
	return sum + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	unsigned ret = uf;
	unsigned exp_mask = ((1 << 8) - 1) << 23;
	unsigned exp = exp_mask & uf;
	
	unsigned frac_mask = (1 << 23) - 1;
	unsigned frac = frac_mask & uf;
	
	unsigned new_exp = ((exp >> 23) + 1) << 23;

	if (exp == exp_mask) {
		ret = uf;
	} else if (!exp) {
		ret =  (uf & ~frac_mask) | (frac << 1);
	} else {
		ret = new_exp | (uf & ~exp_mask);
	}
	return ret;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
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
int floatFloat2Int(unsigned uf) {
	unsigned frac_mask = (1 << 23) - 1;
	unsigned exp_mask = ((1 << 8) - 1) << 23;
	unsigned frac = frac_mask & uf;
	unsigned exp = exp_mask & uf;
	int bias = (1 << 7) - 1;
	int exp_val = (exp >> 23) - bias;
	int shift_val = exp_val - 23;

	int ret = 0x80000000u;

	if (exp_val < 0) {
		ret = 0;
		// make sure it's in the range
	} else if (shift_val < 8) {
		int frac_val = frac | (1 << 23);
		if (shift_val < 0) {
			frac_val >>= (-shift_val);
		} else {
			frac_val <<= shift_val;
		}
		ret = frac_val;
		if (uf >> 31) {
			ret = -ret;
		}
	}
  return ret;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	int max_exp = 1 << 7;
	int bias = max_exp - 1;
	int lmt_exp = 1 - bias;
	int min_exp = lmt_exp - 23;

	unsigned ret = 0x7F800000;
	if (x < min_exp) {
		ret = 0;
	} else if (x < lmt_exp) {
		int shift_size = lmt_exp - x;
		ret = 1 << (23 - shift_size);
	} else if(x <= max_exp) {
		int exp = x + bias;
		ret = exp << 23;
	}
	return ret;
}
