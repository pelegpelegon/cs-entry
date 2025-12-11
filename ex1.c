/******************
Name: Peleg Sacher
ID: 333135440
Assignment: 
*******************/
#include <stdio.h>

// REMIDER : YOU CANT USE ANY CONTROL FLOW OPERATIONS OR FUNCTIONS, ONLY BITWISE. not even "==, &&, ||, !="

int main()
{

    // Ascii
    
    printf("Ascii:\n");
    char character;
    int isOdd;
    printf("Please enter a character\n");
    scanf(" %c", &character);
    printf("Its numerical value is: %d\n", character);
    isOdd = character;
    isOdd = isOdd & 1;
    printf("0 for even, 1 for odd: %d\n", isOdd);
    /*. Scan one character from the user.
        Then, refer to it as an integer.
        a. Print its value.
        b:
        Print “0”, if its integer representation is even.
        print “1” if its integer representation is odd. */

    // 2's complement and other representations
    
    printf("\n2's complement to other representations:\n");
    int numGivenEx2, OnesCom;
    printf("Please enter a negative integer\n");
    scanf("%d", &numGivenEx2);
    OnesCom = -(~numGivenEx2); //multiplying minus on to turn the number back into negative
    printf("1's complement: %d\n", OnesCom);
    printf("unsigned: %u\n", numGivenEx2);
    
    /*. Scan a negative integer. [2’s complement].
        Print its value in 1’s complement.
        Print its value as unsigned. */

    // Shifting right and left
    
    printf("\nShifting right and left:\n");
    int numGivenEx3, rightShift, leftShift;
    printf("Please enter 3 integers\n");
    scanf("%d%d%d", &numGivenEx3, &rightShift, &leftShift);
    numGivenEx3 = numGivenEx3>>rightShift;
    numGivenEx3 = numGivenEx3<<leftShift;
    printf("After shifting right and left: %d\n", numGivenEx3);
    
    /*. Scan 3 integers.
        The first one - the value you will play with.
        The second and the third - how much to shift right and left, respectively.
        Print the value after shifting right and then shifting left. */

    // Even - Odd
    
    printf("\nEven - Odd:\n");
    int num1, num2, num3, mostOddOrEven;
    printf("Please enter 3 integers\n");
    scanf("%d%d%d", &num1, &num2, &num3);
    //getting the first bit of the numbers given to check if the absolute value is odd or even (1 - odd, 0 - even)
    num1 = num1 & 1;
    num2 = num2 & 1;
    num3 = num3 & 1;
    mostOddOrEven = (num1 & num2) | (num2 & num3) | (num3 & num1); // checks if theres an option where two of the numbers, now representing odd or even are 1
    printf("0 - most of them are even, 1 - most of them are odd: %d\n", mostOddOrEven);
    /* Scan 3 Integers.
    If at least two of them are even - print 0.
    If at least two of them are odd - print 1. */

    // Different Bases
    
    printf("\nDifferent Bases:\n");
     unsigned int octal, hexadecimal, octalLSB, octalMSB, hexadecimalLSB, hexadecimalMSB;
    printf("Please enter two numbers in octal and hexadecimal bases\n");
    scanf("%o%x", &octal, &hexadecimal);

    hexadecimalLSB = hexadecimal & 1;
    octalLSB = octal & 1;
    printf("LSBs: %d %d\n", octalLSB, hexadecimalLSB);

    hexadecimalMSB = hexadecimal & 0xF0000000;
    hexadecimalMSB = hexadecimalMSB>>31;

    octalMSB = octal & 070000000000;
    octalMSB = octalMSB>>31;
    printf("MSBs: %d %d\n", octalMSB, hexadecimalMSB);
    /*  Scan two numbers:
        One in octal base, one in Hexadecimal base.
        Print their LSB’s.
        Print their MSB’s. */

    printf("Bye!\n");
    return 0;
}
