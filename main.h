typedef struct Inventory {
    int slot;
    int item;
} inventory_t;

typedef struct Player {
    // player position
    int x;
    int y;
    inventory_t inventory;
} player_t;

void drawMap(int mapBuffer[20][20]);
void movePlayer(struct Player *player, int mapBuffer[20][20]);
void gameRuntime(struct Player *player, int mapBuffer[20][20]);
void createMapBuffer(struct Player *player, int map[20][20], int mapBuffer[20][20]);