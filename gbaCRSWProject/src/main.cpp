#include "gba.h"
#include "GameGraphics.h"
#include "GameLogic.h"
#include "GameEntity.h"

int main()
{
	initializeGraphics();	

	MouseType mouseObject = IDLE;

	int cursorXLocation = 10;
	int cursorYLocation = 10;

	// These control building & unit logic
	GameEntity* buildingsContainer = NULL;
	GameEntity* unitsContainer = NULL;

	uint16_t population = 0;		// This controls population count
	uint16_t frame = 0;				// This counts frames
	uint16_t unitSpawnDelay = 0;			// This controls the delay between unit spawns

	while (true)
	{
		FlipBuffers();																				// Flip buffers
		
		ClearScreen8(SAND_COLOR);																	// Clear screen

		render(buildingsContainer,unitsContainer);													// Render all buildings and units

		animatePowerPlant(frame);																	// Animate the power plant
		animateBarracks(frame);																		// Animate the barracks

		if(mouseObject!=IDLE)																		// If there has been some mouse action ...
		{
			if(isMovement(mouseObject))																	// ... and it is movement ...
			{
				move(cursorXLocation,cursorYLocation,mouseObject);											// ... movet the mouse.
			}
			 
			else if(isPlacement(mouseObject))															// ... if it is placement ...
			{
				place(cursorXLocation,cursorYLocation,mouseObject,buildingsContainer);						// ... attempt placement.
			}

			else if(isSpawning(mouseObject) && unitSpawnDelay==0 && population!=POP_CAP)				// ... if it is a unit and it's not to soon after the last unit was trained and population cap has not been reached  ...
			{														
				spawn(unitsContainer,buildingsContainer);													// place the unit
				population++;																				// increase population

				unitSpawnDelay = UNIT_SPAWN_COOLDOWN_PERIOD;												// start cooldown timer
			}
		}

		drawCursor(cursorXLocation,cursorYLocation);												// Draw the cursor

		mouseObject = updatedMouseType();															// Update the mouse

		WaitVSync();																				// Sync

		frame = (frame == 100) ? 0 : frame+1;														//	Reset frame count every 100 frames, else increase by one

		if(unitSpawnDelay!=0)																		// If there is a cooldown timer in action ...
			unitSpawnDelay--;																			// ... update it!

	}
	
	// We are environmentaly concious, so we clean after ourselves
	delete buildingsContainer;					
	delete unitsContainer;

	return 0;
}

