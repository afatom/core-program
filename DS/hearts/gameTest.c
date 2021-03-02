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


UNIT(Game_Create_Normal_Test)
    Game* game = NULL;
    game = GameCreate();
    ASSERT_THAT(game != NULL);
    GameDestroy(game); 
END_UNIT

UNIT(Game_Run_One_Game_Test)
    Game* game = NULL;
    game = GameCreate();
    ASSERT_THAT(game != NULL);
    ASSERT_THAT(RunGame(game) == ERR_OK);
    GameDestroy(game); 
END_UNIT

UNIT(Game_Run_Three_Game_Test)
    int i=0;
    Game* game = NULL;
    game = GameCreate();
    ASSERT_THAT(game != NULL);
    while( i < 3)
    {
        ASSERT_THAT (RunGame(game) == ERR_OK);
        ++i;
    }
    GameDestroy(game); 
END_UNIT

UNIT(Game_Run_Few_Test)
    int i=0;
    Game* game = NULL;
    game = GameCreate();
    ASSERT_THAT(game != NULL);
    while( i < 25)
    {
        ASSERT_THAT (RunGame(game) == ERR_OK);
        ++i;
    }
    GameDestroy(game); 
END_UNIT

TEST_SUITE(Hearts_Game_<3_Test)
    TEST(Game_Create_Normal_Test)
    TEST(Game_Run_One_Game_Test)
    TEST(Game_Run_Three_Game_Test)
    TEST(Game_Run_Few_Test)
END_SUITE