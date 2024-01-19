#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "main.h"



int main()
{
    struct Player player = {100, 8, 8};
    int mapBuffer[mapHeight][mapWidth];

    mobsGeneration();
    createMapBuffer(&player, map, mapBuffer);

    gameRuntime(&player, mapBuffer);
    exit(EXIT_SUCCESS);
}

void createMapBuffer(struct Player *player, int map[mapHeight][mapWidth], int mapBuffer[mapHeight][mapWidth]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            mapBuffer[i][j] = map[i][j];
        }
    }
    mapBuffer[player->y][player->x] = 0;
}

void gameRuntime(struct Player *player, int mapBuffer[mapHeight][mapWidth])
{
    printf("\e[1;1H\e[2J");

   

    drawMap(mapBuffer);
    
    displayInv(player);

    movePlayer(player, mapBuffer);
}

void drawMap(int mapBuffer[mapHeight][mapWidth])
{
    for(int i = 0;i < mapHeight;i++){

        for(int j = 0;j < mapWidth;j++){
            if (hasMap == 1 || mapBuffer[i][j] == 0){
                switch(mapBuffer[i][j]){
                    case 0:
                        printf("\033[0;34m P \033[0m");
                        break;
                    case 1:
                        printf("   ");
                        break;
                    case 2:
                        printf("\033[0;32m $ \033[0m");
                        break;
                    case 3:
                        printf("   ");
                        break;
                    case 4:
                        printf("   ");
                        break;
                    case 5:
                        printf(" N ");
                        break;
                    case 6:
                        printf("   ");
                        break;
                    case 7:
                        printf(" ■ ");
                        break;
                    case 8:
                        printf(" ■ ");
                        break;
                    case 9:
                        printf(" ☢ ");
                        break;
                    case 10:
                            printf("███");
                        break;
                    case 11:
                            printf(" X ");
                        break;
                    default:
                        printf("XXX");
                        printf("\n\n\n\033[0;31mERROR: Tile not found !\033[0m\n\n\n");
                        exit(EXIT_SUCCESS);
                } 
            }else{
                printf("   ");
            }
        }
        printf("\n");
    }
}

void displayInv(struct Player *player)
{
    printf("\n--------------------\n");
    printf("\nYour inventory: \n\n");
    for (int i = 0; i < player->inventory.slot; ++i){
        int result = strcmp(player->inventory.items[i], "handmap");
        if (result == 0){
            hasMap = 1;
        }

        printf("[%d] - %s\n", i, player->inventory.items[i]);
    }
    printf("\n--------------------\n");
}

void movePlayer(struct Player *player, int mapBuffer[mapHeight][mapWidth])
{
    char keyPressed;
    printf("Z = Up | S = Down | Q = Left | D = Right");
    printf("\n--------------------\n");
    printf("Choose a action: ");
    scanf(" %c", &keyPressed);

    // 1 - Left
    // 2 = Up
    // 3 = Right
    // 4 = Down
    int savedPlayerPos[2] = {player->y, player->x};

    switch (keyPressed)
    {
        case 'Q':
        case 'q':
            --player->x;
            break;

        case 'Z':
        case 'z':
            --player->y;
            break;

        case 'D':
        case 'd':
            ++player->x;
            break;

        case 'S':
        case 's':
            ++player->y;
            break;
        
        default:
            printf("action not found !");
            break;
    }

    int nextTile = mapBuffer[player->y][player->x];
    if(nextTile == 1 || nextTile == 3 || nextTile == 4 || nextTile == 6 || nextTile == 2 || nextTile == 7 || nextTile == 8 || nextTile == 5 || nextTile == 11){
        mapBuffer[player->y][player->x] = 0;
        mapBuffer[savedPlayerPos[0]][savedPlayerPos[1]] = map[savedPlayerPos[0]][savedPlayerPos[1]];
        if (nextTile == 2) {
            map[player->y][player->x] = 1;
            collectItem(player);
        } else if (nextTile == 7) {
            savedPlayerPos[0] = player->y;
            savedPlayerPos[1] = player->x;
            rdmTp(player);
            mapBuffer[player->y][player->x] = 0;
            mapBuffer[savedPlayerPos[0]][savedPlayerPos[1]] = map[savedPlayerPos[0]][savedPlayerPos[1]];
            if (player->x == 1 && player->y == 17 ){
                map[player->y][player->x] = 1;
            }
        } else if (nextTile == 8){
            savedPlayerPos[0] = player->y;
            savedPlayerPos[1] = player->x;

            if (player->x == 15 && player->y == 8 ){
                player->x = 1;
                player->y = 11;

            } else {
                player->x = 15;
                player->y = 8;
            }

            mapBuffer[player->y][player->x] = 0;
            mapBuffer[savedPlayerPos[0]][savedPlayerPos[1]] = map[savedPlayerPos[0]][savedPlayerPos[1]];
            if (player->x == 1 && player->y == 17 ){
                map[player->y][player->x] = 1;
            }
        } else if (nextTile == 11){
            startFight(player);
        }
    } else {
       player->y = savedPlayerPos[0];
       player->x = savedPlayerPos[1];
    }

    mapBuffer[player->y][player->x] = 0;
    printf("\n%d", player->x);
    printf("\n%d", player->y);
    printf("\n");
    gameRuntime(player, mapBuffer);
}

void collectItem(struct Player *player){
    char newItem[ITEM_NAME_LENGTH];
    if (player->x == 17 && player->y == 1 ){
        strncpy(newItem, "handmap", ITEM_NAME_LENGTH - 1);
        newItem[ITEM_NAME_LENGTH - 1] = '\0';
    }

    if (newItem != NULL){
        strncpy(player->inventory.items[player->inventory.slot], newItem, ITEM_NAME_LENGTH - 1);
        player->inventory.items[player->inventory.slot][ITEM_NAME_LENGTH - 1] = "\0";
        ++player->inventory.slot;
        printf("you loot: %s", newItem);
    }
}

void startFight(struct Player *player)
{
    int inFight = 1;
    srand(time(NULL));
    while (inFight){
        char choice;
        int min = 1;
        int max = 3;
        int mobChoice = rand() % (max - min + 1) + min;

        printf("[1] - Fight\n");
        printf("[2] - Flee\n");
        printf("Choose an action: ");
        scanf(" %c", &choice);
        switch (choice)
        {
        case '1':
            printf("Choose a number between 1 and 3: ");
            scanf(" %c", &choice);
            printf("the creature did %d\n", mobChoice);
            if (choice == mobChoice + '0')
             {
                printf("You hurt him\n\n");
             } else {
                printf("You has been hurt\n\n");
                player->hp = player->hp - MOBS_DAMAGE;
             }
            break;
        case '2':
            printf("Choose a number between 1 and 3: ");
            scanf(" %c", &choice);
            printf("the creature did %d\n", mobChoice);
            if (choice == mobChoice + '0')
            {
                printf("You flee him\n\n");
                inFight = 0;
            }else{
                printf("You has been hurt\n\n");
                player->hp = player->hp - MOBS_DAMAGE;
            }
            break;
        default:
            break;
        }

        if (player->hp <= 0) {
            inFight = 0;
            printf("YOU ARE DEAD !!!\n");

            printf("Press a key to restart");
            scanf(" %c", &choice);
            main();
        }
    }
}

void mobsGeneration(){
    srand(time(NULL));
    int min = 0;
    int max = 100;

    for (int i = 0; i < mapHeight; ++i)
    {
        for (int j = 0; j < mapWidth; ++j)
        {
            if (map[i][j] == 1)
            {
                int spawnChance = rand() % (max - min + 1) + min;
                if (spawnChance <= MOBS_SPAWN_RATE)
                {
                    map[i][j] = 11;
                }
            }
        }
    }
}

void rdmTp(struct Player *player){
    int min = 1;
    int max = 4;
    int validTP = 0;
    srand(time(NULL));

    while (!validTP) {
        int tpNum = rand() % (max - min + 1) + min;

        switch (tpNum)
        {
        case 1:
            if (player->x != 8 && player->y != 8)
            {
                validTP = 1;
                player->x = 8;
                player->y = 8;
            }
            break;
        case 2:
            if (player->x != 10 && player->y != 2)
            {
                validTP = 1;
                player->x = 10;
                player->y = 2;
            }
            break;
        case 3:
            if (player->x != 7 && player->y != 13)
            {
                validTP = 1;
                player->x = 7;
                player->y = 13;
            }
            break;
        case 4:
            if (player->x != 1 && player->y != 17)
            {
                validTP = 1;
                player->x = 1;
                player->y = 17;
            }  
        }
    }
}


// TO DO
/*
on fight give 2 action possible:
1 - Fight
2 - Flee

choose a number between 1 and 3:
    - if same number of the mobs you win
    - if you pick another number you lose
*/