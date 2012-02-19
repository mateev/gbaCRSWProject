/*
	This header controls the most basic in-game entity - the GameEntity
*/

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <cstdlib>			// needed for NULL

// Information about the type of the game entity
enum Type
{
	POWERPLANT = 1,
	CONCRETE,
	BARRACKS,
	UNIT
};

struct GameEntity
{
	static bool PowerPlantExists;	// This is to implement building dependances
	static bool BarracksExists;		// This is to implement unit dependances

	int x;							// Holds x coordinate
	int y;							// Holds y coordinate

	Type contents;				// Holds information about the contents

	GameEntity* next;			// Holds next element

	GameEntity();				// Creates a temporary element
	GameEntity(int&,int&,Type&);	// Creates an element by values
	GameEntity(GameEntity&);// Creates an element, based on another; doesn't deep copy
	
	void update(int&,int&);			// Updates values of current element, except coordinates
	void update(int&,int&, Type&);	// Updates values of current element	

	void add(GameEntity&);				// Add a new element to the end by object
	void add(int&,int&,Type&);		// Add a new element to the end by values

	GameEntity* getNext();		// Gets next element
	GameEntity* getLast();		// Gets last element

	void deleteLast();				// Deletes last element

	~GameEntity();				// Destructor
};

#endif