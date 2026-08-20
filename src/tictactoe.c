//Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//Board Structure
typedef struct {//Provided
    char board[3][3];//Creates 3x3 Grid for TicTacToe board
    char current_player;
} TicTacToeBoard;

//Function Prototypes
// Function Prototype to display the Tic Tac Toe board
void display_board(TicTacToeBoard* board);

// Function Prototype to initialize the Tic Tac Toe board with empty cells
void initialize_board(TicTacToeBoard* board);

// Function Prototype to make a move on the Tic Tac Toe board
int make_move(TicTacToeBoard* board, int row, int col);

// Function Prototype to check if a player has won
int check_win(TicTacToeBoard* board, char player);

// Function Prototype to check if the game is a draw
int check_draw(TicTacToeBoard* board);

// Function Prototype to save the game state to a file
void save_board_to_file(TicTacToeBoard* board, char* file_path);

// Function Prototype to load the game state from a file
void load_board_from_file(TicTacToeBoard* board, char* file_path);


int main() {
    char* file_path = "tic_tac_toe_board.txt";//File Name Variable
    TicTacToeBoard board;//Board Structure Reference Variable
    
    //Title Card, not necessary just seemed nice.
    printf("-- ================== --\n");
    printf("      Tic Tac Toe     \n");
    printf("-- ================== --\n");

    //Player Name input block
    char player1[50], player2[50];
    printf("Enter Player 1 name: \n");
    scanf("%s", player1);
    printf("Enter Player 2 name: \n");
    scanf("%s", player2);

    //Load Previous Game? 
    char choice;
    printf("Do you want to continue the previous game? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        load_board_from_file(&board, file_path);
        printf("Loaded the previous game board:\n");
        display_board(&board);
    }
   else if (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {//Error Handling Keeps User from entering unacceptable value.
        printf("That is not a valid option.\n");
        return 1;//Terminates program with error message.
    }
   else if (choice == 'n' || choice == 'N') {
    initialize_board(&board);//Calls the function to init. the board.||Step 1
    printf("In that case, %s will go first and they will be %c\n", player1, board.current_player);//Tells players who goes first and their icon
    display_board(&board);//Calls Display Function to help Visualize Options for Player.
    }

    //Gameplay Section
    int row, col;//Position Variables.
    while (1) {
        printf("Where would you like to move to? Please indicate the row and the column.\n ");
        printf("Ensure that there are commas between the numbers and remember to use (X,Y) format.\n");
        scanf("%d, %d", &row, &col);//Takes Ordered Pair from User and uses that as the move || Step 2.
        
        /* 3. Check if valid move using make_move
        Provided: use similar method for the rest.
        Creates variable move_result and sets it to hold the value of one or zero contingent on outcome of UDF make_move*/

        int move_result = make_move(&board, row, col);

        if (move_result == 0) {//Error Handling Prevents the user from overwriting a players move or being out of bounds.
            printf("Cell is already occupied or invalid input. Try again.\n");
            continue;
        } 

        printf("\n");//New Line to improve clarity.

        display_board(&board);//Calls Display Board UDF || Step 4.
        
        save_board_to_file(&board, file_path);//Saves Board after each turn. || Step 5.

        // Checks if Win/Draw Conditions are met || Step 6.
        int player_won = check_win(&board, 'X');
        
        if (player_won == 1) {
            printf("Congratulations, %s, you have won the game!\n", player1);//Player 1 victory message
            break;
        }
        int opponent_won = check_win(&board, 'O');
        if (opponent_won == 1) {
            printf("Congratulations, %s, you have won the game!\n", player2);//Player 2 victory message
            break;
        }
        int is_draw = check_draw(&board);
        if (player_won == 0 && opponent_won == 0 && is_draw == 1) {
            printf("It's a draw!\n");//Draw Message
            break;
        }

        //Swaps player
        if (board.current_player == 'X') {
            board.current_player = 'O';
        }
        else if ((board).current_player == 'O') {
            board.current_player = 'X';
        }
        printf("It is now %c's turn.", board.current_player);//Displays the current player after each turn
    }
    return 0;
}



// Function to display the Tic Tac Toe board
void display_board(TicTacToeBoard* board) {
    printf("  0   1   2\n");//Displays X coordinate label || Makes Gameplay experience better for the end user
    for (int row = 0; row < 3; row++) {
        printf("%d ", row);  //Displays Y coordinate label || Makes Gameplay experience better for the end user
        for (int col = 0; col < 3; col++) {
            printf(" %c ", (*board).board[row][col]);//Places the relevant character and gives the proper spacing
            if (col < 2) {
                printf("|"); //Creates Vertical borders
            }
        }
        printf("\n");//Brings the cursor down a line.
        if (row < 2) {
            printf("-------------\n"); //Creates Horizontal borders
        }
    }

    printf("\n");//Allows the game to continue on a new line without interfering with the board
}

// Function to initialize the Tic Tac Toe board with empty cells
void initialize_board(TicTacToeBoard* board) {
       for (int i = 0; i < 3; i++) {//Iterates through the rows
        for (int j = 0; j < 3; j++) {
            (*board).board[i][j] = ' ';
        }
    }
       srand(time(NULL));//Seeding RNG Machine
    if (rand() % 2 == 0) {//Flips Coin, Returns 1 or 0 and sets the character accordingly
        (*board).current_player = 'X';//Sets Current Player to X
    }
    else {
        (*board).current_player = 'O';//Sets Current Player to O
    }
}

// Function to make a move on the Tic Tac Toe board
int make_move(TicTacToeBoard* board, int row, int col) {
    if (row > 2 || row < 0 || col > 2 || col < 0 || (*board).board[row][col] != ' ') {//Error Handling - Returns Error Notif. to main
        return 0;//Sets move_result to zero which notifies of an error
    }
    else {
        (*board).board[row][col] = (*board).current_player;//Sets the value of that spot to the current player token
    }
    return 1;//Returns success value to main. 
}

// Function to check if a player has won
int check_win(TicTacToeBoard* board, char player) {
   
    for (int i = 0; i < 3; i++) {//Increases 'i' to allow the program to move around the board.
        //Checking Rows
        if ((*board).board[i][0] == player && (*board).board[i][1] == player && (*board).board[i][2] == player) {
            return 1;
        }
        //Checking Columns
        if ((*board).board[0][i] == player && (*board).board[1][i] == player && (*board).board[2][i] == player) {
            return 1;
        }
    }
    //Checking Diagonals (L -> R)
    if ((*board).board[0][0] == player && (*board).board[1][1] == player && (*board).board[2][2] == player) {
        return 1;
    }
    //Checking Diagonals (R -> L)
    if ((*board).board[0][2] == player && (*board).board[1][1] == player && (*board).board[2][0] == player) {
        return 1;
    }
    return 0; //Win Conditions not met.
}

// Function to check if the game is a draw
int check_draw(TicTacToeBoard* board) {
    
    int  draw_counter = 0;//Draw flag. 

    for (int i = 0; i < 3; i++) {//Iterates through Rows
        for (int j = 0; j < 3; j++) {//Iterates Through Columns
            if ((*board).board[i][j] != ' ') {
                draw_counter++;
            }
        }
    }
    if (draw_counter == 9) {//There are 9 total slots therefore Draw_Counter must equal 9
        return 1;
    }
    else {
        return 0;
    }
}

// Function to save the game state to a file
void save_board_to_file(TicTacToeBoard* board, char* file_path) {

    FILE* file = fopen(file_path, "w");//Opens file in 'Write' mode

    if (file == NULL) {//Error Handling - Ensures file opens successfully.
        printf("There was an error saving progress\n");
        return;
    }

    fprintf(file, "%c\n", (*board).current_player);//Save the current player to file. Can boot up later
    

    for (int row = 0; row < 3; row++) {//Rows
        for (int col = 0; col < 3; col++) {//Columns

            char move = (*board).board[row][col];//Sets move to hold the value at that position

            if (move == 'X' || move == 'O' || move == ' ') {//Checks if the value of move is an an actual player move and not part of the board
                fprintf(file, "%c", move);//Writes to the file the move
            }
        }
    }

    fclose(file); //Closes the file

}

// Function to load the game state from a file
void load_board_from_file(TicTacToeBoard* board, char* file_path) {
    
    FILE* file = fopen(file_path, "r");//Opens file in 'Read' mode

    if (file == NULL) {//Error Handling - Ensures file opens successfully.
        printf("There was an error loading the previous game.\n");
        return;
    }
    
    initialize_board(board);//Creates a default board.
    
    fscanf(file, "%c\n", &(*board).current_player);//Loads the last player from the file.
    
    char move;//Used to hold the move value i.e X, O or a space

    for (int row = 0; row < 3; row++) {//Iterates through Rows
        for (int col = 0; col < 3; col++) {//Iterates through Columns

            fscanf(file, "%c", &move);//Scans the file to see what the slot there held

            if (move == 'X' || move == 'O' || move == ' ') {//Ensures the value brought back is not random junk.
                (*board).board[row][col] = move;//Updates that section of the board to reflect gamestate
            }
        }
    }

        fclose(file); //Closes the file
}
