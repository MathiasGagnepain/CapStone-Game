#define INVENTORY_SIZE 20
#define ITEM_NAME_LENGTH 30
#define PLAYER_DAMAGE 5
#define MOBS_SPAWN_RATE 10 // percentage
#define MOBS_HEALTH_POINTS 10
#define MOBS_DAMAGE 5
#define BOSS_HEALTH_POINTS 500
#define BOSS_DAMAGE 20

// DON'T TOUCH IF YOU DON'T KNOW WHAT YOU ARE DOING
const int mapWidth = 20;
const int mapHeight = 20;
int hasMap = 0;

// 0 = Player
// 1 = Path
// 2 = Loot
// 3 = Spawn Point
// 4 = Trap
// 5 = NPC
// 6 = Quest Reward
// 7 = TP
// 8 = Boss TP
// 9 = Boss
// 10 = Wall
// 11 = Mob
int map[20][20] = {
    {10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10},   
    {10,  1,   1,   1,   1,   10,  10,  10,  10,  10,  10,  10,  1,   4,   10,  1,   1,   2,   10,  10},   
    {10,  1,   10,  10,  1,   10,  10,  1,   1,   1,   7,   10,  1,   10,  10,  1,   10,  10,  10,  10},   
    {10,  1,   10,  9,   1,   10,  10,  1,   10,  1,   10,  10,  1,   10,  10,  1,   1,   6,   1,   10},   
    {10,  1,   10,  10,  10,  10,  10,  1,   10,  1,   1,   1,   1,   10,  10,  1,   10,  10,  1,   10},   
    {10,  1,   10,  10,  1,   1,   1,   1,   10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  1,   10},   
    {10,  1,   10,  10,  1,   10,  10,  6,   5,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   10},   
    {10,  1,   10,  10,  1,   1,   1,   10,  10,  10,  1,   10,  10,  10,  10,  10,  10,  1,   10,  10},   
    {10,  1,   1,   10,  10,  10,  1,   10,  3,   1,   1,   10,  1,   1,   6,   8,   10,  1,   10,  10},   
    {10,  10,  1,   10,  10,  1,   1,   10,  10,  10,  1,   10,  1,   10,  10,  10,  10,  1,   10,  10},   
    {10,  10,  1,   10,  10,  1,   10,  10,  10,  10,  1,   10,  1,   10,  10,  10,  10,  1,   10,  10},   
    {10,  8,   1,   10,  10,  1,   1,   1,   1,   10,  1,   10,  1,   1,   1,   1,   1,   1,   5,   10},   
    {10,  10,  10,  10,  10,  10,  10,  10,  1,   10,  1,   10,  10,  10,  10,  10,  10,  10,  10,  10},   
    {10,  10,  10,  10,  10,  10,  10,  7,   1,   10,  1,   1,   1,   1,   1,   1,   1,   1,   5,   10},   
    {10,  11,  11,  11,  11,  10,  10,  10,  10,  10,  1,   10,  10,  10,  10,  10,  10,  10,  10,  10},   
    {10,  11,  10,  10,  11,  10,  1,   1,   4,   1,   1,   10,  10,  11,  11,  11,  11,  10,  10,  10},   
    {10,  11,  10,  11,  11,  10,  10,  10,  10,  10,  10,  10,  10,  11,  10,  10,  11,  10,  2,   10},   
    {10,  7,   10,  11,  10,  11,  11,  11,  10,  11,  11,  11,  10,  11,  10,  4,   11,  11,  11,  10},   
    {10,  10,  11,  11,  11,  11,   10, 11,  11,  11,   10, 11,  11,  11,  10,  10,  4,   10,  10,  10},   
    {10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10}
};