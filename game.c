
//------------------------------------
//	Include Libraries
//------------------------------------
#include "game.h"
#include <math.h>
#include <stdio.h>


int my_get_int(){
    int i=-1;
    char c;

    do
    {

    } while (((scanf("%d%c", &i, &c)!=2 || c!='\n') && clean_input()));
    return i;
}

int clean_input()
{
    while (getchar()!='\n');
    return 1;
}



//---------------------------------------------
//	01. FUNCTION create_new_game (IMPLEMENTED)
//---------------------------------------------
game* create_new_game(char* p1, char* p2, int im) {
	//1. We declare the variable to be returned
	game* res = NULL;

	//2. We create memory space for it with malloc.
	res = (game*)malloc(1 * sizeof(game));

	//3. We use the names passed as arguments to initialise p1 and p2.
	(*res).p1 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*res).p1, p1);

	(*res).p2 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*res).p2, p2);

	//4. We set the mode based on the names of the players.
	// Human vs. Human --> mode = 1
	// Human vs. Computer --> mode = 2
	// Computer vs. Human --> mode = 3
	// Computer vs. Computer --> mode = 4
	int mode = 1;
	if (strcmp(p1, "Computer") == 0)
		mode = mode + 2;
	if (strcmp(p2, "Computer") == 0)
		mode = mode + 1;

	(*res).mode = mode;

	//5. We set the status to be 1; (i.e., player1 moves first)
	(*res).status = 1;

	//6. We initialise the board so that all its positions are empty
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			(*res).board[i][j] = ' ';

	//7. We use the im passed as arguments to initialise intelligent_machine.
	if (im == 0)
		(*res).intelligent_machine = False;
	else
		(*res).intelligent_machine = True;

	//8. ---Computer Intelligent Movement Only --- We We initialise the avenues
	//avenue 0 --> [0,1,2]
	//avenue 1 --> [3,4,5]
	//avenue 2 --> [6,7,8]
	//avenue 3 --> [0,3,6]
	//avenue 4 --> [1,4,7]
	//avenue 5 --> [2,5,8]
	//avenue 6 --> [0,4,8]
	//avenue 7 --> [2,4,6]
	/*
	(*res).avenue_positions[0][0] = 0;
	(*res).avenue_positions[0][1] = 1;
	(*res).avenue_positions[0][2] = 2;

	(*res).avenue_positions[1][0] = 3;
	(*res).avenue_positions[1][1] = 4;
	(*res).avenue_positions[1][2] = 5;

	(*res).avenue_positions[2][0] = 6;
	(*res).avenue_positions[2][1] = 7;
	(*res).avenue_positions[2][2] = 8;

	(*res).avenue_positions[3][0] = 0;
	(*res).avenue_positions[3][1] = 3;
	(*res).avenue_positions[3][2] = 6;

	(*res).avenue_positions[4][0] = 1;
	(*res).avenue_positions[4][1] = 4;
	(*res).avenue_positions[4][2] = 7;

	(*res).avenue_positions[5][0] = 2;
	(*res).avenue_positions[5][1] = 5;
	(*res).avenue_positions[5][2] = 8;

	(*res).avenue_positions[6][0] = 0;
	(*res).avenue_positions[6][1] = 4;
	(*res).avenue_positions[6][2] = 8;

	(*res).avenue_positions[7][0] = 2;
	(*res).avenue_positions[7][1] = 4;
	(*res).avenue_positions[7][2] = 6;
	*/
	//initializing avenue for whatever size
	int i=0;
    int rdc=0;
    int diag1=0;
    int compteur=0;
    for(i=0;i<2*SIZE+2;i++){
        int j=0;
        int increment=0;
        for (j=0;j<SIZE;j++){
            if(rdc==0)
                (*res).avenue_positions[i][j]= compteur;
            else if (rdc==1)
                (*res).avenue_positions[i][j]= (i-SIZE)+increment;
            else{
                if (diag1<SIZE){
                    (*res).avenue_positions[i][j]= j+increment;
                    diag1++;
                    }
                else
                    (*res).avenue_positions[i][j]= 2*j+2;
            }
            increment+=SIZE;
            compteur++;
        }
        if (i==SIZE-1)
            rdc++;
        else if(i==2*SIZE-1)
            rdc++;
    }

	//9. ---Computer Intelligent Movement Only --- We initialise all avenues to state2
	for (int i = 0; i < 2*SIZE+2; i++)
		(*res).avenue_states[i] = 2;

	//10. We return res
	return res;
}


//-------------------------------------
//	02. FUNCTION display_board_content
//-------------------------------------
void display_board_content(game* g) {
    int i=0;
    int j=0;
    for(j=0;j<SIZE;j++)
    {
        printf("        |");

        for(i=0;i<SIZE;i++)
        {
            printf("---|");
        }
        printf("\n");
        printf("        |");

        for(i=0;i<SIZE;i++)
        {
            printf(" %c |",g->board[i][j]);
        }
        printf("\n");
    }
    printf("        |");
    for(i=0;i<SIZE;i++)
    {
        printf("---|");
    }
    printf("\n");

}

//------------------------------------
//	03. FUNCTION display_game_status
//------------------------------------
void display_game_status(game* g) {
    printf("        -------------\n");
    printf("        GAME STATUS \n");
    printf("        -------------\n");
    printf("\n");
    display_board_content(g);
    switch (g->status){
        case 1:
            printf("Player %s moves next\n",g->p1);
            break;
        case 2:
            printf("Player %s moves next \n", g->p2);
            break;
        case 3:
            printf("Player %s win\n", g->p1);
            exit(0);
            break;
        case 4:
            printf("Player %s win\n", g->p2);
            exit(0);
            break;
        case 5:
            printf("Game finished with a Draw");
            exit(0);
            break;
        default:
            printf("Default");
            break;
    }
    if (g->status==1 && (g->mode == 1 || g->mode == 2) || g->status ==2 && (g->mode==1 || g->mode == 3))
    {

    print_tab(g);

    printf("        Enter a position from 0 to %d:",SIZE*SIZE-1);

    }
    else
    {
        //on ne fait rien si c'est un ordi

    }

}
void print_tab(game* g){
    int i=0;
    int compteur=0;
    printf("        |");
    for(i=0;i<SIZE;i++)
    {
        printf("---|");
    }
    printf("\n");
    for(i=0;i<SIZE;i++)
    {
        printf("        |");
        int j=0;
        for(j=0;j<SIZE;j++)
        {
            if(compteur<10)
                printf(" %d |",compteur);
            else if(compteur<100)
                printf(" %d|",compteur);
            else
                printf("%d|",compteur);
            compteur++;
        }
        printf("\n");
        printf("        |");
        for(j=0;j<SIZE;j++)
        {
            printf("---|");
        }
        printf("\n");

    }

}
//--------------------------------------------------
// 04. gen_num (IMPLEMENTED)
//--------------------------------------------------
int gen_num(int lb, int ub) {
	//1. We create the output variable with an initial value.
	int res = 0;

	//2. We assign num to a random value in the desired range
	res = (rand() % (ub - lb)) + lb;

	//3. We return the output variable
	return res;
}

//--------------------------------------------------
// 05. FUNCTION my_getchar (IMPLEMENTED)
//--------------------------------------------------
char my_get_char() {
	//1. We create the variable to be returned
	char res = ' ';

	//2. We create an extra variable to consume any other characters entered until a return is pressed
	boolean line_consumed = False;
	char dummy_char = ' ';

	//3. We consume the first char entered, i.e., the one we are interested at
    res = getchar();

	//4. While still there are remaining characters
	while (line_consumed == False) {
		//4.1. We consume the next character
		dummy_char = getchar();

		//4.2. If the new character is the end of line one, we can ensure we have consumed the entire line.
		if (dummy_char == '\n')
			line_consumed = True;

	}
	//5. We return res
	return res;
}

//------------------------------------
//	06. FUNCTION is_position_empty
//------------------------------------
boolean is_position_empty(game* g, int pos) {
	//1. We create the variable to be returned
	boolean res = False;
    int x=pos%SIZE;
    int y=pos/SIZE;
    if(g->board[x][y]==' ')
        res=True;
	//2. We check if the index is a valid one and if the board is empty at that index.
	//If it is valid and free, we return True.
	//Otherwise, we return False and write a warning message.

	//3. We return res
	return res;
}

//---------------------------------------
//	07. FUNCTION user_get_movement_index
//---------------------------------------
int user_get_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We create a boolean variable to control that we have received a valid movement index.
    boolean b = False;
	//3. We create a char variable to control the index we are receiving by keyboard.
    int control=-1;
	//4. While we have not received a valid movement index.
	while(b!=True)
    {
        control=my_get_int();
        res=control;


        if(res!=-1){
            if (is_position_empty(g,res))
                b=True;
        }
    }
	//We print a message asking for a new movement.
	//We call to my_get_char to get the index and we convert it to an integer.
	//We call to is_position_empty to check that the index is a valid one.

	//5. We return res
	return res;
}

//-------------------------------------------
//	08. FUNCTION computer_get_movement_index
//-------------------------------------------
int computer_get_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We create a boolean variable to control that we have received a valid movement index.
    boolean b = False;
	//3. While we have not received a valid movement index.
	while(b!=True){
        if(!g->intelligent_machine){
            res = gen_num(0,SIZE*SIZE);
        }
        else{
            res= intelligent_selection(g);
        }
        if (is_position_empty(g,res))
                b=True;

	}


    printf("        Press a key to continue...\n");
    my_get_char();
	return res;
}

//---------------------------------------
//	09. FUNCTION get_next_movement_index
//---------------------------------------
int get_next_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We ask for the next valid movement to be selected.
	//Depending on the game status and the players name we call to the function

	//human case
    if (g->status==1 && (g->mode == 1 || g->mode == 2) || g->status ==2 && (g->mode==1 || g->mode == 3))
    {
        res=user_get_movement_index(g);
    }
    else
    {
        res=computer_get_movement_index(g);
    }
	//user_get_movement_index or computer_get_movement_index

	//3. We return res
	return res;
}

//------------------------------------
//	10. FUNCTION is_there_a_winner
//------------------------------------
int is_there_a_winner(game* g) {
	//1. We create the variable to be returned
	int res = 0;
    int i=0;
    for(i=0;i<2*SIZE+2;i++)
    {
        int j=0;
        int nbX=0;
        int nbO=0;
        for(j=0;j<SIZE;j++)
        {
            int pos=g->avenue_positions[i][j];
            int x=pos%SIZE;
            int y=pos/SIZE;
            if(g->board[x][y]=='X')
                nbX+=1;
            else if(g->board[x][y]=='O')
                nbO+=1;

        }
        if (nbX==SIZE)
            return 1;
        if (nbO==SIZE)
            return 2;
    }
	//2. We check the 8 possible ways (avenues) of winning the game,
	//to see if either player P1 or player P2 have won in any of them.
	//avenue 0 --> [0,1,2]
	//avenue 1 --> [3,4,5]
	//avenue 2 --> [6,7,8]
	//avenue 3 --> [0,3,6]
	//avenue 4 --> [1,4,7]
	//avenue 5 --> [2,5,8]
	//avenue 6 --> [0,4,8]
	//avenue 7 --> [2,4,6]

	//3. We return res
	return res;
}

//------------------------------------
//	11. FUNCTION is_board_full
//------------------------------------
boolean is_board_full(game* g) {
	//1. We create the variable to be returned
	boolean res = True;
    int i=0;
    for(i=0;i<SIZE;i++)
    {
        int j=0;
        for(j=0;j<SIZE;j++)
        {
            if(g->board[i][j]==' ')
            {
                return False;
            }

        }
    }
	//2. We check if the 9 positions of the board are busy.
	//If all positions are busy, we return True.
	//If at least one position is empty, we return False.

	//3. We return res
	return res;
}

//------------------------------------
//	12. FUNCTION process_movement
//------------------------------------
void process_movement(game* g, int pos) {
	// 1. We update board with the new movement at index 'pos'.
	// This requires checking the current status to know if the movement is an 'X' or a 'O'.
    int x=pos%SIZE;
    int y=pos/SIZE;
    if(g->status==1)
    {

        g->board[x][y]='X';
    }
    else if(g->status==2)
    {
        g->board[x][y]='O';
    }

	//2. ---Computer Intelligent Movement Only ---
	//We traverse each avenue: If pos belongs to it, we call to update_avenue_states to update its state.
    int i=0;
    for(i=0;i<2*SIZE+2;i++)
    {
        int j=0;
        for(j=0;j<SIZE;j++)
        {
            if(g->avenue_positions[i][j]==pos)
                update_avenue_states(g,i);
        }
    }
	//3. We create a variable winner and call to the function is_there_a_winner
	//to see if this movement has lead to a winner.
    int winner=-1;
    winner=is_there_a_winner(g);
    boolean draw=is_board_full(g);

    if(winner==1)
    {
        g->status=3;
    }
    else if(winner==2)
    {
        g->status=4;
    }
	//4. We create a variable winner and call to the function is_board_full to see if the board is full.
    else if (draw)
    {
        g->status=5;
    }
    else if(g->status==1)
    {
        g->status=2;
    }
    else{
        g->status=1;
    }

	//5. We update the status accordingly.
	// (Case 1) winner == 1 --> Game Status = 3.
	// (Case 2) winner == 2 --> Game Status = 4.
	// (Case 3) winner == 0 and full == True --> Game Status = 5.
	// (Case 4) winner == 0 and full == False --> Depending on current Game Status.
	//											  If Game Status == 1 --> Game Status = 2.
	//											  If Game Status == 2 --> Game Status = 1.

}

//------------------------------------
//	13. FUNCTION play_game
//------------------------------------
void play_game(char* p1, char* p2, int im){
	//1. We create a variable pointer game* g and call to the function
	//create_new_game so as to initialise it.
	game* g = create_new_game(p1, p2, im);
	/*int i=0;
    for(i=0;i<2*SIZE+2;i++){
        int j=0;
        for(j=0;j<SIZE;j++){
            printf("Pos %d:%d val: %d\n",i,j,(*g).avenue_positions[i][j]);
        }
    }*/
	//2. Game loop: While the game is on (i.e., Game Status = 1 or Game Status = 2)
	while(g->status==1 || g->status==2)
    {
        display_game_status(g);
        int pos=get_next_movement_index(g);
        process_movement(g,pos);
    }
    display_game_status(g);
    exit(0);
	//2.1. We call to display_game_status to print the board content and the next player to move.
	//2.2. We call to get_next_movement_index to force the human player or the computer
	//to select a valid index to move for.
	//2.3. We call to process_movement to update the board content and the Game Status.

	//3. Once the game is over we call to display_game_status to print the last Game Status of the game.

}

//------------------------------------
//	14. FUNCTION update_avenue_states
//------------------------------------
void update_avenue_states(game* g, int avenue) {
	// 1. We update the state

    int tab[SIZE];

    int i=0;
    for(i=0;i<SIZE;i++){
        tab[i]=g->avenue_positions[avenue][i];
    }
    int nbX=0;
    int nbO=0;
    int nbempty=0;
    for(i=0;i<SIZE;i++)
    {
        int x = tab[i]%SIZE;
        int y = tab[i]/SIZE;
        if(g->board[x][y]=='X'){
            nbX++;
        }
        else if(g->board[x][y]=='O'){
            nbO++;
        }
        else{
            nbempty++;
        }
    }
    if(nbX==SIZE || nbO==SIZE)
    {
        g->avenue_states[avenue]=SIZE*SIZE-1;
    }
    else if(nbempty==SIZE)
    {
        g->avenue_states[avenue]=1;
    }
    else if(nbX!=0 && nbO!=0){
        g->avenue_states[avenue]=0;
    }
    else if(nbX<SIZE&&nbO==0){
        g->avenue_states[avenue]=nbX*2+1;
    }
    else if(nbO<SIZE&&nbX==0){
        g->avenue_states[avenue]=nbO*2+2;
    }

	// CASE State 1 --> We keep still at State 1.

	// CASE State 2 --> If Player1 is moving --> State 3.
	//					If Player2 is moving --> State 4.

	// CASE State 3 --> If Player1 is moving --> State 5.
	//					If Player2 is moving --> State 1.

	// CASE State 4 --> If Player1 is moving --> State 1.
	//					If Player2 is moving --> State 6.

	// CASE State 5 --> If Player1 is moving --> State 7.
	//					If Player2 is moving --> State 1.

	// CASE State 6 --> If Player1 is moving --> State 1.
	//					If Player2 is moving --> State 8.

	// CASE State 7 --> This case does not make sense, as the game is over.

	// CASE State 8 --> This case does not make sense, as the game is over.

}

//----------------------------------------
//	15. FUNCTION get_position_points
//----------------------------------------
int get_position_points(game* g, int pos) {
	//1. We create the variable to be returned
	int res = 0;
    int i=0;
    for(i=0;i<2*SIZE+2;i++)
    {
        int j=0;
        for(j=0;j<SIZE;j++)
        {
            if(g->avenue_positions[i][j]==pos)
            {
                if(g->status==2&&(g->mode==2 || g->mode==4))//les O jouent
                {
                    if(g->avenue_states[i]==2){
                        res+=1;
                    }
                    else if (g->avenue_states[i]==1){
                        res+=0;
                    }
                    else if(g->avenue_states[i]%2==0 && g->avenue_states[i]!=2)//on regarde si l'etat est a l'avantage des O
                    {
                        int puissance=(g->avenue_states[i]-2)/2;
                        res+=pow(4,puissance);
                        //state 4->4
                        //state 6->16
                        //state 8->64
                    }
                    else if (g->avenue_states[i]%2==1 && g->avenue_states[i]!=1){
                        int puissance=(g->avenue_states[i]-2)/2;
                        res+=2*pow(4,puissance);
                        //state 3->2
                        //state 5->8
                        //state 7->32
                    }
                }
                else // les X jouent
                {
                   if(g->avenue_states[i]==2){
                        res+=1;
                    }
                    else if (g->avenue_states[i]==1){
                        res+=0;
                    }
                    else if(g->avenue_states[i]%2==0 && g->avenue_states[i]!=2)//on regarde si l'etat est a l'avantage des O
                    {
                        int puissance=(g->avenue_states[i]-3)/2;
                        res+=2*pow(4,puissance);
                        //state 4->4
                        //state 6->16
                        //state 8->64
                    }
                    else if (g->avenue_states[i]%2==1 && g->avenue_states[i]!=1){// on regarde si l'avantage est au X
                        int puissance=(g->avenue_states[i]-1)/2;
                        res+=pow(4,puissance);
                        //state 3->2
                        //state 5->8
                        //state 7->32
                    }
                }
            }
        }
    }
	//2. We traverse the 8 avenues, to see if pos in on it.
	//Remember that each pos will belong to multiple avenues:
	//pos = 1; pos = 3; pos = 5; pos = 7 belong to 2 avenues.
	//pos = 0; pos = 2; pos = 6; pos = 8 belong to 3 avenues.
	//pos = 4 belongs to 4 avenues.

	//For each avenue pos belongs to, it gets points from it.
	//How many points? It depends of the state of the avenue.
	// CASE State 1 --> 0 points.

	// CASE State 2 --> 1 point.
	//

	// CASE State 3 --> If Player1 is moving --> 4 points.
	//					If Player2 is moving --> 2 points.

	// CASE State 4 --> If Player1 is moving --> 2 points.
	//					If Player2 is moving --> 4 points.

	// CASE State 5 --> If Player1 is moving --> 16 points.
	//					If Player2 is moving --> 8 points.

	// CASE State 6 --> If Player1 is moving --> 8 points.
	//					If Player2 is moving --> 16 points.

	// CASE State 7 --> This case does not make sense, as the game is over.

	// CASE State 8 --> This case does not make sense, as the game is over.


	//3. We return the accumulated amount of points of pos
	return res;
}

//----------------------------------------
//	16. FUNCTION intelligent_selection
//----------------------------------------
int intelligent_selection(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We create an auxiliary variable max_points to compute the maximum amount of points we have found so far.
    int max_points=-1;
    int i=0;
    for(i=0;i<SIZE*SIZE;i++)
    {
        if(is_position_empty(g,i)){
            int score = get_position_points(g,i);
            if (score>max_points){
                res=i;
                max_points=score;
            }
        }
    }
    printf("score:%d for pos:%d\n",max_points,res);
	//3. We traverse all the positions of boards to pick the one leading to maximum points.
	//If a position is not empty then we do not consider it.
	//If a position is empty, then we call to get_position_points to get its points.
	//We compare the result with max_points.
	//If the new position gets more points than max_points, then we update:
	//(1) The selected position and (2) The proper variable max_points with the new points computed.


	//4. We return res
	return res;
}



