#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "main.h"



int main()
{
    struct Player player = {8, 8};
    int mapBuffer[mapHeight][mapWidth];
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
    
    drawMap(mapBuffer);
    
    movePlayer(player, mapBuffer);
}

void drawMap(int mapBuffer[mapHeight][mapWidth])
{
    int hasMap = 1;
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

void movePlayer(struct Player *player, int mapBuffer[mapHeight][mapWidth])
{
    char keyPressed;
    printf("Choose a direction: ");
    scanf(" %c", &keyPressed);

    // 1 - Left
    // 2 = Up
    // 3 = Right
    // 4 = Down
    int savedPlayerPos[2] = {player->y, player->x};

    if( keyPressed == 'Q' || keyPressed == 'q'){
        printf("player moved to left");
        --player->x;
    }
    else  if( keyPressed == 'Z' || keyPressed == 'z')
    {
        printf("player moved to up");
        --player->y;
    }
    else  if( keyPressed == 'D' || keyPressed == 'd')
    {
        printf("player moved to right");
        ++player->x;
    }
    else  if( keyPressed == 'S' || keyPressed == 's')
    {
        printf("player moved to down");
        ++player->y;
    }
    else {
        printf("invalide action");
    }

    int nextTile = mapBuffer[player->y][player->x];
    if(nextTile == 1 || nextTile == 3 || nextTile == 4 || nextTile == 6 ){
        mapBuffer[player->y][player->x] = 0;
        mapBuffer[savedPlayerPos[0]][savedPlayerPos[1]] = map[savedPlayerPos[0]][savedPlayerPos[1]];
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