#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "printFixed.h"

/*gets the number of digits in input number*/
long
getDigits(long long number)
{
	long long n = number;
	long count = 0;

	while(n != 0){
		n /= 10;
		count++;
	}

	if(number == 0){
		count = 1;
	}

	return count;
}

/*gets the length of the number with precision*/
long
getPrecision(long digits, int precision){	
	long length; 
	
	if(precision <= (digits - 1)){
		length = digits + 1;
	} else if (precision == digits) {
		length = digits + 4;
	} else { 
		length = precision + 4;
	}

	return length;
}

/*converts string numbers to absolute value*/
char
* checkNegative(char *snumber)
{
	int length = strlen(snumber);
	
	for(int i = 0; i < strlen(snumber); i++){
		if(snumber[i] == '-'){
			length--;
		}
	}

	char *abs_snumber = malloc(length);

	if(length < strlen(snumber)){
		for(long i = 1; i < strlen(snumber); i++){
			abs_snumber[(i - 1)] = snumber[i];
		}

		return abs_snumber;
	}

	return snumber;
}

/*extends the number string according to precision*/
char
* precisionExtend(long long number, int precision, char decimalPoint){

	/*get the number of digits*/
	long digits = getDigits(number);

	/*convert number to string*/
	char snumber[digits++];	

	sprintf(snumber, "%lld", number);

	/*check for negative numbers*/
	char *abs_snumber = checkNegative(snumber);

	/*create precision number*/
	long length = getPrecision(digits, precision);
	char *pnumber = malloc(length);

	pnumber[(length - 1)] = '\0'; /*add terminating character*/
	
	/*place decimal point*/
	if(precision < (digits - 22)){
		pnumber[(length - 2 - precision)] = decimalPoint;
	} else {
		pnumber[1] = decimalPoint;
	}

	/*add number digits*/
	long index = 0;

	for(long i = 0; i < (length - 1); i++){
		
		if(pnumber[i] != decimalPoint){

			if((i >= (length - digits - 1)) && (index != digits) && (precision <= digits)){
				
				pnumber[i] = abs_snumber[index];
				index++;

			} else if ((i >= (length - digits - 1) && (index!= digits) && (precision > digits ))) {
				
				pnumber[i] = abs_snumber[index];
				index++;

			} else {

				pnumber[i] = '0';
			}
		}
	}	
	
	return pnumber;
}

/*extends the number according to separator*/
char
* separatorExtend(char *pnumber, char separator, int precision, long long number)
{
	/*get the digits*/
	long digits = getDigits(number);
	int thousands = (digits - precision - 1) / 3; 

	long length = strlen(pnumber) + thousands + 1;

	/*add separators*/
	char *spnumber = malloc(length);
	int index = 0; /*pnumber index*/
	long count = 0; /*spnumber digit count past the precision point*/
	
	spnumber[(length - 1)] = '\0';

	for(long i = (length - precision - 2); i > 0; i--){
		
		if(count == 4){
			spnumber[i] = separator;
			count = 0;
		}

		count ++;
	}

	/*copy pnumber into spnumber*/
	for(long i = 0; i < (length - 1); i++){
		if(spnumber[i] != separator){
			spnumber[i] = pnumber[index];
			index++;
		}
	}

	return spnumber;
}

void
printFixed(long long number, char separator, char decimalPoint, unsigned int precision)
{	
	/*get rid of the number sign*/
	long long absnumber = number;
	
	/*get the precision extended number*/
	char *pnumber = precisionExtend(absnumber, precision, decimalPoint);

	/*add the separators*/
	char *spnumber = separatorExtend(pnumber, separator, precision, number);

	/*check for a negative*/
	if(number < 0){
		putchar('-');
	}

	for (int i = 0; i < strlen(spnumber); i++){
		putchar(spnumber[i]);
	}
		
	/*free number variables*/
	free(pnumber);
	free(spnumber);
}
