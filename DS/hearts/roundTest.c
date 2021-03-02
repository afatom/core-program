#include "round.h"
#include <stdlib.h> /*Malloc, Size_t*/
#include "player.h"
#include "ADTDefs.h"
#include "trick.h"
#include "deck.h"
#include "vector.h"
#include <stdlib.h>
#include "card.h"
#include "mu_test.h"
#include <stdio.h>



UNIT(Round_Create_Normal_Test)
    int i;
    SwitchCards x = RIGHT;
    Round* rnd = NULL;
    Player *arr[4] = {NULL, NULL, NULL, NULL};
    for (i = 0; i < 4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }
    ASSERT_THAT ((rnd = RoundCreate(arr, x))!=NULL);
    RoundDestroy(rnd);
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
END_UNIT

UNIT(Round_Double_Destroy_Test)
    int i;
    SwitchCards x = RIGHT;
    Round* rnd = NULL;
    Player *arr[4] = {NULL, NULL, NULL, NULL};
    for (i = 0; i < 4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }
    ASSERT_THAT ((rnd = RoundCreate(arr, x))!=NULL);
    RoundDestroy(rnd);
    RoundDestroy(rnd);
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
END_UNIT

UNIT(Round_Run_One_Round_Test)
    int i;
    SwitchCards x = RIGHT;
    Round* rnd = NULL;
    Player *arr[4] = {NULL, NULL, NULL, NULL};
    for (i = 0; i < 4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }
    ASSERT_THAT ((rnd = RoundCreate(arr, x))!=NULL);
    ASSERT_THAT (RoundRunTheGame(rnd));
    RoundDestroy(rnd);
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
    RoundDestroy(rnd);
END_UNIT

UNIT(Round_Run_3_Rounds_Test)
    int i;
    SwitchCards x = RIGHT;
    Round* rnd = NULL;
    Player *arr[4] = {NULL, NULL, NULL, NULL};
    for (i = 0; i < 4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }
    for (i = 0; i < 3; ++i)
    {
        ASSERT_THAT ((rnd = RoundCreate(arr, x))!=NULL);
        ASSERT_THAT (RoundRunTheGame(rnd));
        RoundDestroy(rnd);
    }
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
END_UNIT

UNIT(Round_Run_13_Rounds_Test)
    int i;
    SwitchCards x = RIGHT;
    Round* rnd = NULL;
    Player *arr[4] = {NULL, NULL, NULL, NULL};
    for (i = 0; i < 4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }
    for (i = 0; i < 13; ++i)
    {
        ASSERT_THAT ((rnd = RoundCreate(arr, x))!=NULL);
        ASSERT_THAT (RoundRunTheGame(rnd));
        RoundDestroy(rnd);
    }
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
END_UNIT

TEST_SUITE(Round Module Tests)
    TEST(Round_Create_Normal_Test)
    TEST(Round_Double_Destroy_Test)
    TEST(Round_Run_One_Round_Test)
    TEST(Round_Run_3_Rounds_Test)
    TEST(Round_Run_13_Rounds_Test)
END_SUITE