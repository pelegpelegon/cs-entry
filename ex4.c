#include <stdio.h>
#include <string.h>

/*******************
| * Peleg Sacher
| * 333135440
| * Assignment 4
|******************/

/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6


/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3

/***************************
**** GENERAL PARAMETERS ****
****************************/
#define TRUE 1
#define FALSE 0

#define NOT_PALINDROME_CHAR '\n'


#define RECURSING_OBJECTS 1
#define RECURSING_VERBS 2
#define RECURSING_SUBJECTS 3


#define EMPTY 0
/***************************
*** ZIP PUZZLE PARAMETERS **
****************************/

#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'
#define LAST_TILE 'X'

/***************************
* USER INTEFACE PROTOTYPES *
****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();


/****************************
* IMPLEMENTATION PROTOTYPES *
*****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM+1], int,
                                          char[][LONGEST_TERM+1], int,
                                          char[][LONGEST_TERM+1], int);

int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     int, int, int, int);

int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);


/******************************
* HELPER FUNCTIONS PROTOTYPES *
*******************************/

int readTerms(char[][LONGEST_TERM+1], int, char[]);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);
int isInBounds(int, int, int);
int cleanBuffer();

void task1ReversePhraseRecursion();
int task2CheckPalindromeRecursion(int, int);
void task3GenerateSentencesRecursion(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int,
                                     char[][LONGEST_TERM+1], int, int, int, int, int, int);

int task4SolveZipBoardRecursion(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                int, int, int, int, int, int);

int task5SolveSudokuRecursion(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int, int);

int isSudokuMoveValid(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int, int);
int sudokuCheckRow(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int);
int sudokuCheckCol(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int);
int sudokuCheckSubgrid(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int, int, int);

/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}


/***************************
****** USER INTERFACE ******
****************************/


void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}


void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}


void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount=readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount=readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount=readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}


void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest=0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if(board[i][j]>highest){
                highest=board[i][j];
            }
        }
    }
    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}


void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board))
    {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }
}


/***************************
********* HELPERS **********
****************************/


int readTerms(char terms[][LONGEST_TERM+1], int maxNumOfTerms, char type[]){
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if(termsCount < 1 || termsCount > maxNumOfTerms){
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for(int i=0;i<termsCount;i++){
        printf("%d. ",i+1);
        scanf(" %[^\n]",terms[i]);
    }
    return termsCount;
}


void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+-------+\n");
    }
}

/***************************
*********** TODO ***********
****************************/


void task1ReversePhraseImplementation(){
    char firstChar;
    scanf("%c", &firstChar);
    printf("\nThe reversed phrase is:\n");

    task1ReversePhraseRecursion();

    //prints the char that was lost in scanf
    printf("%c", firstChar);
}


void task1ReversePhraseRecursion(){
    int character;
    character = getchar();
    if(character != '\n'){
        task1ReversePhraseRecursion();
        printf("%c", character);
    }
}


int task2CheckPalindromeImplementation(int length){
    char firstChar;
    int distenceFromPhraseMiddle = length/2 - 1;
    int isEven = (length % 2 == 0)? 1:0;
    int isPalindrome;
    /* plus one to account for the \0 in a string */

    scanf("%c", &firstChar);
    isPalindrome = (firstChar == task2CheckPalindromeRecursion(distenceFromPhraseMiddle, isEven));
    /*
    in case its not a palindrome and the recursive function is cut early
    the buffer wont be empty when it ends 
    */
    cleanBuffer();
    return isPalindrome;
}

int task2CheckPalindromeRecursion(int distenceFromPhraseMiddle, int isEven){
    int curChar = getchar();
    if((distenceFromPhraseMiddle == 0) && isEven)
        return curChar;

    if((distenceFromPhraseMiddle == 0) ||
        (curChar == task2CheckPalindromeRecursion(distenceFromPhraseMiddle - 1, isEven)))
        return getchar();

    else{
        return NOT_PALINDROME_CHAR;
    }
}

int cleanBuffer(){
    int chr = getchar();
    if(chr == '\n')
        return TRUE;
    return cleanBuffer();
}

void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM+1], int subjectsCount,
                                          char verbs[][LONGEST_TERM+1], int verbsCount,
                                          char objects[][LONGEST_TERM+1], int objectsCount){
    task3GenerateSentencesRecursion(subjects, subjectsCount, verbs, verbsCount,
                                    objects, objectsCount, RECURSING_SUBJECTS, 0, 0, 0, 1);
}


void task3GenerateSentencesRecursion(char subjects[][LONGEST_TERM+1], int subjectsCount, char verbs[][LONGEST_TERM+1],
                                     int verbsCount, char objects[][LONGEST_TERM+1], int objectsCount,
                                     int recursiveType, int subject, int verb, int object, int count){
    switch(recursiveType){
        case RECURSING_OBJECTS:
            printf("%d. %s %s %s\n", count, subjects[subject], verbs[verb], objects[object]);

             /* if not last object goes to the next one */
            if(object != objectsCount - 1)
                task3GenerateSentencesRecursion(subjects, subjectsCount, verbs, verbsCount,
                                                objects, objectsCount, recursiveType, subject,
                                                verb, object + 1, count + 1);
            break;
        
        case RECURSING_VERBS:
            /* runs through the subjects for this verb */
            task3GenerateSentencesRecursion(subjects, subjectsCount, verbs, verbsCount,
                                            objects, objectsCount, RECURSING_OBJECTS, subject,
                                            verb, 0, count);

            /* if not last verb goes to the next one */
            if(verb != verbsCount - 1)
            {
                count += objectsCount;
                task3GenerateSentencesRecursion(subjects, subjectsCount, verbs, verbsCount,
                                                objects, objectsCount, RECURSING_VERBS, subject,
                                                verb + 1, object, count);
            }
            break;

        case RECURSING_SUBJECTS:
            /* runs through the verbs for this subject */
            task3GenerateSentencesRecursion(subjects, subjectsCount, verbs, verbsCount,
                                            objects, objectsCount, RECURSING_VERBS, subject,
                                            0, object, count);

            /* if not last subject goes to the next one */
            if(subject != subjectsCount - 1)
            {
                count += objectsCount * verbsCount;
                task3GenerateSentencesRecursion(subjects, subjectsCount, verbs, verbsCount,
                                                objects, objectsCount, RECURSING_SUBJECTS, subject + 1,
                                                verb, object, count);
            }
            break;

        default: break;

    }
}


int task4SolveZipBoardImplementation(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     int size, int startR, int startC, int highest){
    return task4SolveZipBoardRecursion(board, solution, size, startR, startC, highest, 1, 1);
}


int task4SolveZipBoardRecursion(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                int size, int placeR, int placeC, int highest, int currentCount, int MoveCount){
    /* to put back the value that was changed on the board to mark that i was already there */
    int oldValue; 
    if(!isInBounds(size, placeR, placeC)){
        return FALSE;
    }

    if(board[placeR][placeC] > currentCount + 1){
        return FALSE;
    }

    if(board[placeR][placeC] == highest){
        if(MoveCount == size * size){
            return TRUE;
        }
        else{
            return FALSE;
        }
    }

    if(board[placeR][placeC] == currentCount + 1){
        currentCount++;
    }


    oldValue = board[placeR][placeC];
    board[placeR][placeC] = highest + 1;

    /* checks up */
    if(task4SolveZipBoardRecursion(board, solution, size, placeR - 1, placeC, highest, currentCount, MoveCount + 1)){
        solution[placeR][placeC] = UP;
        return TRUE;
    }

    /* checks down */ 
    if(task4SolveZipBoardRecursion(board, solution, size, placeR + 1, placeC, highest, currentCount, MoveCount + 1)){
        solution[placeR][placeC] = DOWN;
        return TRUE;
    }

    /* checks left */
    if(task4SolveZipBoardRecursion(board, solution, size, placeR, placeC - 1, highest, currentCount, MoveCount + 1)){
        solution[placeR][placeC] = LEFT;
        return TRUE;
    }

    /* checks right */
    if(task4SolveZipBoardRecursion(board, solution, size, placeR, placeC + 1, highest, currentCount, MoveCount + 1)){
        solution[placeR][placeC] = RIGHT;
        return TRUE;
    }

    board[placeR][placeC] = oldValue;
    return FALSE;
    
}


int isInBounds(int size, int placeR, int placeC){
    return (placeC >= 0) && (placeR >= 0) && (placeC <= size - 1) && (placeR <= size - 1);
}




int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{ 
    return task5SolveSudokuRecursion(board, 0, 0, 1);
}


int task5SolveSudokuRecursion(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int curRow, int curCol, int placedValue){
    
    int nextRow, nextCol;
    
    /* if finished going through the entire board */ 
    if(curRow >= SUDOKU_GRID_SIZE)
        return TRUE;

    /* 
        if tries all the options in a value
        and all failed returns false
    */
    if(placedValue > 9){
        return FALSE;
    }

    
    nextCol = ((curCol + 1) == SUDOKU_GRID_SIZE)? 0:(curCol + 1);

    nextRow = (nextCol == 0)? (curRow + 1): curRow;

    /* if tile isn't empty goes to the next one */
    if(board[curRow][curCol] != EMPTY){
        return task5SolveSudokuRecursion(board, nextRow, nextCol, 1);
    }

    /* 
       check if the move is valid,
       if so makes it and moves on to the next tile
    */
    if(isSudokuMoveValid(board, placedValue, curRow, curCol)){
        board[curRow][curCol] = placedValue;

        if(task5SolveSudokuRecursion(board, nextRow, nextCol, 1))
            return TRUE;

        /* 
           back tracking if the decision tree returns false
           and then tries the next value in this tile 
        */
        board[curRow][curCol] = EMPTY;
    }

    return task5SolveSudokuRecursion(board, curRow, curCol, placedValue + 1);
}


/* checks if the move the computer going to make will be valid */
int isSudokuMoveValid(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int valueToCheck, int row, int col){

    int subgridFirstRow, subgridFirstCol;

    subgridFirstRow = (row / SUDOKU_SUBGRID_SIZE) * SUDOKU_SUBGRID_SIZE;
    subgridFirstCol = (col / SUDOKU_SUBGRID_SIZE) * SUDOKU_SUBGRID_SIZE;

    return sudokuCheckRow(board, row, valueToCheck) &&
           sudokuCheckCol(board, col, valueToCheck) &&
           sudokuCheckSubgrid(board, valueToCheck, subgridFirstRow, subgridFirstCol);
}


/* checks if there is a specific value in a row */ 
int sudokuCheckRow(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int rowToCheck, int valueToCheck){
    if( (board[rowToCheck][0] == valueToCheck) ||
        (board[rowToCheck][1] == valueToCheck) ||
        (board[rowToCheck][2] == valueToCheck) ||
        (board[rowToCheck][3] == valueToCheck) ||
        (board[rowToCheck][4] == valueToCheck) ||
        (board[rowToCheck][5] == valueToCheck) ||
        (board[rowToCheck][6] == valueToCheck) ||
        (board[rowToCheck][7] == valueToCheck) ||
        (board[rowToCheck][8] == valueToCheck))
        return FALSE;

    return TRUE;
}


/* checks if there is a specific value in a colunm */
int sudokuCheckCol(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int colToCheck, int valueToCheck){
    if( (board[0][colToCheck] == valueToCheck) ||
        (board[1][colToCheck] == valueToCheck) ||
        (board[2][colToCheck] == valueToCheck) ||
        (board[3][colToCheck] == valueToCheck) ||
        (board[4][colToCheck] == valueToCheck) ||
        (board[5][colToCheck] == valueToCheck) ||
        (board[6][colToCheck] == valueToCheck) ||
        (board[7][colToCheck] == valueToCheck) ||
        (board[8][colToCheck] == valueToCheck))
        return FALSE;

    return TRUE;
}


/* checks if there is a specific value in a subgrid */
int sudokuCheckSubgrid(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int valueToCheck,
                       int subgridFirstRow, int subgridFirstCol){
    /* 
       checks if any of the boxes in the subgrid has the checked value 
       (not brilliant but fast enough and it does the job)
    */
    if( (board[subgridFirstRow][subgridFirstCol] == valueToCheck)         ||
        (board[subgridFirstRow][subgridFirstCol + 1] == valueToCheck)     ||
        (board[subgridFirstRow][subgridFirstCol + 2] == valueToCheck)     ||
        (board[subgridFirstRow + 1][subgridFirstCol] == valueToCheck)     ||
        (board[subgridFirstRow + 1][subgridFirstCol + 1] == valueToCheck) ||
        (board[subgridFirstRow + 1][subgridFirstCol + 2] == valueToCheck) ||
        (board[subgridFirstRow + 2][subgridFirstCol] == valueToCheck)     ||
        (board[subgridFirstRow + 2][subgridFirstCol + 1] == valueToCheck) ||
        (board[subgridFirstRow + 2][subgridFirstCol + 2] == valueToCheck))
        return FALSE;

    return TRUE;
}
