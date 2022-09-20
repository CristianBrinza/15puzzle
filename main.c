#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

 int board[4][4] = {
	{1,   2,   3,   4},
	{5,   6,   7,   8},
	{9,  10,  11,  12},
	{13, 14,  15,  16} };

int inputKey = ' ', mode = 1, xi = 0, xj = 0;  
int nMoves = 0, inputMode = -999, choosenNumberI = 0, choosenNumberJ = 0,numI = 0, numJ = 0; 

int elementNotInList(int element, int* list, int n) {
	for (int i = 0; i < n; i++)  if (list[i] == element) return 0;
	return 1;
}

int menu(void) {
	int  menuOptions[] = {1, 2, 3}, menuOptionsLen = 3,c = -999;

	while(elementNotInList(c, menuOptions, menuOptionsLen)) {
		system("clear");
		printf("\t\tCristian Brinza   UTM FCIM FAF-212  POO  Lab1 \n\n\n\n\n\n\n");
        printf("\t\t     ▒▄█░▒█▀▀░░█▀▄ █░█ ▀▀▀▀█ ▀▀▀▀█ █░░ █▀▀\n");
        printf("\t\t     ░▒█░▒▀▀▄░░█░█ █░█ ░▄▀▀░ ░▄▀▀░ █░▄ █▀▀\n");
        printf("\t\t     ▒▄█▄▒▄▄▀░░█▀░ ░▀░ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀ ▀▀▀\n\n\n\n\n");
      

        printf("\t\t\t\t   Menu:\n\n");
		printf("\t\t\t\t1.Start\n");
		printf("\t\t\t\t2.Exit game\n");
		printf("\t\t\t\t3.Resume previos game\n\n\n");;
		printf("\t\t\t\nChoose an option: ");
	
		c = (int)(getc(stdin) - '0');
	}

	return c;
}

void won() {
	int winMatrix[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	for (int i = 0; i < 4; i++)
		for (int j = 1; j < 4; j++)
			if (board[i][j] != winMatrix[i][j])
				return;

	mode = 3;
}

void shuffleBoard() {
	int flag;
	int row = rand() % 4, col = rand() % 4;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			flag = board[i][j];
			board[i][j] = board[row][col];
			board[row][col] = flag;
		}
}

void displayNumber(int n, char* color, int padding) {	
	if (n == 16)
		printf("%s%*c%s", color, padding, 'X', "\x1B[0m");
	else
		printf("%s%*d%s", color, padding, n, "\x1B[0m");
}

void displayBoard() {
    printf("\t\tCristian Brinza   UTM FCIM FAF-212  POO  Lab1\n");
        
    printf("\n\t\t\t\t");
	for (int i = 0; i < 6; i++) {
		if (i == 0 || i == 5)
			for (int j = 0; j < 6; j++)
				printf("░░░");
					
		else
			for (int j = 0; j < 6; j++) {
				if (j == 0 || j == 5) 
					printf("░");
				else {
					if (numI == i - 1 && numJ == j - 1)
						displayNumber(board[i - 1][j - 1], "\x1b[5m", 4);
					else
						displayNumber(board[i - 1][j - 1], "\x1B[0m", 4);
				}
			}
		
		printf("\n\t\t\t\t");
	}

	printf("\n\n");
}

void displayProgress() {
    
	printf("       Moves made: %d", nMoves);
	printf("      Currently position (%d, %d)", numI, numJ);
	printf("    Blank tile at (%d, %d)\n\n", xi, xj);
    printf("");
}

void displayInputHelp() {
	if (mode == -999)
		return;

	if (mode == 1){
        printf("      =======================================================================\n");
	
printf("          Tip :  Choose a number to move using arrows...\n");
	
    }
		else if (mode == 2)
		printf("%s!!! Error !!!  Cannot move this one :/%s\n", "\x1B[31m", "\x1B[0m");

	printf("\n\tControls:\n");
	printf("Arrows  - move the cursor between tiles\n");
	printf("Space   - choose the tile and switch it with the empty tile (X)\n");
	printf("  u     - undo move\n");
    printf("  r     - reset game\n");
	printf("  s     - save and quit game\n");
	printf("  q     - quit game\n\n");
}

void getXCoords() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (board[i][j] == 16) {
				xi = i;
				xj = j;

				return;
			}
}

void move(int direction) {
	if (direction == 65 && numI > 0)
		numI--;
	else if (direction == 66 && numI < 3)
		numI++;
	else if (direction == 67 && numJ < 3)
		numJ++;
	else if (direction == 68 && numJ > 0)
		numJ--;
}

int canMoveTile() {
	if (abs(xi - numI) <= 1 && abs(xj - numJ) <= 1 && abs(xi - numI) + abs(xj - numJ) <= 1) {
		mode = 2;

		return 1;
	}

	return 0;
}

void swapTiles() {
	if (mode != 1)
		return;

	if (inputKey == ' ' && board[numI][numJ] != 16 && canMoveTile()) {
		board[xi][xj] = board[numI][numJ];
		board[numI][numJ] = 16;

		mode = 1;
		nMoves++;
	}
	else if (inputKey == 65 || inputKey == 66 || inputKey == 67 || inputKey == 68)
		move(inputKey);
}

int isSolvable() {
	int arr[16];
	int k = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			arr[k] = board[i][j];
			k++;
		}

	int inversions = 0;

	for (int i = 0; i < 15; i++)
		if (arr[i] > arr[i + 1] && arr[i] != 16 && arr[i + 1] != 16)
			inversions++;

	if ((inversions % 2 == 0 && (4 - xi) % 2 != 0) || (inversions % 2 != 0 && (4 - xi) % 2 == 0))
		return 1;

	return 0;
}

void initGame() {
	nMoves = 0;
	mode = 1;

	shuffleBoard();
	while (isSolvable() == 0)
		shuffleBoard();

	getXCoords();
	numI = 0;
	numJ = 0;
}

void resume() {
	FILE *f;
	char buff[3];

	f = fopen("./state.txt", "r");

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			fscanf(f, "%s", buff);	

			board[i][j] = atoi(buff);
		}

	
	fscanf(f, "\n%s", buff);
	nMoves = atoi(buff);

	fclose(f);

	mode = 1;
	numI = 0;
	numJ = 0;
	getXCoords();
}

void displayWinText() {
	printf("\n\n\tCongratulation. You have won!\n");
}

void exitGame() {
	printf("\n\nQuiting...\n");
	exit(0);
}

void save() {
	FILE *f;

	f = fopen("./state.txt", "w");

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			fprintf(f, "%d ", board[i][j]);

	
	fprintf(f, "\n%d", nMoves);

	fclose(f);
}

void play(int shouldResume) {
	
	if (shouldResume == 1)
		resume();
	else
		initGame();
	
	 
	while(1) {
		system("clear");
		displayBoard();

		if (mode == 3) {
			displayWinText();
			exit(0);
		}


		displayProgress();
		displayInputHelp();

		mode = 1;
		getXCoords();

		inputKey = (int)getchar();

		if (inputKey == 'q')
			exitGame();
		else if (inputKey == 'r')
			initGame();
		else if (inputKey == 's') {
			save();
			exit(0);
		}

		if (mode == 1)
			swapTiles();

		won();
	}
}

int main(void) {
	switch(menu()) {
		case 1: play(0); break;
		case 2: return 0;
		case 3: play(1); break;
		default: break;
	}

	return 0;
}