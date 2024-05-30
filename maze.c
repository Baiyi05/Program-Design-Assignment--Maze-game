/*
DCP5101 Program Design @ Multimedia University
Trimester 2310 - 2023/24
Lecturer: Madam Nurul Aqma binti Salleh
Assignment Topic: MAZE Minigame
Group Members: 1. Koo Ming Sheng 1221207533
               2. Law Yong Soon 1221208246
               3. NG ZE JIAN 1221208430
               4. CHEN XIANG JUN 1221208265
*/ 

#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>

#define MAX_INPUT_LENGTH 5
#define WIDTH 8
#define HEIGHT 6

//for colour

#define red "\033[1;31m"
#define green "\033[0;32m"
#define yellow "\033[0;33m"
#define blue "\033[0;34m"
#define purple "\033[0;35m"
#define cyan "\033[0;36m"
#define clearcolor "\033[0m"


//for main menu
int menu ();
void menu_title ();
void startGame ();
void viewInstruction ();
void Instruction_titte();

//for level selection
int level_select ();
void level_tite();
void level_map (int level);
void print_map ();
void printmapperstep();
char temp[HEIGHT][WIDTH];
char map[HEIGHT][WIDTH];

//for game run
char* get_moves();
void move(char* moves,int level);
void gameover();
void win(int level);
void record_winner_name();
void display_winner_names();
void aftergame();


//set start point
struct player
{
    int x;
    int y;
};

void startpoint(struct player *p1, int level);



// main for game
int main()
{
    menu();

    return 0;
}

// main menu
int menu ()
{
    system("cls");
    int choice;
    menu_title();
    do {
        printf (yellow"\n1. Start Game\n");
        printf ("2. View Instruction\n");
        printf ("3. View Winners\n");
        printf ("4. Exit\n"clearcolor);
        printf (blue"\nEnter your choice : "clearcolor);
        scanf ("%d", &choice);
        fflush (stdin);

        switch (choice) {
            case 1 : 
            system("cls");
            startGame ();
            break;

            case 2 :
            system("cls");
            viewInstruction ();
            break;

            case 3 :
            system("cls");
            display_winner_names();
            break;

            case 4 :
            system("cls");
            printf ("Exiting the maze game. Goodbye!\n");
            exit(0);
            break;

            default :
            printf ("Invalid Choice! Please enter a number between 1 and 4.");
        } 
    } while (choice != 1 && choice != 2 && choice != 4 && choice != 4);

    return 0;
}

void menu_title ()
{   
  printf(purple"\n--------------------------------------------------------"clearcolor);
  printf(blue"\n       $$`       $$`   $$$$$ |`  $$$$$$$$$ / $$$$$$$$` ");
  printf("\n      $$$`    $$$$ / $$  __$$ / ____ $$$ / $$  ______/");
  printf("\n     $$$$` $$$$$$ / $$ /  $$ /     $$$ /  $$ /      ");
  printf("\n    $$`$$$$ / $$ / $$$$$$$$ /    $$$ /   $$$$$$$`    ");
  printf("\n   $$ `$$$ / $$ / $$  __$$ /   $$$ /    $$  ____/   ");
  printf("\n  $$ /`$  / $$ / $$ /  $$ /  $$$ /     $$ /      ");
  printf("\n $$ / `__/ $$ / $$ /  $$ / $$$$$$$$`  $$$$$$$$$` ");
  printf("\n`__/      `__/ `__/  `__/ `________/ `_________/"clearcolor);
  printf(purple"\n--------------------------------------------------------"clearcolor);
  
}

void Instruction_titte()
{

	printf(blue);
    printf("\n----------------------------------------------------------------------------------------------------");
	printf("\n$$$$$$ $$`   $$`  $$$$$$` $$$$$$$$`$$$$$$$`  $$`   $$`  $$$$$$` $$$$$$$$`$$$$$$` $$$$$$`  $$`   $$` ");
	printf("\n _$$  _$$$`  $$ |$$  __$$``__$$  __$$  __$$ |$$ |  $$ |$$  _ $$|`__$$  __`_$$  _$$  __$$` $$$`  $$ |");
	printf("\n  $$ | $$$$` $$ |$$ /  `_|   $$ |  $$ |  $$ |$$ |  $$ |$$ / `__|   $$ |    $$ | $$ /  $$ |$$$$` $$ |");
	printf("\n  $$ | $$ $$`$$ |`$$$$$$`    $$ |  $$$$$$$ ` $$ |  $$ |$$ |        $$ |    $$ | $$ |  $$ |$$ $$`$$ |");
	printf("\n  $$ | $$ `$$$$ |`_____$$`   $$ |  $$  __$$ |$$ |  $$ |$$ |        $$ |    $$ | $$ |  $$ |$$ `$$$$ |");
	printf("\n  $$ | $$ |`$$$ |$$`   $$ |  $$ |  $$ |  $$ |$$ |  $$ |$$ |  $$`   $$ |    $$ | $$ |  $$ |$$ |`$$$ |");
	printf("\n$$$$$$`$$ | `$$ | $$$$$$ /   $$ |  $$ |  $$ |`$$$$$$ /` $$$$$$ |   $$ |  $$$$$$ `$$$$$$  |$$ | `$$ |");
	printf("\n`______`__| `___|` -____/    `__|  `__|  `__|`______/  `______/    `__|  `_____| `______/ `__|  `__|");
	printf("\n----------------------------------------------------------------------------------------------------"clearcolor);
	

}

void startGame ()
{
    system("cls");
    int level = level_select();
    print_map(level);
    char* moves = get_moves();
    move(moves,level);
    
}

void viewInstruction() {
    int choice;
    Instruction_titte();
    printf ("\n");
    printf (cyan"-------------------- Maze Game Instructions --------------------\n");
    printf (yellow"\nWelcome to MAZE game!\n");
    printf ("S is start point\nE is end point\n+ is your position\n# is wall\n\n");
    printf ("You need to move from start point to end point in 5 steps.\n");
    printf ("You'll keep moving until you hit a wall; you can't move through walls.\n");
    printf ("You can only move up, down, left, or right.\n");
    printf ("---------------------------------------------------------------\n");
    printf (green"\nControls:\n");
    printf ("  - a: Move left\n");
    printf ("  - d: Move right\n");
    printf ("  - w: Move up\n");
    printf ("  - s: Move down\n");
    printf ("---------------------------------------------------------------\n");
    printf ("Enjoy your game!\n");
    printf (clearcolor);

    system("pause");
    menu();
}


// level selection

void level_tite()
{
	printf(yellow"\n--------------------------------------");
	printf("\n+_____________________________________+");
	printf("\n|  __   ___    ____    _  _     _____ |");
	printf("\n| /_ | |__ \\  |___ \\  | || |   | ____||");
	printf("\n|  | |    ) |   __) | | || |_  | |__  |");
	printf("\n|  | |   / /   |__ <  |__   _| |___ \\ |");
	printf("\n|  | |  / /_   ___) |    | |    ___) ||");
	printf("\n|  |_| |____| |____/     |_|   |____/ |");
	printf("\n|_____________________________________|");
	printf("\n--------------------------------------"clearcolor);
}



int level_select()
{
    int level;
        level_tite();
        do {
        printf ("\nSelect Level (1-5): ");
        scanf("%d", &level);
        fflush (stdin);
        if(level != 1 && level != 2 && level != 3 && level != 4 && level != 5) {
            printf("Invalid level! Please enter a number between 1 and 5.\n");

        }
    } while (level != 1 && level != 2 && level != 3 && level != 4 && level != 5);

    printf("\n    Level %d\n\n", level);
    level_map(level);

    return level;
}


void level_map (int level)
{
   if (level == 1)
   {
        char temp[HEIGHT][WIDTH] = 
            {
            {'#', '#', '#', '#', '#', 'E', '#', '#'},
            {'#', 'S', ' ', ' ', '#', ' ', ' ', '#'},
            {'#', ' ', '#', ' ', '#', '#', ' ', '#'},
            {'#', ' ', '#', '#', '#', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#'}
            };
            memcpy(map, temp, sizeof(temp));
    
   }
    else if (level == 2) 
    {
        char temp[HEIGHT][WIDTH] = 
            {
            {'#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
            {'E', ' ', ' ', ' ', '#', ' ', ' ', '#'},
            {'#', '#', ' ', ' ', ' ', 'S', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#'}
            };
            memcpy(map, temp, sizeof(temp));
    
    }
    else if (level == 3) 
    {
        char temp[HEIGHT][WIDTH] = 
            {
            {'#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', '#', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'E', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', 'S', ' ', ' ', '#', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#'}
            };
            memcpy(map, temp, sizeof(temp));
            
    }
    else if (level == 4)
    {
        char temp[HEIGHT][WIDTH] = 
            {
            {'#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', '#', 'S', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', '#'},
            {'#', ' ', ' ', '#', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', 'E', '#', '#', '#'}
            };
            memcpy(map, temp, sizeof(temp));
    }

    else if (level == 5)
    {
        char temp[HEIGHT][WIDTH] = 
            {
            {'#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', 'E'},
            {'#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
            {'#', ' ', 'S', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#'}
            };
            memcpy(map, temp, sizeof(temp));
    }

}

void print_map(int level) {
    system("cls");
    printf(yellow"\n*** Level %d ***\n\n"clearcolor, level);
    int i;
    int j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            char cell = map[i][j];
            switch (cell) {
                case '#':
                    printf(blue "# ");
                    break;
                case 'S':
                    printf(purple "S ");
                    break;
                case 'E':
                    printf(green "E ");
                    break;
                case '+':
                    printf(yellow "+ ");
                    break;
                default:
                    printf("  "); 
            }
        }
        printf("\n"clearcolor);
    }
}


void startpoint(struct player *p1, int level)
{

    if (level == 1)
    {
        p1->x = 1;
        p1->y = 1;
    }
    else if (level == 2)
    {
        p1->x = 5;
        p1->y = 3;
    }
    else if (level == 3)
    {
        p1->x = 1;
        p1->y = 4;
    }
    else if (level == 4)
    {
        p1->x = 6;
        p1->y = 1;
    }
    else if (level == 5)
    {
        p1->x = 2;
        p1->y = 4;
    }
}

//move
char* get_moves() {
    static char moves[MAX_INPUT_LENGTH + 1];
	int k;
	int w;
    for (k = 0; k < MAX_INPUT_LENGTH; k++) {
        printf("Enter move %d (w/a/s/d): ", k + 1);
        moves[k] = getchar();
        while (moves[k] == '\n') { // Ignore newline characters
            moves[k] = getchar();
        }
        while (getchar() != '\n'); // Clear the input buffer

        

        if (moves[k] != 'w' && moves[k] != 'a' && moves[k] != 's' && moves[k] != 'd') {
            printf("Invalid move. Please enter 'w', 'a', 's', or 'd' to move.\n");
            k--; // Decrement k to re-enter the current move
        } 
        // Print moves entered so far
        else {
            printf(cyan"Moves entered so far: "clearcolor);
            for (w = 0; w <= k; w++) {
                printf(yellow"%c "clearcolor, moves[w]);
            }
            printf("\n");
        }
    }

    moves[MAX_INPUT_LENGTH] = '\0';  // Null-terminate the string

    // Print final moves entered
    printf("Final moves entered: ");
    int z;
    for (z = 0; z < MAX_INPUT_LENGTH; z++) {
        printf("%c ", moves[z]);
    }
    printf("\n");
    return moves;
}

void printmapperstep(int level)
{
    print_map(level);
    Sleep(500);
}

void move(char* moves,int level)
{

    struct player p1;
    startpoint(&p1, level);

    int x = p1.x;
    int y = p1.y;
	int a;
    for (a = 0; a < MAX_INPUT_LENGTH && moves[a] != '\0'; a++) 
    {
            switch (moves[a]) 
            {
                case 'a':
                    map[y][x] = ' ';
                    while (map[y][x - 1] != '#' && map[y][x - 1] != 'E')
                    {
                        map[y][x] = ' ';
                        map[y][x - 1] = '+';
                        
                        x--;
                        printmapperstep(level);
                    }
                    map[y][x] = '+';
                    break;
                    
                case 'd':
                    map[y][x] = ' ';
                    while (map[y][x + 1] != '#' && map[y][x + 1] != 'E')
                    {
                        map[y][x] = ' ';
                        map[y][x + 1] = '+';
                        x++;
                        printmapperstep(level);
                    }
                    map[y][x] = '+';
                    break;

                case 'w':
                    map[y][x] = ' ';
                    while (map[y -1][x] != '#' && map[y - 1][x] != 'E')
                    {
                        map[y][x] = ' ';
                        map[y - 1][x] = '+';
                        y--;
                        printmapperstep(level);
                    }
                    map[y][x] = '+';
                    break;

                case 's':
                    map[y][x] = ' ';
                    while (map[y + 1][x] != '#' && map[y + 1][x] != 'E')
                    {
                        map[y][x] = ' ';
                        map[y + 1][x] = '+';
                        y++;
                        printmapperstep(level);
                    }
                    map[y][x] = '+';
                    break;
                    
            }


    }


    if (map[y][x - 1] == 'E')
    {
        map[y][x] = ' ';
        map[y][x - 1] = '+';
        print_map(level);
        win(level);
    }

    else if (map[y][x + 1] == 'E')
    {
        map[y][x] = ' ';
        map[y][x + 1] = '+';
        print_map(level);
        win(level);
    }

    else if (map[y - 1][x] == 'E')
    {
        map[y][x] = ' ';
        map[y - 1][x] = '+';
        print_map(level);
        win(level);
    }

    else if (map[y + 1][x] == 'E')
    {
        map[y][x] = ' ';
        map[y + 1][x] = '+';
        print_map(level);
        win(level);
    }
    
    else
    {
        print_map(level);
        gameover();
    }

    aftergame();

    

}

void gameover()
{

printf(red);
printf("\n---------------------------------------------------------------------------------------------------------");
printf("\n / $$$$$$  / $$$$$$  /$$     / $$ /$$$$$$$$       / $$$$$$ / $$  / $$ /$$$$$$$$/ $$$$$$$  / $$$/ $$$/ $$$");
printf("\n/ $$__ $$ / $$__  $$| $$$   / $$$| $$_____/      / $$__  $$| $$  | $$| $$_____/| $$__  $$ | $$$| $$$| $$$");
printf("\n| $$  `__ | $$  ` $$| $$$$ / $$$$| $$            | $$  | $$| $$  | $$| $$      | $$  ` $$ | $$$| $$$| $$$");
printf("\n| $$ /$$$ | $$$$$$$$| $$ $$ $$ $$| $$$$$         | $$  | $$| $$  / $$| $$$$$   | $$$$$$$/ ` $$$` $$$` $$$");
printf("\n| $$|_ $$ | $$__  $$| $$` $$$| $$| $$__/         | $$  | $$ ` $$/ $$/| $$__/   | $$__  $$  `__/ `__/ `__/");
printf("\n| $$  `$$ | $$  | $$| $$ ` $ | $$| $$            | $$  | $$ `  $$$$/ | $$      | $$  ` $$                ");
printf("\n|  $$$$$$ | $$  | $$| $$     | $$| $$$$$$$$      |  $$$$$$/  `  $$/  | $$$$$$$$| $$  | $$  | $$ | $$ | $$");
printf("\n `______/ |__/  |___|__/     |___|________/       `______/    `__/   |________/|__/  |__/  `__/ `__/ `__/");
printf("\n---------------------------------------------------------------------------------------------------------\n"clearcolor);
 
}

void win(int level)
{

printf(green);
printf("\n-----------------------------------------------------------------------------------------");
printf("\n/ $$    / $$/ $$$$$$ / $$  / $$       / $$         / $$/ $$$$$$/ $$  / $$ / $$$/ $$$/ $$$");
printf("\n`  $$  / $$/ $$__  $$| $$  | $$       | $$   / $   | $$ `  $$  | $$$ | $$ | $$$| $$$| $$$");
printf("\n `  $$/ $$ | $$  | $$| $$  | $$       | $$  / $$$  | $$  | $$  | $$$$| $$ | $$$| $$$| $$$");
printf("\n  `  $$$$  | $$  | $$| $$  | $$       | $$ / $$ $$ | $$  | $$  | $$ $$ $$ ` $$$` $$$` $$$");
printf("\n    | $$   | $$  | $$| $$  | $$       `  $$ $$`  $$ $$/  | $$  | $$` $$$$  `__/ `__/ `__/");
printf("\n    | $$   | $$  | $$| $$  | $$        `  $$$/ `  $$$/   | $$  | $$ ` $$$                ");
printf("\n    | $$   |  $$$$$$/|  $$$$$$/         `  $/   `  $/  / $$$$$$| $$  ` $$  | $$ | $$ | $$");
printf("\n    |__/    `______/  `______/           `_/     `_/   |______/|__/  |__/  `__/ `__/ `__/");
printf("\n-----------------------------------------------------------------------------------------\n"clearcolor);

if (level == 5) {
        record_winner_name();
    }

}

void record_winner_name() {
    FILE *file;
    char name[50];

    printf("Congratulations! You've won the game!\n");
    printf("Enter your name: ");
    gets(name);

    file = fopen("winners.txt", "a");
    if (file != NULL) {
        fprintf(file, "- %s -\n", name);
        fclose(file);
        printf("Your name has been recorded as a winner!\n");
    } else {
        printf("Failed to open the file for writing.\n");
    }
}

void display_winner_names() {
    FILE *file;
    char winner[100];

    file = fopen("winners.txt", "r");
    if (file != NULL) {
        printf("\nList of Winners level 5:\n");
        printf("----------------\n");
        while (fgets(winner, sizeof(winner), file) != NULL) {
            printf("%s", winner);
        }
        fclose(file);
    } else {
        printf("No winners recorded yet.\n");
    }
    system("pause");
    menu();
}

void aftergame()
{
    int pick;
    do{
        printf (blue"What would you like to do next?\n"clearcolor);
        printf (yellow"1: Back to level selection\n");
        printf ("2: Back to main menu\n");
        printf ("3: Exit\n"clearcolor);
        printf ("Enter your choice: ");
        scanf ("%d", &pick);
        fflush (stdin);

        switch (pick)
        {
        case 1:
            startGame();
            break;

        case 2:
            menu();
            break;

        case 3:
            printf ("Exiting the maze game. Goodbye!\n");
            exit(0);
            break;
        
        default:
            printf ("Invalid Choice! Please enter a number between 1 and 3.");

        }
    } while (pick != 1 && pick != 2 && pick != 3);

}
