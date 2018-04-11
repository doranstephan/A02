
//------------------------------------
//	Define
//------------------------------------
#ifndef _GAME_
#define _GAME_
#define SIZE 3
#define _CRT_SECURE_NO_WARNINGS

//------------------------------------
//	Include Libraries
//------------------------------------
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------
//	Datatype bool
//------------------------------------
enum Bool { False, True };
typedef enum Bool boolean;

//------------------------------------
//	Datatype game
//------------------------------------
struct _game {
	char* p1;
	char* p2;
	int mode;
	int status;
	char board[SIZE][SIZE];
	int avenue_positions[2*SIZE+2][SIZE];
	int avenue_states[2*SIZE+2];
	boolean intelligent_machine;
};

typedef struct _game game;

//--------------------------------------------
// 01. FUNCTION create_new_game (IMPLEMENTED)
//--------------------------------------------
game* create_new_game(char* p1, char* p2, int im);

//-------------------------------------
// 02. FUNCTION display_board_content
//-------------------------------------
void display_board_content(game* g);

//------------------------------------
// 03. FUNCTION display_game_status
//------------------------------------
void display_game_status(game* g);

//---------------------------
// 04. gen_num (IMPLEMENTED)
//---------------------------
int gen_num(int lb, int ub);

//---------------------------------------
// 05. FUNCTION my_getchar (IMPLEMENTED)
//---------------------------------------
char my_get_char();

//------------------------------------
// 06. FUNCTION is_position_empty
//------------------------------------
boolean is_position_empty(game* g, int pos);

//---------------------------------------
// 07. FUNCTION user_get_movement_index
//---------------------------------------
int user_get_movement_index(game* g);

//------------------------------------------
// 08. FUNCTION computer_get_movement_index
//------------------------------------------
int computer_get_movement_index(game* g);

//--------------------------------------
// 09. FUNCTION get_next_movement_index
//--------------------------------------
int get_next_movement_index(game* g);

//------------------------------------
//	10. FUNCTION is_there_a_winner
//------------------------------------
int is_there_a_winner(game* g);

//------------------------------------
//	11. FUNCTION update_game_status
//------------------------------------
void update_game_status(game* g);

//------------------------------------
// 12. FUNCTION process_movement
//------------------------------------
void process_movement(game* g, int pos);

//------------------------------------
// 13. FUNCTION play_game
//------------------------------------
void play_game(char* p1, char* p2, int im);

//------------------------------------
// 14. FUNCTION update_avenue_states
//------------------------------------
void update_avenue_states(game* g, int avenue);

//----------------------------------------
// 15. FUNCTION get_position_points
//----------------------------------------
int get_position_points(game* g, int pos);

//----------------------------------------
// 16. FUNCTION intelligent_selection
//----------------------------------------
int intelligent_selection(game* g);

//------------------------------------
//	End of file
//------------------------------------
int diago1(int i, int j, int incr);
int diago2(int i, int j);
void print_tab(game* g);
int clean_input();
#endif

















