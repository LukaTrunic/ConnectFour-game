#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <setjmp.h>  //I first put all the libraries that I need for this project and also put some along the way

#define ROWS    6
#define COLS    7 //This is to define how many rows and columns my connect four game is going to have and that I can write that, not numbers, and not get lost

char scores[ROWS][COLS]; //this is a variable where all the information about my board is going to be stored
char letter = 'X'; //the starting letter for the game that will start it
char name1[20]; //first name of the player
char name2[20]; //second name of the player
char filename[12] = "board__.txt";
int id;
int column = 0; //the starting column(first)
int save(char *); //where I save my file
int load(char *); //where I load my file
int check(char letter); //to check the letters in the correct order for a win (vertical, horizontal and diagonal) in all possible ways
//to load the list of saved games

void init_scores(); //this it to print the scores, but the board is not printed yet
void print_board(); //this is to print the board
void choose(); // to choose from numbers 0-7 to play the game
void fill_column(); //this function is to fill the chosen column according to what is already in the column
void game_mechanic(); //this is just the mechanic of the game that the game runs in
void names(); //names of both players
void load_game();//function to load the game
void load_list();
void load_user();
 

jmp_buf buf; //this is located at setjmp.h library and the longjump() transfers control the pointer which is pointed by setjump(). This means I can jump to a specific line when I want to.

int main()
{

    char response, newline;
    int choice, choice2;
    FILE *file;
    setjmp(buf);

    while(1){
        printf("====================\n");//when you start the program, first it goes into the main menu that has a while loop which will come back to the menu when the game is finished
        printf("-------MENU---------\n");
        printf("====================\n");
        printf("1.Play a new game\n");
        printf("2.Load already saved game\n");
        printf("3.Exit the game\n");//there are three options available in it
        printf("Enter your choice: \n");
        scanf("%d", &choice); //here, the user chooses which option they want to go with
        newline=getchar();

        switch(choice){
            case 1://if the user types 1
                do{
                    names();
                    init_scores();
                    print_board();
                    game_mechanic();
                    printf("Thanks for playing!\n");//After all of the functions have finished, it will print out Thanks for playing and
                    printf("Would you like to play again? Y/N \n");//ask if they would like to play again
                    scanf("%c", &response);
                    newline=getchar();
                } while(response == 'Y' || response == 'y');//this do while loop will be if they type y or Y, the game will restart and they will start another one but if they write something else or N, the game will end and go back to main menu

                break;
            case 2://if the user types 2, this will go to another menu that will be for loading games
                printf("1. List all saved games\n");
                printf("2. List all saved games for a particular player\n");
                printf("3. Show the board of one of the saved games\n");
                printf("4. Load a game\n");
                printf("5. Return to main menu\n");
                printf("Enter your choice: \n");
                scanf("%d", &choice2);
                newline=getchar();

                switch(choice2){
                    case 1:
                        load_list();
                        longjmp(buf, 1);
                        break;
                    case 2://if they choose 2, this will show the list of all saved games saved under a player

                        longjmp(buf, 1);
                        break;
                    case 3://if they choose 3, this will show just the board when they type the id in, but they cannot play the game, just see the saved board
                        load_game();
                        longjmp(buf, 1);//this function will jump to the main menu when the board is shown
                        break;
                    case 4://if they choose 4, this will load that board and they can play the game
                        load_game();
                        game_mechanic();
                        printf("Thanks for playing!\n");
                        longjmp(buf, 1);//this will jump to main menu when they finish the rest of the game
                        break;
                    case 5:// if they choose 5, this will return it to the main menu
                        longjmp(buf, 1);//this will jump to main menu
                        break;
                }

            case 3://this will exit the program
                exit(0);
                break;
            default://if the user writes something that is not given, they will get INVALID INPUT
                printf("INVALID INPUT\n");
        }
    }


    return 0;
}

void names() {//this function is just to ask for the name of the users that will play the game
	printf("\nName of first player:");
	scanf("%s", &name1);
	printf("\nName of second player:");
	scanf("%s", &name2);
}

void game_mechanic(){//this is how the game will work when the user starts it
    while(1){
        printf("Player %c, your turn!\n", letter);//this will specify whose turn is to go and then
        choose();//they will choose the column where they want to put it
        printf("\n\n");
        print_board();//this will then print the board and then
        if (check('X')){
            printf("\n\nPlayer X wins!\n\n");//if it checks (4 in a vertical, horizontal or diagonal way) for X, then it will print that X has won the game
            break;//If X wins, it will break and continue the program
        }
        if (check('O')){
            printf("\n\nPlayer O wins!\n\n");//If it checks for O, it will print that O has won the game
            break;//If O wins, it will break and continue the program
        }
        printf("Would you like to save this game? Press 0\n");
    }
}


void init_scores(){//this is just to have all possible places where the X and O can go, without printing the board yet. i will be the ROWS part and j will be the COLS.
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            scores[i][j] = ' ';
        }
    }
}

void print_board(){//this is the board that is going to be printed out in the program when the function is executed (or when the scores and names function ends) with the scores where you do exactly like the score function just set the %c so you can place X or O there.

    puts("|---|---|---|---|---|---|---|");//this will print the upper part

    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("| %c ", scores[i][j]);
        }
        printf("|\n");//this is one inside
        puts("|---|---|---|---|---|---|---|");//this the all the lines in the middle which will also be printed with the spaces because of the for loop

    }
    puts("  1   2   3   4   5   6   7  ");//this will print the down part with number of the column
    }

    void choose(){
    char newline, filename[12] = "board__.txt";
    int number, id;

    while (1)
    {
        printf("\nChoose column: "); //this is to choose what column they want to play their X or O in ranging from 1-7 and also if they want to save the game with 0
        scanf(" %d", &number);
        newline=getchar();

        switch(number)
        {
            case 0: //if they press 0, it will save the game in a file
                        printf("Enter a board number to save as (0 to 9):\n");
                        scanf("%d", &id);
                        filename[6] = '0' + id; //the filename will be the name given as char plus the id set by the user
                        printf("Board will be saved in %s\n", filename); //this will just print out the file name

                        if (save(filename) == 0)
                            puts("Board saved !");//this will just tell confirm to us that the file has been saved
                        else
                            puts("Could not save board !");
            case 1: //if they pick 1, letter will go to the first column
                column = 0;
                break;
            case 2: //if they pick 2, letter will go to the second column
                column = 1;
                break;
            case 3: //if they pick 3, letter will go to the third column
                column = 2;
                break;
            case 4: //if they pick 4, letter will go to the forth column
                column = 3;
                break;
            case 5: //if they pick 5, letter will go to the fifth column
                column = 4;
                break;
            case 6: //if they pick 6, letter will go to the sixth column
                column = 5;
                break;
            case 7: //if they pick 7, letter will go to the seventh column
                column = 6;
                break;
            default: //if they enter an invalid number, this will give them a message to type something else
                column = 100;
                printf("\nWrong number! Try again.\n\n");
                print_board();
        }
        if ((column >= 0 && column <= 6) && (scores[0][column] == ' ')) //this means that the letters cannot go into a column that does not exist, just to 1-7 column
        {
            fill_column(); //if there is a letter already in the column, this will stop it from going into the same row, but the row above it
            letter = (letter == 'X') ? 'O' : 'X'; //this will print out the appropriate letter
            break;
        }
    }
}

void fill_column(){
    int level;//this specifies the lowest level in the board

    for (level = ROWS - 1; level >= 0; level--) //this for loop will make sure that if there is already a letter in the column, another letter will go above it
    {
        if (scores[level][column] == ' ')
        {
            scores[level][column] = letter;
            break;
        }
    }
}

int check(char letter)
{
    int i, j, k;
    int count;
    int ways = 4;
    //ways is for up and down and count is for diagonals

    for (i = 0; i < ROWS; ++i) //this for loop will set that in one row, there are 4 possible ways that the X and O can match together
    {
        for (j = 0; j < ways; ++j)
        {
            count = 0;
            for (k = 0; k < 4; ++k)
            {
                if (scores[i][j + k] == letter) count++;
            }
            if (count == 4) return 1;
        }
    }

    ways = 3;
    for (j = 0; j < COLS; ++j) //this for loop will set that there are only 3 possible ways X and O to connect and be set for the win in a column
    {
        for (i = 0; i < ways; ++i)
        {
            count = 0;
            for (k = 0; k < 4; ++k)
            {
                if (scores[i + k][j] == letter) count++;
            }
            if (count == 4) return 1;
        }
    }

    int ii, jj;
    for (i = 1; i < ROWS-1; i++) //this for loop will set that letters can connect 4 tilting left going up
    {
        for (j = 1; j < COLS-1; j++)
        {
            count = 0;
            for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--)
            {
                if (scores[ii][jj] == letter)
                {
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            for (ii = i+1, jj = j+1; (ii <= ROWS-1) || (jj <= COLS-1); ii++, jj++)//this for loop will set that letters can connect 4 tilting left going down
            {
                if (scores[ii][jj] == letter)
                {
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }


            count = 0;

            for (ii = i, jj = j; (ii <= ROWS-1) || (jj >= 0); ii++, jj--)//this for loop will set that letters can connect 4 tilting right going down
            {
                if (scores[ii][jj] == letter)
                {
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            for (ii = i-1, jj = j+1; (ii >= 0) || (jj <= COLS-1); ii--, j++)//this for loop will set that letters can connect 4 tilting right going up
            {
                if (scores[ii][jj] == letter)
                {
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }
        }
    }

    return 0;
}

//They are the imaginary programs which serialise and deserialise the information about the board.
//The variables filename and id decide which file is read or written to.

void load_list(){

    FILE *file = fopen(filename, "r");

    for(id = 0; id < 10; id++){ //I did a for loop so all 10 saves can be shown
        filename[6] = '0' + id;
        printf("Saved in %s\n", filename);
    }

    fclose(file);
}

void load_user(){

}

void load_game(){

    printf("Enter a id number to load (0 to 9):\n"); //enter to id that the user wants to load
    scanf("%d", &id);
    filename[6] = '0' + id; //this is the name of the file plus the id that was typed
    printf("Loading board saved in %s\n", filename); //just to tell the user how the saved file is called that is being loaded

    if (load(filename) == 0)
        puts("Board loaded !"); //to tell the user that the load was successful
    else
        puts("Could not load board ! (Maybe such a file does not exist)"); //to tell the user that maybe the board could not load.
    puts("\n---------------------------------------------");
    puts("Your final board is : (same as old board if new one could not be loaded)");
    print_board(); //to print the saved board when the user tries to enter it
}

int save(char *filename) { //this is to save the file

    FILE *file = fopen(filename, "w"); //here we open the file in the writing mode
    if (file == NULL) //if there is no file to save, we just return
        return -1;
    else{ //else if there is, we save only the score in the board

        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                fprintf(file, "%c", scores[i][j]);

    }
    fclose(file); //we close the file
}

int load(char *filename)
{
    FILE *file = fopen(filename, "r"); //we open again the same file we saved and read it (mode read)
    if (file == NULL)
        return -1;
    else
    {
        for (int i = 0; i < ROWS; i++) //we print the score in the file saved on the command prompt
            for (int j = 0; j < COLS; j++)
                fscanf(file, "%c", &scores[i][j]);
    }
    fclose(file); //we close the file in the end
}
