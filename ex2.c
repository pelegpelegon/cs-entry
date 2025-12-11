/******************
Name: Peleg Sacher
ID: 333135440
Assignment: 2
*******************/

#include <stdio.h>

int main()
{
    
    int choice = 1;
    do 
    {
        // MAIN MENU LOOP
        do
        {
            if (choice > 6 || choice < 1)
                printf("\nInvalid option, please try again\n\n"); 

            printf("\nWelcome to our games, please choose an option:\n\n1. Ducky's Unity Game\n\n2. The Memory Game\n\n3. Professor Pat's Power Calculation\n\n4. The Duck Parade\n\n5. The Mystery of the Repeated Digits\n\n6. Good Night Ducks\n\n");
            scanf("%d", &choice); 
        }while(choice > 6 || choice < 1);

        switch(choice)
        {
            // TASK 1: Ducky's Unity Game
            case 1:
                int duckyDecimalNumber = 1, numOfOnes = 0;

                do
                {
                    if (duckyDecimalNumber <= 0)
                        printf("\nInvalid number, please try again\n\n");
                    
                    printf("please enter a positive number:\n\n");
                    scanf("%d", &duckyDecimalNumber);
                }while(duckyDecimalNumber <= 0);

                while(duckyDecimalNumber > 0)
                {
                    numOfOnes += (duckyDecimalNumber % 2);
                    duckyDecimalNumber /= 2;
                }

                printf("\nDucky earns %d corns\n\n", numOfOnes);

                break;

            // TASK 2: The Memory Game
            case 2:
                int numOfDucks = 1,doQUAK = 0;
                long int quakMemory = 0;
                do
                {
                    if (numOfDucks <= 0)
                        printf("\nInvalid number, please try again\n\n");
                    else
                        printf("please enter the number of ducks:\n\n");
                    scanf("%d", &numOfDucks);
                }while(numOfDucks <= 0);
    
                printf("\nyou entered %d ducks\n\n", numOfDucks);

                for(int i = 1; i <= numOfDucks; i++)//gets the quaks or sh..
                {    
                    do
                    {
                        if (doQUAK != 1 && doQUAK != 0)
                            printf("\nInvalid number, please try again\n\n");
                        else
                            printf("\nduck %d do QUAK? 1 for yes, 0 for no\n\n", i);
                        scanf("%d", &doQUAK);
                    }while(doQUAK != 1 && doQUAK != 0);
                    quakMemory = quakMemory | doQUAK<<(i-1);
                } 
                
                for(int i = 1; i <= numOfDucks; i++)//prints the quaks and shs
                {    
                    doQUAK = quakMemory & 1<<(i - 1);
                    doQUAK = doQUAK>>(i-1);
                    if(doQUAK)
                        printf("duck number %i do Quak\n\n",i);
                    else
                        printf("duck number %i do Sh...\n\n", i);
                }
                break;

            // TASK 3: Professor Pat's Power Calculation
            case 3:
                int number = 1, exponent = 1, power = 1;
                do//gets number
                {
                    if (number < 0)
                        printf("\nInvalid number, please try again\n\n");
                    else
                        printf("please enter the number\n\n");
                    scanf("%d", &number);
                }while(number < 0);

                do//gets exponent
                {
                    if (exponent < 0)
                        printf("\nInvalid number, please try again\n\n");
                    else
                        printf("\nplease enter the exponent\n\n");
                    scanf("%d", &exponent);
                }while(exponent < 0);

                for(;exponent > 0; exponent--)
                    power *= number;

                printf("\nyour power is: %d\n\n", power);
                break;

            // TASK 4: The Duck Parade
            case 4:
                int numOfPrintDucks = 0;
                do
                {
                    if (numOfPrintDucks < 0)
                        printf("\nInvalid number, please try again\n\n");
                    else
                        printf("\nplease enter number of ducks:\n\n");
                    scanf("%d", &numOfPrintDucks);
                }while(numOfPrintDucks < 0);

                while(numOfPrintDucks > 0)
                {
                    for(int i = 1; i <= numOfPrintDucks && i<=10; i++)
                        printf("   _       ");
                    printf("\n");
                    for(int i = 1; i <= numOfPrintDucks && i<=10; i++)
                        printf("__(o)>     ");
                    printf("\n");
                    for(int i = 1; i <= numOfPrintDucks && i<=10; i++)
                        printf("\\___)      ");
                    printf("\n");
                    numOfPrintDucks -= 10;
                }
                break;

            // TASK 5: The Mystery of the Repeated Digits
            case 5:
                int currentDigit, mysteryNumber = 1, digitsMemory = 0;
                do
                {
                    if (mysteryNumber <= 0)
                        printf("\nInvalid number, please try again\n\n");
                    else
                        printf("\nplease enter number\n\n");
                    scanf("%d", &mysteryNumber);
                }while(mysteryNumber <= 0);

                while(mysteryNumber > 0)
                {
                    currentDigit = mysteryNumber % 10;

                    if (digitsMemory & 1<<currentDigit)
                        printf("\n%d appears more than once!\n\n", currentDigit);

                    digitsMemory = digitsMemory | 1<<currentDigit;
                    mysteryNumber /= 10;
                }
                break;

            // TASK 6: EXIT
            case 6:
                printf("Good night! See you at the pond tomorrow.\n\n");
                break;

            default: break;
        }

    } while(choice != 6);
    

    
    return 0;
}
