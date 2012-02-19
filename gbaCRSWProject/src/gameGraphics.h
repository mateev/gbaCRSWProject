/*
	This header controls rendering
*/

#ifndef GAMEGRAPHICS_H
#define GAMEGRAPHICS_H

#include "GameEntity.h"
#include "colors.h"
#include "gba.h"
#include "constants.h"

void initializeGraphics();					// Initializes palette

void render(GameEntity*&,GameEntity*&);		// This draws units and buildings

void drawBuilding(GameEntity*&);			// This decides what building the passed GameEntity is
void drawConcrete(int,int);					// This draws Concrete at a location
void drawPowerPlant(int,int);				// This draws the Power Plant at a location
void drawBarracks(int,int);					// This draws the Barracks at a location

void drawUnit(int,int);						// This draws a single unit at a location

void drawCursor(int,int);					// This draws the cursor at a location


void animatePowerPlant(uint16_t&);
void animateBarracks(uint16_t&);

#endif