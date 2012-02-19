/*
	This header holds game logic
*/

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "GameEntity.h"
#include "colors.h"
#include "constants.h"
#include "gba.h"
#include <cstdlib>

// Information about the current mouse status
enum MouseType
{
	IDLE = 0,
	PLACE_POWERPLANT,
	PLACE_CONCRETE,
	PLACE_BARRACKS,
	SPAWN_UNIT,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};

// Used when training units - helps decide whether a unit should be spawned above/below or left/right of the barracks
enum Edge
{
	VERTICAL = 0,
	HORIZONTAL
};

int randomSign();									// Returns -1 or 1
Edge randomEdge();									// Returns VERTICAL or HORIZONTAL; implemented via randomSign()

bool isMovement(MouseType&);						// Returns true if the passed MouseType is among MOVE_LEFT, MOVE_RIGHT, MOVE_UP or MOVE_DOWN
bool isPlacement(MouseType&);						// Returns true if the passed MouseType is among PLACE_POWERPLANT, PLACE_CONCRETE or PLACE_BARRACKS
bool isSpawning(MouseType&);						// Returns true if the passed MouseType is SPAWN_UNIT

MouseType updatedMouseType();						// Returns the current status of the mouse

void move(int&, int&, MouseType&);					// Makes the mouse move, based on the passed MouseType
void manageWallHit(int &, int&);					// Makes sure the mouse is WALL_BORDER_WIDTH-pixels away from screen edge

void place(int&,int&,MouseType&,GameEntity*&);		// Controls building placement
void spawn(GameEntity*&,GameEntity*&);				// Controls unit training

bool canDrawConcrete(int&, int&);					// Returns true if the "ground" square of size CONCRETE_SIZE_OFFSET at a location is SAND_COLOR
bool canDrawPowerPlant(int&, int&);					// Returns true if the "ground" square of size POWERPLANT_SIZE_OFFSET at a location is CONCRETE_COLOR
bool canDrawBarracks(int&, int&);					// Returns true if the "ground" square of size BARRACKS_SIZE_OFFSET at a location is CONCRETE_COLOR					

bool isValidSpawnPoint(int&, int&);					// Returns true if the "ground" pixel at a location is SAND_COLOR or CONCRETE_COLOR

Type getTypeFromMouse(MouseType&);					// Converts MouseType to Type for building placement

#endif