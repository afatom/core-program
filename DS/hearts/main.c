#include "round.h"
#include <stdlib.h> /*Malloc, Size_t*/
#include "player.h"
#include "game.h"
#include "ADTDefs.h"
#include "trick.h"
#include "deck.h"
#include "vector.h"
#include "card.h"
#include "mu_test.h"
#include <stdio.h>



int main (int argc, char* argv[])
{

	Game* game = NULL;   
	game = GameCreate();
	RunGame(game);
	GameDestroy(game);
return 0;
}
