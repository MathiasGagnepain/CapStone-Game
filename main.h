typedef struct Inventory {
    int slot;
    char items[INVENTORY_SIZE][ITEM_NAME_LENGTH];
} inventory_t;

typedef struct Player {
    // player position
    int x;
    int y;
    inventory_t inventory;
} player_t;

void drawMap(int mapBuffer[mapHeight][mapWidth]);
void movePlayer(struct Player *player, int mapBuffer[mapHeight][mapWidth]);
void gameRuntime(struct Player *player, int mapBuffer[mapHeight][mapWidth]);
void createMapBuffer(struct Player *player, int map[mapHeight][mapWidth], int mapBuffer[mapHeight][mapWidth]);
void collectItem(struct Player *player);

void rdmTp(struct Player *player);