#include <ctype.h>   // isdigit()
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // rand(), srand()
#include <string.h>
#include <time.h>    // time()

//written by Paul Jesic 28/sep/2026


enum gamegameState {NO_WINNER, GAME_WON, GAME_TIE};
enum gamegameState gameState = 0;
enum currentplayer {COMPUTER, PLAYER};


void printHeader(void) {
    printf("=====================================\n");
    printf("        TIC-TAC-TOE vs COMPUTER\n");                 
    printf("=====================================\n\n");
    printf("You are O and you go first. The computer is X.\n");
    printf("On your turn, type the number of an empty square:\n\n"); 
    printf(" 1 | 2 | 3 \n");
    printf("---+---+---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---+---+---\n");
    printf(" 7 | 8 | 9 \n\n");

    return;
}

void playerTurn(char board[]) {
    while (true) {
        char input[100];

        printf("Your turn (O). Enter a square number (1-9): ");
        scanf("%s", input);      //get player input as string

        if (strlen(input) != 1 || !isdigit(input[0])) {        //check if input is a single digit
            printf("\n\nInvalid input! Please enter a number between 1-9.\n");
            continue;
        }
        int playerInput = input[0] - '0';      //convert char to int
        if (playerInput < 1 || playerInput > 9) {       //check if input is between 1-9
            printf("\n\nInvalid input! Please enter a number between 1-9.\n");
            continue;
        }

        if (board[playerInput - 1] != 'O' && board[playerInput - 1] != 'X') {
            board[playerInput - 1] = 'O';   //update board using player input 
            printf("\n");
            return;
        }
        else {
            printf("\n\nSpot has already been choosen!\n");
        }
    }

}

void computerTurn(char board[]) {
    int computerInput;

    printf("Computer (X) is thinking...\n");
    
    while (true) {
        computerInput = rand() % 9 + 1;         //assign computerInput = rand number between 1-9

        if (board[computerInput - 1] != 'O' && board[computerInput - 1] != 'X') {       //check choosen spot is taken
            board[computerInput - 1] = 'X';   //update board using player input 
            break;
        }

    }
    
    printf("Computer (X) chose square %d. Your move next!\n\n", computerInput);

}

void initializeBoard(char board[]){
    char letter = '1';


    for (int i=0; i<9; ++i){
        board[i] = letter;
        ++letter;
    }

}

void printBoard(char board[]){

    
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n\n", board[6], board[7], board[8]);
    

}

enum gamegameState checkWinner(char board[]) {

    int emptySpots = 0;
    char arrayPosition = '1';

    

    if (board[0] == board[1] && board[1] == board[2]){          //top row
        return GAME_WON;
    }
    else if (board[3] == board[4] && board[4] == board[5]){           //middle row
        return GAME_WON;
    }
    else if (board[6] == board[7] && board[7] == board[8]){          //bottom row
        return GAME_WON;
    }
    else if (board[0] == board[3] && board[3] == board[6]){          //first column
        return GAME_WON;
    }
    else if (board[1] == board[4] && board[4] == board[7]){          //second column
        return GAME_WON;
    }
    else if (board[2] == board[5] && board[5] == board[8]){          //third column
        return GAME_WON;
    }
    else if (board[2] == board[4] && board[4] == board[6]){          //diagonal
        return GAME_WON;
    }
    else if (board[0] == board[4] && board[4] == board[8]){          //other diagonal
        return GAME_WON;
    }
    
    
    for (int i = 0; i < 9; ++i) {          // check if theres any empty spots left and if there isnt, return game tie
        if (board[i] == arrayPosition) {
            ++emptySpots;
        }
        ++arrayPosition;
    }
    

    if (emptySpots == 0) {
        return GAME_TIE;
        //printf("FIXME: checkwinner thinks there was a tie\n");
    }


    return NO_WINNER;

    //there is probably a cleaner way of doing this but this is much simpler and quicker 
    
}

void askToPlayAgain(bool *playAgain, enum gamegameState *gameState) {
    char userInput;
    
    while (true){
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &userInput);


        if (userInput == 'y') {
            *playAgain = true;
            *gameState = NO_WINNER;
            printf("\n");
            return;
        }
        else if (userInput == 'n') {
            *playAgain = false;
            return;
        }
        else {
            printf("Invalid input\n\n");
        }
    }
    
}

bool checkGameState(char board[], bool *playAgain, enum gamegameState *gameState, bool isplayerTurn) {
    *gameState = checkWinner(board);

    if (*gameState == GAME_WON && isplayerTurn == true) {       //check if player won
        printf("Congratulations player! you won\n\n");
        printBoard(board);      // print winning board 
        askToPlayAgain(playAgain, gameState); // ask player if they want to play again. resets gamestate back to NO_WINNER so game keeps going
        initializeBoard(board); // reset board for next game

        if (*playAgain == false) {                   //if player does not want to play again, exit program
            printf("\nThank you for playing!\n");
            exit(0);                                //exit(0) terminates main and ends the program
        }
        else {
            printBoard(board);
            return true;                      // print the board after someone has won so the player can see an empty board
        }
    }

    else if (*gameState == GAME_TIE) {       //check if game was tied
        printf("Game was tied! how did you manage that?\n\n");
        printBoard(board);      // print winning board
        askToPlayAgain(playAgain, gameState); // ask player if they want to play again. resets gamestate back to NO_WINNER so game keeps going
        initializeBoard(board); // reset board for next game
        if (*playAgain == false) {                   //if player does not want to play again, exit program
            printf("\nThank you for playing!\n");
            exit(0);
        }
        else {
            printBoard(board); // print the board after someone has won so the player can see the empty board
            return true;
        }
    }

    else if (*gameState == GAME_WON && isplayerTurn == false) {       //check if computer won
        printf("You lost! how did you manage that?\n\n");       //check if comp won
        printBoard(board);          // print winning board
        askToPlayAgain(playAgain, gameState); // ask player if they want to play again. resets gamestate back to NO_WINNER so game keeps going
        initializeBoard(board); // reset board for next game
        if (*playAgain == false) {                   //if player does not want to play again, exit program
            printf("\nThank you for playing!\n");
            exit(0);
        }
        else {
            printBoard(board); // print the board after someone has won so the player can see the empty board
            return true;
        }
    }

    return false;
}



int main(void) {
    char board[9];

    //start up
    printHeader();      //print header
    initializeBoard(board);  // assign int 1-9 to the empty array
    srand(time(NULL)); // reset random numbers
    bool playAgain = true;    //initiliaze the variable that checks whether the player wants to play again
    bool isplayerTurn = true;    //initialize the variable that checks whether it is the players turn or not
    
    while (true) {
        while (playAgain == true) {
            isplayerTurn = true;
            playerTurn(board);
            if (checkGameState(board, &playAgain, &gameState, isplayerTurn)) {
                break;
            }

            //computer turnt ---- code is the exact same as player turn 
            isplayerTurn = false;
            computerTurn(board);      //create and apply computers input
            if (checkGameState(board, &playAgain, &gameState, isplayerTurn)) {
                break;
            }

            printBoard(board);      //print board after computer turn
        
        }
    }
        


}
    
    


    /*
    ALL GAME CONDITIONS ARE ACCOUNTED FOR!
    tie win condition is accounted for, even if board is full it will first detect for winner AND THEN say the game is tied
    computer win is accounted for
    player win is accounted for
    the player AND computer choosing an already choosen spot is accounted for by prompting each for another selection

   invalid input for yes no
   char input for player turn
    
    */







    //planning -------
    // while (winner has been found == false)
        //ask for user input
            //check if square is already taken
        //update table
        //print table
            //check if winner has been found
                //print winner has been found and update winner found 

        
        //create computer input
        //update table
        //print table
            //check if winner has been found
                //print winner has been found and update winner found 
            
        



   
