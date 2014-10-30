//
//  GameConfig.h
//  VitrumPuzzle
//
//  Created by NorthSouth Studios on 10/15/14.
//
//

#ifndef VitrumPuzzle_GameConfig_h
#define VitrumPuzzle_GameConfig_h

// AppDelegate configuration
#define DISPLAY_STATS true
#define GAME_NAME "Vitrum Puzzle"

// World configuration
#define MIN_ZINDEX -999999

// TMX Data
#define TMX_LAYER_PISO "piso"
#define TMX_LAYER_MUROS "muros"
#define TMX_LAYER_ELEMENTOS "elementos"
#define TMX_OBJECT_OBJETOS "objetos"
#define TMX_OBJECT_GAME "game"

// Data de objetos en los TMX
// Arrows names
#define NAME_ARROW_LEFT "arrow_left"
#define NAME_ARROW_RIGHT "arrow_right"
#define NAME_ARROW_UP "arrow_up"
#define NAME_ARROW_DOWN "arrow_down"

// Money names
#define NAME_MONEY_GOLD "gold"
#define NAME_MONEY_DIAMOND "diamond"

// Trap names
#define NAME_TRAP_HOLE "hole"

// Obstacles names
#define NAME_OBSTACLE_ROCK1 "rock1"

// Paths names
#define NAME_PLAYER_START "player_start"
#define NAME_PLAYER_END "player_end"
#define NAME_PATH_LAND "normal_land"

// Teleport names

// Switch names

// Types
#define TYPE_ARROW "arrow"
#define TYPE_OBSTACLE "obstacle"
#define TYPE_MONEY "money"
#define TYPE_TRAP "trap"
#define TYPE_PATH "path"
#define TYPE_TELEPORT "teleport"
#define TYPE_SWITCH "switch"
#define TYPE_PLAYER_START "player_start"
#define TYPE_PLAYER_END "player_end"

// Game Constants
#define SWIPE_TIME 0.5f
#define SWIPE_FORCE 80.0f
#define PLAYER_SPEED 0.05f
#define SCREEN_WIDTH 1024.0f
#define SCREEN_HEIGHT 768.0f

// Swipe states
typedef enum {
    kDirectionNone = 0,
    kDirectionLeft,
    kDirectionRight,
    kDirectionUp,
    kDirectionDown
} DirectionState;

extern int level;


#endif
