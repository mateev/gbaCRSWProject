/*
	Game logic definitions
*/

#include "gameLogic.h"

// Returns true if the passed MouseType is among MOVE_LEFT, MOVE_RIGHT, MOVE_UP or MOVE_DOWN
bool isMovement(MouseType& mouseObject)
{
	return (mouseObject>=MOVE_LEFT) && (mouseObject<=MOVE_DOWN);
}

// Returns true if the passed MouseType is among PLACE_POWERPLANT, PLACE_CONCRETE or PLACE_BARRACKS
bool isPlacement(MouseType& mouseObject)
{
	return (mouseObject <= PLACE_BARRACKS) && (mouseObject >= PLACE_POWERPLANT);
}

// Returns true if the passed MouseType is SPAWN_UNIT
bool isSpawning(MouseType& mouseObject)
{
	return mouseObject==SPAWN_UNIT;
}

// Returns the current status of the mouse
MouseType updatedMouseType()
{
	if((REG_P1 & KEY_A) == 0)
		return PLACE_BARRACKS;
	else if((REG_P1 & KEY_B) == 0)
		return PLACE_POWERPLANT;
	else if((REG_P1 & KEY_L) == 0)
		return PLACE_CONCRETE;
	else if((REG_P1 & KEY_R) == 0)
		return SPAWN_UNIT;

	if((REG_P1 & KEY_LEFT) == 0)
		return MOVE_LEFT;
	else if((REG_P1 & KEY_RIGHT) ==0)
		return MOVE_RIGHT;
	else if((REG_P1 & KEY_UP)==0)
		return MOVE_UP;
	else if((REG_P1 & KEY_DOWN)==0)
		return MOVE_DOWN;

	return IDLE;
}

// Makes sure the mouse is WALL_BORDER_WIDTH-pixels away from screen edge
void manageWallHit(int &cursorXLocation, int &cursorYLocation)
{
	if(SCREEN_WIDTH-cursorXLocation<WALL_BORDER_WIDTH)
	{
		cursorXLocation=SCREEN_WIDTH-WALL_BORDER_WIDTH;
	}
	else if(cursorXLocation<WALL_BORDER_WIDTH)
	{
		cursorXLocation=WALL_BORDER_WIDTH;
	}

	if(SCREEN_HEIGHT-cursorYLocation<WALL_BORDER_WIDTH)
	{
		cursorYLocation=SCREEN_HEIGHT-WALL_BORDER_WIDTH;
	}
	else if(cursorYLocation<WALL_BORDER_WIDTH)
	{
		cursorYLocation=WALL_BORDER_WIDTH;
	}
}

// Returns VERTICAL or HORIZONTAL
Edge randomEdge()
{
	return randomSign() == -1 ? VERTICAL : HORIZONTAL;	// implemented via randomSign()
}

// Returns -1 or 1
int randomSign()
{
	return rand()%2 == 0 ? -1 : 1;	
}

// Controls unit training
void spawn(GameEntity*& gameUnits,GameEntity*& gameBuildings)
{
	if(!GameEntity::BarracksExists)						// If there is no barracks ...
		return;											// ... can't train a unit, so pass

	int spawnPointX, spawnPointY;						// Unit location candidate variables
	Type unitType = UNIT;							    // Since GameEntity::add needs an argument by reference

	GameEntity* barracksFinder = gameBuildings;			// We want to spawn from the first possible barracks, so we select the buildings list ...

	while(barracksFinder->contents!=BARRACKS)			// ... and until we find a barracks ...
		barracksFinder=barracksFinder->next;				// ... we iterate over the list.

	
	do													// To pick a place where to put the unit ...
	{													// ... we get a possible location ...
		switch(randomEdge())							// We first pick along which edge will the unit appear where 0 is vertical and 1 is horizontal
		{
		case VERTICAL:				// ... it will be along a vertical edge ...
			spawnPointY = barracksFinder->y + randomSign()*(rand() % (2 + BARRACKS_SIZE_OFFSET) );	// somewhere along the line
			spawnPointX = barracksFinder->x + (randomSign() * (2 + BARRACKS_SIZE_OFFSET));	// either on the left or on the right;
			break;
		case HORIZONTAL:				// ... it will be along a horizontal edge ...
			spawnPointX = barracksFinder->x + (rand() % (2 + BARRACKS_SIZE_OFFSET));	// somewhere along the line
			spawnPointY = barracksFinder->y + randomSign()*(randomSign() * (2 + BARRACKS_SIZE_OFFSET));	// either on the top or on the bottom;
			break;
		}

	}
	while(!isValidSpawnPoint(spawnPointX,spawnPointY));	// ... we try a new location until a free one becomes available
	

	if(gameUnits==NULL)														// If there are currently no units in-game ...
		gameUnits = new GameEntity(spawnPointX, spawnPointY, unitType);			// ... we create the units list..
	else
		gameUnits->add(spawnPointX, spawnPointY, unitType);					// ... or else we add a new unit to the list

}

// Controls building placement
void place(int& cursorXLocation,int& cursorYLocation,MouseType& mouseObject,GameEntity*& buildingsContainer)
{	
	
	// This big if checks if we are doing a correct placement and if building prerequisites have been met...
	if(																																
		((mouseObject==PLACE_CONCRETE) && !canDrawConcrete(cursorXLocation,cursorYLocation))		||								
		((mouseObject==PLACE_POWERPLANT) && !canDrawPowerPlant(cursorXLocation,cursorYLocation))	||
		((mouseObject==PLACE_BARRACKS) && (!GameEntity::PowerPlantExists || !canDrawBarracks(cursorXLocation,cursorYLocation)))	
		)
		return; // ... can't place, so exit.


	Type contents = getTypeFromMouse(mouseObject);											// First we extract information about what we are placing from the mouse

	// The following is related to building/unit prerequisites
	if(mouseObject==PLACE_POWERPLANT)														// If the building being placed is a powerplant ...
		GameEntity::PowerPlantExists=true;														// ... we denote that a power plant has been placed, so now one exists
	else if(mouseObject==PLACE_BARRACKS)													// If it's a barracks
		GameEntity::BarracksExists=true;														// ... we repeat the same

	if(buildingsContainer==NULL)															// If there haven't been any building placed yet ...
		buildingsContainer=new GameEntity(cursorXLocation,cursorYLocation,contents);			// ... we create the buildings list, starting with our new building.
	else
		buildingsContainer->add(cursorXLocation,cursorYLocation,contents);						// ... or else we add the new building to the end of the list
}

// Makes the mouse move, based on the passed MouseType
void move(int& cursorXLocation, int& cursorYLocation, MouseType& mouseObject)
{
	switch(mouseObject)
	{
	case MOVE_LEFT:
		cursorXLocation--;
		break;
	case MOVE_RIGHT:
		cursorXLocation++;
		break;
	case MOVE_UP:
		cursorYLocation--;
		break;
	case MOVE_DOWN:
		cursorYLocation++;
		break;
	default:
		return;
	}

	manageWallHit(cursorXLocation,cursorYLocation);
}

// Returns true if the "ground" square of size BARRACKS_SIZE_OFFSET at a location is CONCRETE_COLOR		
bool canDrawBarracks(int &xLocation, int &yLocation)
{
	for(int x = xLocation-BARRACKS_SIZE_OFFSET;x<=xLocation+BARRACKS_SIZE_OFFSET;x++)
	{
		for(int y=yLocation-BARRACKS_SIZE_OFFSET;y<=yLocation+BARRACKS_SIZE_OFFSET;y++)
		{
			if(GetPixel8(x,y)!=CONCRETE_COLOR)
				return false;
		}
	}

	return true;
}

// Returns true if the "ground" square of size POWERPLANT_SIZE_OFFSET at a location is CONCRETE_COLOR
bool canDrawPowerPlant(int &xLocation, int &yLocation)
{
	for(int x = xLocation-POWERPLANT_SIZE_OFFSET;x<=xLocation+POWERPLANT_SIZE_OFFSET;x++)
	{
		for(int y=yLocation-POWERPLANT_SIZE_OFFSET;y<=yLocation+POWERPLANT_SIZE_OFFSET;y++)
		{
			if(GetPixel8(x,y)!=CONCRETE_COLOR)
				return false;
		}
	}

	return true;
}

// Returns true if the "ground" square of size CONCRETE_SIZE_OFFSET at a location is SAND_COLOR
bool canDrawConcrete(int &xLocation, int &yLocation)
{
	for(int x = xLocation-CONCRETE_SIZE_OFFSET;x<=xLocation+CONCRETE_SIZE_OFFSET;x++)
	{
		for(int y=yLocation-CONCRETE_SIZE_OFFSET;y<=yLocation+CONCRETE_SIZE_OFFSET;y++)
		{
			if((GetPixel8(x,y)!=SAND_COLOR))
				return false;
		}
	}

	return true;
}

// Returns true if the "ground" pixel at a location is SAND_COLOR or CONCRETE_COLOR
bool isValidSpawnPoint(int &pixelXLocation, int &pixelYLocation)
{
	return ((GetPixel8(pixelXLocation,pixelYLocation)==SAND_COLOR) || (GetPixel8(pixelXLocation,pixelYLocation)==CONCRETE_COLOR));
}

// Converts MouseType to Type for building placement
Type getTypeFromMouse(MouseType& mouseObject)
{
	return (Type)(int)mouseObject;
}