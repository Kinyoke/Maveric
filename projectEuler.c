#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "projectEuler.h"

/*
*@Author: (Faisal Burhan).
*@Date: (26 | March | 2018 ).
*This program is intended for practicing math solving skills
*presented by https://projecteuler.net.
*HOW IT WORKS.
*The program takes a given number of parameters to perfom a certain procedure
*1.First parameter to be given is an instruction number that points to which 
*  instruction should be performed to the rest of peremeters specified.
*2.These parameter are variable(s) list or data feed into the program.
*  [for the next increment of the program, several action will be added such as output file generation, etc.]  
*/

static char argument[255];
int result;
String instruction[1000] = {
	"List all the natural numbers below (N) that are multiples of (a) or (b) and sum of these multiples.",
	"By considering the terms in the Fibonacci sequence whose values do not exceed (n), where n <= n*10**20, find the sum of the even-valued terms.",
	"What is the largest prime factor of the number 600851475143 ?",
	"Find the largest palindrome made from the product of two 3-digit numbers.",
	"Enter a number (N), to find out if the number is even, odd or prime."
};

int main(int argc, char const *argv[])
{
	if (argc < 2)displayMenu(instruction);
	strcpy(argument, ((argv[1] != NULL)? argv[1] : "null"));
	if ((strcmp("help",argument)) == 0)displayMenu(instruction);
	if (argv[1] != NULL)
	{
		switch(strtol(argv[1],NULL,10)){
		case 1:
			result = sum_multiples_of_a_number(strtol(argv[2],NULL,10),strtol(argv[3],NULL,10),strtol(argv[4],NULL,10));
			printf("sum = %d\n", result);
		break;
		case 2:
			/*	screen log showing anomoly in the data where given fib-number execeeds 92.
				91:  7 540 113 804 746 346 429
				92: 12 200 160 415 121 876 738 
				93:  1 293 530 146 158 671 551 //anomoly
				94: 13 493 690 561 280 548 289
				95: 14 787 220 707 439 219 840
				96:  9 834 167 195 010 216 513
				97:  6 174 643 828 739 884 737
				98: 16 008 811 023 750 101 250
				99:  3 736 710 778 780 434 371
				100: 1 298 777 728 820 984 005

         MIN_R_THRESHOLD =    40 000 000 000 000 000 000
				   MIN_R =     3 770 056 902 373 173 214
		 MAX_R_THRESHOLD = 4 000 000 000 000 000 000 000 
				   MAX_R =    15 970 217 317 495 049 952
			*/
			printf("non_rec_results: %llu rec_results: %llu\n", non_rec_fibonacci(strtol(argv[2],NULL,10)));
			//sum_of_even_infibseq(strtol(argv[2],NULL,10),strtol(argv[3],NULL,10));
		break;
		case 3:
			get_primeFactor(strtol(argv[2],NULL,10)); //600851475143
		break; 
		case 4:
			 if (isPrime(strtol(argv[2],NULL,10)) == true) { 
			 	printf("%s\n", "The given number is Prime!"); 
			 }else if (isOdd(strtol(argv[2],NULL,10)) == true) { printf("%s\n", "The given number is Odd"); }
			  else if (isEven(strtol(argv[2],NULL,10)) == true) { printf("%s\n", "The given number is Even!"); }
		break;
	}
	}
	return 0;
}

void displayMenu(String *inst){
	printf("%s\n%s\n%s\n\n\n", "Welcome to compute de engine powered by the maven e-library.","copyright (c) 2018 maven inc","Dev by Ultraman.");
	printf("%s\n\n","Instructions		[ inststr: ./progname instno param1 pramn... ]");
	for (int i = 0; i < 5; ++i)
	{
		printf("%d: %s\n",i+1, instruction[i]);
	}
}

int sum_multiples_of_a_number(int a, int b, int range){
	int sum = 0;
	for (int i = 0; i < range; ++i)
		if ((i > 0 && i%a == 0) || (i > 0 && i%b == 0)){ sum+=i; printf("%d\n", i);}
	return sum;
}
static long unsigned int rec_fibonacci(int number){
 	if (number == 0) return 0;
 	else if (number == 1) return 1;
 	else return rec_fibonacci(number-1)+rec_fibonacci(number-2);
}

long long unsigned int non_rec_fibonacci(int number){
	long unsigned int prev = 0, next = 1, res = 0;
	for (int i = 1; i < number; ++i)
	{
		res = prev + next;
		prev = next;
		next = res;
	}
	return res;
}


void sum_of_even_infibseq(int data, long long unsigned int limit){
	long long unsigned int even = 0;
	for (int i = 1; i < data+1; ++i)
	{
		if (even < limit) even = (non_rec_fibonacci(i)%2 == 0)? even+=non_rec_fibonacci(i) : even;
	}
	printf("Answer: sum of even numbers in the given fibonacci sequence less than %llu = %llu\n", limit, even);
}

int get_primeFactor(long unsigned int number){
	int val = 0, result[100];
	long unsigned int n = 2;
	for (long unsigned int i = 3; i < number; i+=2)
	{
		if (number % i == 0 && i < number) { 
			//val = i; //printf("i: %llu val: %llu \n", i, val);
			for (int j = 0; j < 3; ++j)
			{
				result[j] = i;
			}
			//if (result < number)
			//{
				//result = val;
				//printf("%d \n", i);
			//}
		}  
	}
	return n;
}
long unsigned int getPrimes(long unsigned int number){ 
	long unsigned int val = 2;
	for (int i = 2; i < number; i++){ if (isPrime(i) == true) val = i; }
	return val; 
}
boolean isPrime(long unsigned int n){
	if (n % 2 == 0) return false;
	for (long unsigned int i = 3; 1 * i < n; i+=2) { if (n % i == 0) return false; }
	return true; 
} 
int getOdds(long unsigned int number){ int val = 0; val = (number%2 > 0)? val = number : val; return val; }
boolean isOdd(long unsigned int n){ if (n % 3 == 0) return true; }
int getEvens(long unsigned int number){ int val = 0; val = (number%2 == 0)? val = number : val; return val; }
boolean isEven(long unsigned int n){ if (n % 2 == 0) return true; }