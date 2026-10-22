"""
Name: Peleg Sacher
ID: 333135440
Assignment: ex7 - Connect-N and Tic-Tac-Toe
*******************************************************************************
This program implements a customizable Connect-Four style game. It supports
dynamic board sizes and includes a specific Tic-Tac-Toe mode.
The AI logic uses a priority-based system to simulate and evaluate moves.
*******************************************************************************
"""

import random

# Global Constants (Section 2.0.5: UPPER_CASE)
EMPTY = '.'
P1_SYMBOL = 'X'
P2_SYMBOL = 'O'
TTT_P1_MARK = 'X'
TTT_P2_MARK = 'O'
MIN_DIM = 2
MAX_DIM = 100
TTT_SIZE = 3

# -----------------------------------------------------------------------------
# Configuration and Input Processing
# -----------------------------------------------------------------------------

def getDimensions():
    """
    Prompts the user for board dimensions. 
    Validates input is within [2, 100].
    """
    while True:
        try:
            # Added \n to inputs as requested
            inputRows = input("Enter number of rows\n").strip()
            if not inputRows: continue
            
            inputCols = input("Enter number of columns\n").strip()
            if not inputCols: continue
            
            numRows = int(inputRows) 
            numCols = int(inputCols) 
            
            if MIN_DIM <= numRows <= MAX_DIM and MIN_DIM <= numCols <= MAX_DIM:
                return numRows, numCols
            
            # Added \n to error message
            print(f"Dimensions must be between {MIN_DIM} and {MAX_DIM}.\n")
        except ValueError:
            print("Invalid input. Enter a number.\n")

def determineGameRules(numRows, numCols):
    """
    Determines sequence length and if Tic-Tac-Toe mode should trigger.
    """
    # Section 2.0.4: Boolean style naming for 'isTtt'
    if numRows == TTT_SIZE or numCols == TTT_SIZE:
        return 3, True
    
    if numRows == 2 or numCols == 2:
        return 2, False
    if numRows <= 5 or numCols <= 5:
        return 3, False
    if numRows <= 10 or numCols <= 10:
        return 4, False
    
    return 5, False

# -----------------------------------------------------------------------------
# Board Display and Win Detection
# -----------------------------------------------------------------------------

def printGameBoard(board, numRows, numCols, isTttMode=False):
    """
    Prints the grid with vertical bars.
    (No \n added here per instructions: "exepct the board one")
    """
    for rowList in board:
        # Construct the string for a single row
        rowString = "|" + "|".join(rowList) + "|"
        print(rowString)
    
    if not isTttMode:
        # Print column numbers for Connect-N
        colNums = [str(i + 1) for i in range(numCols)]
        print(" " + " ".join(colNums))

def isWinnerFound(board, numRows, numCols, symbol, sequenceN):
    """
    Section 2.0.4: Function name starts with 'is' for boolean return.
    Scans for N consecutive symbols in 4 directions.
    """
    # Horizontal scan
    for r in range(numRows):
        for c in range(numCols - sequenceN + 1):
            if all(board[r][c + i] == symbol for i in range(sequenceN)):
                return True
                
    # Vertical scan
    for r in range(numRows - sequenceN + 1):
        for c in range(numCols):
            if all(board[r + i][c] == symbol for i in range(sequenceN)):
                return True
                
    # Diagonal scans
    for r in range(numRows - sequenceN + 1):
        for c in range(numCols - sequenceN + 1):
            if all(board[r + i][c + i] == symbol for i in range(sequenceN)):
                return True
                
    for r in range(sequenceN - 1, numRows):
        for c in range(numCols - sequenceN + 1):
            if all(board[r - i][c + i] == symbol for i in range(sequenceN)):
                return True
                
    return False

# -----------------------------------------------------------------------------
# AI Logic
# -----------------------------------------------------------------------------

def getBestAiMove(board, numRows, numCols, aiSym, playerSym, n):
    """
    Evaluates moves based on 5 priorities using board simulation.
    Used for 's' (Strategic) computer.
    """
    center = (numCols - 1) / 2.0
    validCols = [c for c in range(numCols) if board[0][c] == EMPTY]
    
    # Sort valid columns by center proximity (Priority 5)
    validCols.sort(key=lambda x: (abs(x - center), x))

    def simulateMove(colIdx, sym):
        # Section 2.0.3: camelCase function
        for r in range(numRows - 1, -1, -1):
            if board[r][colIdx] == EMPTY:
                board[r][colIdx] = sym
                return r
        return -1

    # Priorities 1 & 2: Instant Win or Block Win
    for currentSym in [aiSym, playerSym]:
        for col in validCols:
            row = simulateMove(col, currentSym)
            if row != -1:
                isWin = isWinnerFound(board, numRows, numCols, currentSym, n)
                board[row][col] = EMPTY # Undo move
                if isWin:
                    return col

    # Priorities 3 & 4: Sequence creation/blocking (N-1)
    if n > 2:
        for currentSym in [aiSym, playerSym]:
            for col in validCols:
                row = simulateMove(col, currentSym)
                if row != -1:
                    isAlmostWin = isWinnerFound(board, numRows, numCols, currentSym, n - 1)
                    board[row][col] = EMPTY
                    if isAlmostWin:
                        return col

    return validCols[0]

def getRandomAiMove(board, numCols):
    """
    Simple Random AI for 'r' selection.
    """
    validCols = [c for c in range(numCols) if board[0][c] == EMPTY]
    if not validCols:
        return 0
    return random.choice(validCols)

# -----------------------------------------------------------------------------
# Game Loops
# -----------------------------------------------------------------------------

def runTicTacToe():
    """
    Special loop for 3x3 Tic-Tac-Toe mode.
    """
    print("Tic Tac Toe (Human vs Human)\n")
    
    board = [[EMPTY] * TTT_SIZE for _ in range(TTT_SIZE)]
    # turnInfo stores: (board_marker, player_number, message_symbol)
    turnInfo = [(TTT_P1_MARK, '1', P1_SYMBOL), (TTT_P2_MARK, '2', P2_SYMBOL)]
    turnIndex = 0
    
    printGameBoard(board, TTT_SIZE, TTT_SIZE, True)

    while True:
        marker, pNum, msgSym = turnInfo[turnIndex]
        try:
            # Added \n to input prompt
            userInput = input("Enter position (1-9): \n").strip()
            if not userInput: continue
            
            # Section 2.0.2: 'pos' is meaningful but short
            pos = int(userInput) - 1 
            if not (0 <= pos <= 8):
                # Added \n to error message
                print("Invalid position. Choose between 1 and 9.\n")
                continue
            
            r, c = divmod(pos, 3) 
            if board[r][c] != EMPTY: continue
                
            board[r][c] = marker
            printGameBoard(board, TTT_SIZE, TTT_SIZE, True)
            
            if isWinnerFound(board, TTT_SIZE, TTT_SIZE, marker, 3):
                # Added \n to win message
                print(f"Player {pNum} ({msgSym}) wins!\n")
                break
                
            # Check for full board (Tie)
            if all(cell != EMPTY for row in board for cell in row):
                # Added \n to tie message
                print("Board full and no winner. It's a tie!\n")
                break
            turnIndex = 1 - turnIndex
        except ValueError:
            print("Invalid input. Enter a number.\n")

def runConnectN(numRows, numCols, n):
    """
    Standard Connect-N game loop.
    """
    # Added \n to Header
    print(f"Connect Four - Or More [Or Less] ({numRows} rows x {numCols} cols, connect {n})\n")
    
    # Added \n to Player selection inputs
    p1Type = input("Choose type for player 1: h - human, r - random/simple computer, s - strategic computer: ").lower()
    p2Type = input("Choose type for player 2: h - human, r - random/simple computer, s - strategic computer: \n").lower()
    
    board = [[EMPTY] * numCols for _ in range(numRows)]
    playerData = [(P1_SYMBOL, "1", p1Type), (P2_SYMBOL, "2", p2Type)]
    turnIndex = 0
    printGameBoard(board, numRows, numCols)

    while True:
        sym, num, pType = playerData[turnIndex]
        # Added \n to Turn message
        print(f"Player {num} ({sym}) turn.\n")
        
        targetCol = -1
        if pType == 'h':
            while targetCol == -1:
                try:
                    # Added \n to Column input prompt
                    choice = input(f"Enter column (1-{numCols}): \n").strip()
                    if not choice: continue
                    val = int(choice)
                    if not (1 <= val <= numCols):
                        # Added \n to Error message
                        print(f"Invalid column. Choose between 1 and {numCols}.\n")
                    elif board[0][val - 1] != EMPTY:
                        # Added \n to Full column message
                        print(f"Column {val} is full. Choose another column.\n")
                    else:
                        targetCol = val - 1
                except ValueError:
                    print("Invalid input. Enter a number.\n")
        else:
            # Computer Logic
            oppSym = playerData[1 - turnIndex][0]
            if pType == 's':
                targetCol = getBestAiMove(board, numRows, numCols, sym, oppSym, n)
            else:
                targetCol = getRandomAiMove(board, numCols)
                
            # Added \n to Computer choice message
            print(f"Computer chose column {targetCol + 1}\n")

        # Drop the token
        for r in range(numRows - 1, -1, -1):
            if board[r][targetCol] == EMPTY:
                board[r][targetCol] = sym
                break
        
        printGameBoard(board, numRows, numCols)
        
        if isWinnerFound(board, numRows, numCols, sym, n):
            # Added \n to Win message
            print(f"Player {num} ({sym}) wins!\n")
            break
        if all(board[0][i] != EMPTY for i in range(numCols)):
            # Added \n to Tie message
            print("Board full and no winner. It's a tie!\n")
            break
        turnIndex = 1 - turnIndex

def main():
    """
    Main entry function to configure and start the game.
    """
    numRows, numCols = getDimensions()
    winSequence, isTttActive = determineGameRules(numRows, numCols)
    
    if isTttActive:
        runTicTacToe()
    else:
        runConnectN(numRows, numCols, winSequence)

if __name__ == "__main__":
    main()