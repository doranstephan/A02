
//------------------------------------
//	Define
//------------------------------------
#define _CRT_SECURE_NO_WARNINGS

//------------------------------------
//	Include Libraries
//------------------------------------
#include <time.h>
#include "game.h"
#include <string.h>

//------------------------------------
//	FUNCTION main
//------------------------------------
int main(int argc, char* argv[]) {
	//1. We set the seed for generating random numbers (in case the "Computer" acts as one of the players)
	srand((unsigned int) time(NULL));

	//2. We parse the input arguments to the program
	//2.1. The first argument is the name of the first player
	//char* p1 = (char*)malloc(strlen(argv[1]) + 1 * sizeof(char));
	//strcpy(p1, argv[1]);
	char* p1 = "John";

	//2.2. The second argument is the name of the second player
	//char* p2 = (char*)malloc(strlen(argv[2]) + 1 * sizeof(char));
	//strcpy(p2, argv[2]);
	char* p2 = "Don";

	//2.3. The third argument is 0 for non-intelligent machine or 1 for intelligent
	//int im = atoi(argv[3]);
	int im = 0;

	//3. We call to the main function of the game
	play_game(p1, p2, im);

	//4. We finish the application returning 0
	return 0;
}



