#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include<string.h>

#define NORM 0
#define DNORM 1
#define SPEC 2
#define BIAS 127
int get_flt_bits_int(float);
char* get_flt_sign_char(float);
int get_flt_sign_val(float);
char* get_flt_exp_str(float);
int get_flt_exp_val(float);
int get_flt_exp_mode(float);
char* get_flt_man_str(float);
double get_flt_man_val(float);
char* get_flt_bits_str(float);
void print_flt(float);

/*
    Declare a "typedef struct {} flt;" to contain data for a float
    The data should include:
        An integer for the sign
            (1 for positive, -1 for negative)
        An integer for the exponent value
            (should be bit value to integer minus BIAS or -126 for denormalized)
        A float to contain the value of the mantissa
            (Actual float value extracted from the binary value)
        An integer to contain the mode using the defines above
            (NORM, DNORM and SPEC)
    Example after processing: -15.375 = 1 10000010 11101100000000000000000
        sign = -1
        exp = 3
        man = 0.9218750000
        mode = NORM
*/


typedef struct {
	int sign;
	int exp;
	float man;
	int mode;
}flt;


/*
    Write a function get_flt_bits_int to return an integer with the
    bits copied from a float.
    Example:
        for f = -15.375,
        the bits of int n = 11000001011101100000000000000000

    Look at the slides and code from the float lectures and use the
    indirection trick.  This can easily be done in one line of code.
    The function should accept a float and return an int.
*/

int get_flt_bits_int(float f){
	
	
	return *(int*)(&f);

}


/*
    Write a function that returns the sign of a float as a char.
    You should call get_flt_bits_int to get the bits in an int
    and return '1' if the sign is negative else return '0'.  The
    function should accept a float and return a string.
*/

char* get_flt_sign_char(float f){

	char *sign = malloc(3);
	
	int n = get_flt_bits_int(f);
	
	if(n < 0)
		sign[0] = '1';
	else
		sign[0] = '0';
	
	sign[1] = ' ';
	sign[2] = '\0';
	
	return sign;
}


/*
    Write a function that returns the sign of a float as an integer.
    You should call get_flt_bits_int to get the bits in an int
    and return -1 if the sign is negative else return 1.  The function
    should accept a float and return an int.
*/

int get_flt_sign_val(float f){

	int sign;
	
	int n = get_flt_bits_int(f);
	
	if(n < 0)
		sign = -1;
	else
		sign = 1;
	
	
	return sign;
}


/*
    Write a function to return a string containing the
    actual binary value of the exponent of a float in a
    char array.  You should call get_flt_bits_int to get
    the bits in an int and return the string.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the exponent bits are "10000010"
    The function should accept a float and return a string.
*/

char* get_flt_exp_str(float f){
	
	char *bits = malloc(10);
	int n = get_flt_bits_int(f);
	
	int i;
	n=n>>23;
	
	for(i = 0; i<8; i++){
		bits[8-i-1] = ( n & 1) + '0';
		n = n>>1;
	}
	
	bits[i] = ' ';
	bits[i+1] = '\0';
	
	return bits;

}


/*
    Write a function to return an integer containing the
    actual integer value of the exponent of a float.  You
    should call get_flt_bits_int to get the bits in an int
    and return the int with the exponent value.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the exponent bits are 10000010
            the actual value of the exponent is 3
    The function should accept a float and return an int.
*/

int get_flt_exp_val(float f){
	
	int n = get_flt_bits_int(f);
	
	int i;
	n=n>>23;
	int exp = 0;
	int mul = 1;
	
	for(i = 0; i<8; i++){
		exp = exp + (n & 1) * mul;
		n = n>>1;
		mul = mul * 2;
	}
	
	if(exp == 255)
		return exp;
	else
		return exp-BIAS;
	
	
}


/*
    Write a function to return an integer containing the
    mode of the exponent of a float.  You should call
    get_flt_exp_val to get the bits in an int and return
    the int with the mode value.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the exponent bits are 10000010
            the mode is NORM
    The function should accept a float and return an int.
*/


int get_flt_exp_mode(float f){

	int mode;
	int exp = get_flt_exp_val(f);
	//printf("exp is %d\n", exp);

	if(exp == 255){
		mode = SPEC;
		//printf("spec\n");
	}
	else if(exp == 0){
		mode = DNORM;
		//printf("dnorm\n");
	}
	else{
		mode = NORM;
		//printf("norm\n");
	}
	
	return mode;
}


/*
    Write a function to return a string containing the
    actual binary value of the mantissa of a float in a
    char array.  You should call get_flt_bits_int to get
    the bits in an int and return the string.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the mantissa bits are "11101100000000000000000"
    The function should accept a float and return a string.
*/

char * get_flt_man_str(float f){

	char *bits = malloc(25);
	int n = get_flt_bits_int(f);
	
	int i;
	
	for(i = 0; i<23; i++){
		bits[23-i-1] = ( n & 1) + '0';
		n = n>>1;
	}
	
	bits[i] = ' ';
	bits[i+1] = '\0';
	
	return bits;
}


/*
    Write a function to return a float containing the
    actual float value of the mantissa of a float.  You
    should call get_flt_bits_int to get the bits in an int
    and return the int with the mantissa value.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            the mantissa bits are 11101100000000000000000
            the actual value of the mantissa is 0.9218750000
    The function should accept a float and return an int.
*/

double get_flt_man_val(float f){
	int n = get_flt_bits_int(f);
	
	int i;
	double man = 0;
	double mul = pow(2,23);
	
	
	for(i = 0; i<23; i++){
		man = man + (n & 1) / mul;
		//printf("%d\n", n&1);
		//printf("man = %.12f\n", man);
		n = n>>1;
		mul = mul / 2;
		//printf("mul is %.12f\n", mul);
	}
	
	return man;
}

/*
    Write a function to return a string containing the
    actual binary value of a float in a char array.  You
    should call get_flt_sign_char, get_flt_exp_str and
    get_flt_man_str to get the bits in an char and two
    strings and return the concatenated string.
    Example:
        for f = -15.375
            n = 11000001011101100000000000000000
            The sign is '1'
            the exponent is "10000010"
            and the mantissa bits are "11101100000000000000000"
            The string should be formatted as:
                "1 10000010 11101100000000000000000" to clearly
                separate the 3 parts.
    The function should accept a float and return a string.
*/

char * get_flt_bits_str(float f){

	char * res = malloc(36);
	char * sign = malloc(4);
	sign = get_flt_sign_char(f);
	char * exp = malloc(10);
	exp = get_flt_exp_str(f);
	char * man = malloc(24);
	man = get_flt_man_str(f);
	
	
	
	strcpy(res, sign);
	//printf("%s\n", res);
	strcat(res, exp);
	//printf("%s\n", res);
	strcat(res, man);
	//printf("%s\n", res);
	
	return res;
}


/*
    Write a function to separate the parts of a float
    into a flt struct as described above.  You should
    call get_flt_sign_val, get_flt_exp_mode,
    get_flt_exp_val and get_flt_man_val.
    Hint:  make sure to set exponent to -126 for
    DNORM mode.
*/
flt get_flt_val_flt(float f){

	flt num;
	num.sign = get_flt_sign_val(f);
	num.mode = get_flt_exp_mode(f);
	if(get_flt_exp_mode(f) == 1)
		num.exp = -126;
	else
		num.exp = get_flt_exp_val(f);
	num.man = get_flt_man_val(f);
	
	return num;
}



/*
    Write a function to print a flt struct to screen.
    It should accept a flt struct and return nothing.
    Hint: Use if statement to print mode.
*/
void print_flt(float f){

	flt num = get_flt_val_flt(f);
	printf("sign = %d\n", num.sign);
	printf("exp = %d\n", num.exp);
	printf("man = %f\n", num.man);
	if(num.mode == 0)
		printf("mode = normalized\n");
	else if(num.mode == 1)
		printf("mode = denormalized\n");
	else
		printf("mode = specialized\n");
}



/*
    Write a function to get the actual float value back
    out of a flt struct.
    Hints:
        The float value produced will depend on the mode.
        To set a float to infinity use the math library constant INFINITY
        To set a float to not-a-number use the math library constant NAN
        Check the slides and text for conditions for NORN, DNORM and SPEC
        You need to return (sign) * M * 2^e
*/

float get_flt_bits_val(flt f){

	if(f.mode==0)
		return (pow(-1,f.sign))*(1+f.man)*(pow(2,f.exp));
	else if(f.mode == 1)
		return (pow(-1,f.sign))*f.man*(pow(2,f.exp));
	else{
		if(f.man == 0.0)
			return INFINITY;
		else
			return NAN;
	}
}


/*
    Write a main function that calls an prints results for
    each function when completed.
    get_flt_sign_char
    get_flt_sign_val

    get_flt_exp_str
    get_flt_exp_val

    get_flt_man_str
    get_flt_man_val

    get_flt_bits_str

    get_flt_val_flt
    print_flt

    get_flt_bits_val
*/
int main(){

	//float f = -15.375;
	float f = INFINITY;
	//float f = sqrt(-1);
	
	int n = *(int *)(&f);
	
	//printf("%d\n", get_flt_bits_int(f));
	printf("f = %f\n\n", f);
	printf("sign = %s\n", get_flt_sign_char(f));
	printf("s = %d\n\n", get_flt_sign_val(f));
	printf("exp = %s\n", get_flt_exp_str(f));
	printf("e = %d\n\n", get_flt_exp_val(f));
	//printf("%d\n", get_flt_exp_mode(f));
	printf("man = %s\n", get_flt_man_str(f));
	printf("m = %f\n\n", get_flt_man_val(f));
	printf("bits = %s\n\n", get_flt_bits_str(f));
	print_flt(f);
	printf("\nff = %f\n", get_flt_bits_val(get_flt_val_flt(f)));
	


    return 0;
}
