#include <stdio.h>

#ifndef ROWS
#define ROWS 6
#endif

#ifndef COLS
#define COLS 7
#endif

#define CONNECT_N 4
#define CONNECT_THREE 3

/* Tokens */
#define EMPTY '.'
#define TOKEN_P1 'X'
#define TOKEN_P2 'O'

#define HUMAN 1
#define COMPUTER 2

#define NO_VERTICAL_MOVEMENT 0
#define DIAGONAL_MOVEMENT_RIGHT -1
#define DIAGONAL_MOVEMENT_LEFT 1

#define TRUE 1
#define FALSE 0

#define INVALID_ROW -1

/* Return 1 if yes 0 if no*/
int isColumnFull(char[][COLS], int, int);

/* Return 1 if yes 0 if no*/
int isBoardFull(char[][COLS], int, int);

/* Return 1 if yes 0 if no*/
int isInBounds(int, int, int, int);

/* Return index of row where token will land, or -1 if column full */
int getFreeRow(char[][COLS], int, int, int);

/* Place token in column (0-based). Return row index or -1 if illegal */
int makeMove(char[][COLS], int, int, int, char);

/* returns 1 if the player will win in the current move, if no returns 0 */
int checkVictory(char[][COLS], int, int, int, char);

/* Human player: asks repeatedly until a valid non-full column is chosen (0-based) */
int humanChoose(char[][COLS], int);

/* Computer */
int computerChoose(char[][COLS], int, int, char, char);

/* orgenize an array ib the computer column order rules */
void computerRowOrder(int[COLS], int);

/* function to check if there is a sequence move, if so returns 1 else returns 0 */
int checkDownwardsSequence(char[][COLS], int, int, int, int, char);

int checkHorizontalSequence(char[][COLS], int, int, int, int, char);

int checkDiagonalSequence(char[][COLS], int, int, int, int, char);

/* combines all the checks */
int checkGeneralSequence(char[][COLS], int, int, int, int, char);

/* checks a sequence in a general line on the board, can check diagonals using the vertical movment vriable */
int checkGeneralLineSequence(char[][COLS], int, int, int, int, int, int, char);

void runConnectFour(char[][COLS], int, int, int, int);

/* do the player turn stuff, returns 1 if the player won, else returns 0 */
int playerTurn(char[][COLS], int, int, int, int, char, char);

/* resets board */
void initBoard(char[][COLS], int, int);

void printBoard(char[][COLS], int, int);

int getPlayerType(int);


int main() {
    char board[ROWS][COLS];
    printf("Connect Four (%d rows x %d cols)\n\n", ROWS, COLS);
    int p1Type = getPlayerType(1);
    int p2Type = getPlayerType(2);
    initBoard(board, ROWS, COLS);
    printBoard(board, ROWS, COLS);
    runConnectFour(board, ROWS, COLS, p1Type, p2Type);
    return FALSE;
}

void runConnectFour(char board[][COLS], int rows, int cols, int p1Type, int p2Type){
    
    int isWinMove;
    while(TRUE){
        //player 1 turn
        isWinMove = playerTurn(board, rows, cols, p1Type, 1, TOKEN_P1, TOKEN_P2);
        printBoard(board, rows, cols);
        if (isWinMove){
            printf("Player 1 (%c) wins!", TOKEN_P1);
            break;
        }

        if(isBoardFull(board, rows, cols)){
            printf("Board full and no winner. It's a tie!");
            break;
        } 

        //player 2 turn
        isWinMove = playerTurn(board, rows, cols, p2Type, 2, TOKEN_P2, TOKEN_P1);
        printBoard(board, rows, cols);
        if (isWinMove){
            printf("Player 2 (%c) wins!", TOKEN_P2);
            break;
        }

        if(isBoardFull(board, rows, cols)){
            printf("Board full and no winner. It's a tie!");
            break;
        } 
    }
}

int playerTurn(char board[][COLS], int rows, int cols, int playerType, int playerNumber,
                char playerToken, char opponentToken){
    
    int isWinMove, playerChoice;
    printf("Player %d (%c) turn.\n", playerNumber, playerToken);
        switch (playerType){
            case HUMAN:
                playerChoice = humanChoose(board, cols);
                isWinMove = checkVictory(board, rows, cols, playerChoice, playerToken);
                makeMove(board, rows, cols, playerChoice, playerToken);
                break;

            case COMPUTER:
                playerChoice = computerChoose(board, rows, cols, playerToken, opponentToken);
                isWinMove = checkVictory(board, rows, cols, playerChoice, playerToken);
                makeMove(board, rows, cols, playerChoice, playerToken);
                printf("Computer chose column %d\n", playerChoice + 1);
                break;
        }
        return isWinMove;
}

int checkVictory(char board[][COLS], int rows, int cols, int nextMove, char playerToken){
    return checkGeneralSequence(board, rows, cols, nextMove, CONNECT_N, playerToken);
}

void printBoard(char board[][COLS], int rows, int cols) {
    printf("\n");
    for (int r = 0; r < rows; r++) {
        printf("|");
        for (int c = 0; c < cols; c++) {
            putchar(board[r][c]);
            printf("|");
        }
        printf("\n");
    }
    for (int c = 1; c <= cols; c++) {
        printf(" %d", c % 10);
    }
    printf("\n\n");
}

int getPlayerType(int playerNumber) {
    char ch;
    while (TRUE) {
        printf("Choose type for player %d: h - human, c - computer: ", playerNumber);
        int n = scanf(" %c", &ch);
        if (n != TRUE) {
            printf("Input error. Try again.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        if (ch == 'h' || ch == 'H') return HUMAN;
        if (ch == 'c' || ch == 'C') return COMPUTER;

        printf("Invalid selection. Enter h or c.\n");
        while (getchar() != '\n'); // clear rest of input
    }
}

int computerChoose(char board[][COLS], int rows, int cols, char playerToken, char opponentToken){
      
    int colCheckOrder[COLS];
    computerRowOrder(colCheckOrder, cols);

  
    //checks if player has a win move
    for(int i = 0; i < cols; i++){
        if(checkGeneralSequence(board, rows, cols, colCheckOrder[i], CONNECT_N, playerToken))
            return colCheckOrder[i];
    }


    //checks if opponent has a win move
    for(int i = 0; i < cols; i++){
        if(checkGeneralSequence(board, rows, cols, colCheckOrder[i], CONNECT_N, opponentToken))
            return colCheckOrder[i];
    }


    //checks if player has a sequence of three
    for(int i = 0; i < cols; i++){
        if(checkGeneralSequence(board, rows, cols, colCheckOrder[i], CONNECT_THREE, playerToken))
            return colCheckOrder[i];
    }


    //checks if opponent has a sequence of three
    for(int i = 0; i < cols; i++){
        if(checkGeneralSequence(board, rows, cols, colCheckOrder[i], CONNECT_THREE, opponentToken))
            return colCheckOrder[i];
    }


    //defult moves
    for(int i = 0; i < cols; i++){
        if(isInBounds(rows, cols, 0, colCheckOrder[i]) && !isColumnFull(board, cols, colCheckOrder[i]))
            return colCheckOrder[i];
    }
    return -1;
}

void computerRowOrder(int RowOrder[COLS], int cols){
    int startingCol = (cols - 1) / 2;

    if (cols % 2 != 0)
        for(int i = 0; i < cols; i++){
            startingCol = (i % 2 == 0)? (startingCol + i): (startingCol - i);
            RowOrder[i] = startingCol;
        }
    else
        for(int i = 0; i < cols; i++){
            startingCol = (i % 2 == 0)? (startingCol - i): (startingCol + i);
            RowOrder[i] = startingCol;
        }
    return;
}

int checkGeneralSequence(char board[][COLS], int rows, int cols, int colMove, int sequence, char playerToken){
    return (checkDownwardsSequence(board, rows, cols, colMove, sequence, playerToken) ||
            checkHorizontalSequence(board, rows, cols, colMove, sequence, playerToken) ||
            checkDiagonalSequence(board, rows, cols, colMove, sequence, playerToken));
}

int checkDownwardsSequence(char board[][COLS], int rows, int cols, int colMove, int sequence, char playerToken){
    int landRow = getFreeRow(board, rows, cols, colMove);

    if (landRow == INVALID_ROW)
        return FALSE;


    if (!isInBounds(rows, cols, landRow + (sequence - 1), colMove)){
        return FALSE;
    }

    for (int i = landRow + 1; i <= landRow + (sequence - 1); i++)
        if (board[i][colMove] != playerToken){
            return FALSE;
        }

    
    return 1;
}

int checkDiagonalSequence(char board[][COLS], int rows, int cols, int colMove, int sequence, char playerToken){
    
    int landRow = getFreeRow(board, rows, cols, colMove);

    if(landRow == INVALID_ROW)
        return FALSE;



    for(int i = 1; i <= sequence; i++){
        if(checkGeneralLineSequence(board,rows, cols, colMove, sequence, i, DIAGONAL_MOVEMENT_RIGHT,playerToken)){
            return TRUE;
        }
    }

    for(int i = 1; i <= sequence; i++){
        if(checkGeneralLineSequence(board,rows, cols, colMove, sequence, i, DIAGONAL_MOVEMENT_LEFT,playerToken)){
            return TRUE;
        }
    }

    return FALSE;
}

int checkHorizontalSequence(char board[][COLS], int rows, int cols, int colMove, int sequence, char playerToken){
    int landRow = getFreeRow(board, rows, cols, colMove);

    if (landRow == INVALID_ROW)
        return FALSE;


    for(int i = 1; i <= sequence; i++){
        if(checkGeneralLineSequence(board,rows, cols, colMove, sequence, i, NO_VERTICAL_MOVEMENT, playerToken)){
            return TRUE;
        }
    }

    return FALSE;
}

int checkGeneralLineSequence(char board[][COLS], int rows, int cols, int colMove, int sequence,
                            int placeInSequence, int vertMovement, char playerToken){

    int landRow = getFreeRow(board, rows, cols, colMove);
    int startingPlace = sequence - placeInSequence;


    if(landRow == INVALID_ROW)
        return FALSE;
    
    //goes through the wanted line and checks each spot to see if theres a sequence
    if (isInBounds(rows, cols, landRow + (startingPlace) * vertMovement,colMove + (startingPlace))
        && isInBounds(rows, cols, landRow - (placeInSequence - 1) * vertMovement,colMove - (placeInSequence - 1)))
        for(int i = landRow - (placeInSequence - 1) * vertMovement, j = colMove - (placeInSequence - 1);
            j <= colMove + (startingPlace); j++, i += vertMovement){

            if (j == colMove)
                continue;

            if(board[i][j] != playerToken)
                break;

            if ( (j == colMove + startingPlace) || ((j == colMove + startingPlace - 1)
                 && placeInSequence == sequence) ){
                return TRUE;
            }
        }

    return FALSE;
}

int isInBounds(int rows, int cols, int checkRow, int checkCol){
    return ((checkRow >= 0 && checkRow < rows) && (checkCol >= 0 && checkCol < cols));
}

void initBoard(char board[][COLS], int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            board[i][j] = EMPTY;
        }
    }
}

int isBoardFull(char board[][COLS], int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == EMPTY)
                return FALSE;
        }
    }
    return TRUE;
}

int humanChoose(char board[][COLS], int cols){
    int colChoice, isValid;
    while(TRUE) {
        printf("Enter column (1-%d): ", COLS);
        isValid = scanf(" %d", &colChoice);

        if (isValid != TRUE) {
            printf("Invalid input. Enter a number.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        if(!(colChoice >= 1 && colChoice <= cols)){
            printf("Invalid column. Choose between 1 and %d.\n", cols);
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        if(!isColumnFull(board, cols, colChoice - 1))
            return colChoice - 1; 

        printf("Column %d is full. Choose another column.\n", colChoice);
        while (getchar() != '\n'); // clear input buffer
    }
}

int makeMove(char board[][COLS], int rows, int cols, int colMove, char playerToken){
    int landRow = getFreeRow(board, rows, cols, colMove);

    if (landRow == INVALID_ROW)
        return landRow;

    board[landRow][colMove] = playerToken;
    return landRow;    
}

int isColumnFull(char board[][COLS], int cols, int checkCol){
    if (checkCol > cols - 1)
        return TRUE;
    return (board[0][checkCol] != EMPTY);
}

int getFreeRow(char board[][COLS], int rows, int cols, int colMove){
    if (cols <= colMove || colMove < 0)
        return INVALID_ROW;

    for (int i = rows - 1; i >= 0; i--) {
        if (board[i][colMove] == EMPTY)
            return i;
    }
    return INVALID_ROW;
}

