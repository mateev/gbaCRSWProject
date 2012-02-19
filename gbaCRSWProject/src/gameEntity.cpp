/*
	GameEntity definitions
*/

#include "GameEntity.h"


bool GameEntity::PowerPlantExists = false;
bool GameEntity::BarracksExists = false;

// Create temporary coordinates
GameEntity::GameEntity()
{
	x = y = -1;
	next  = NULL;
}

// Creates an element by values
GameEntity::GameEntity(int& inputX, int& inputY, Type& inputContents)
{
	x = inputX;
	y = inputY;
	contents = inputContents;
	next  = NULL;
}

// Creates an element; doesn't deep copy!!!
GameEntity::GameEntity(GameEntity& other)
{
	x = other.x;
	y = other.y;
	contents = other.contents;

	next = NULL;
}

// Updates current pair's coordinates
void GameEntity::update(int& inputX, int& inputY)
{
	x = inputX;
	y = inputY;
}

// Updates current pair
void GameEntity::update(int& inputX, int& inputY, Type& inputContents)
{
	x = inputX;
	y = inputY;
	contents = inputContents;
}

// Add a new element to the end by values
void GameEntity::add(int& inputX, int& inputY, Type& inputContents)
{
	GameEntity* lastElement = getLast();								// Find last element ...

	lastElement->next = new GameEntity(inputX,inputY,inputContents);	// ... and create a new element after it.

}

// Add a new element to the end by object
void GameEntity::add(GameEntity& other)
{
	add(other.x,other.y,other.contents);									// Implemented using add-by-value
}

// Gets last element
GameEntity* GameEntity::getLast()
{
	GameEntity* returnValue = this;						// This finds the last element ...

	while(returnValue->next!=NULL)							// ... by iterating over the list ...
		returnValue = returnValue->next;

	return returnValue;										// ... and returning :-)
}

// Gets next element
GameEntity* GameEntity::getNext()
{
	return next;
}

// Delete the last element
void GameEntity::deleteLast()
{
	GameEntity* last = getLast();						// Get the last element

	if(this == last)										// If we are at the last element
	{
		next = NULL;										// clean up
		return;												// and return
	}

	GameEntity* preLast = this;							// This will find the last element ...

	while(preLast->next!=last)								// ... by iterating over all elements, until the next in sight is the last
		preLast=preLast->next;

	delete last;											// Then last element is deleted

	preLast->next = NULL;									// And pre-last becomes last
}

// Destructor
GameEntity::~GameEntity()
{
	while(this->next!=NULL)								// While there are elements, other than the first
		deleteLast();										// Delete the last
}