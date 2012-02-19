/*
	Rendering definitions
*/

#include "GameGraphics.h"

// Initializes palette
void initializeGraphics()
{
	REG_DISPCNT = MODE4 | BG2_ENABLE;

	SetPaletteBG(SAND_COLOR, RGB(26,17,9));
	SetPaletteBG(CURSOR_INNER_COLOR, RGB(31,31,31));
	SetPaletteBG(CURSOR_OUTER_COLOR, RGB(0,0,0));
	SetPaletteBG(MENU_MAIN_COLOR, RGB(5,9,22));
	SetPaletteBG(CONCRETE_COLOR, RGB(25,26,20));
	SetPaletteBG(POWERPLANT_COLOR, RGB(0,15,0));
	SetPaletteBG(POWERPLANT_COLOR2, RGB(0,2,20));
	SetPaletteBG(POWERPLANT_COLOR3, RGB(0,20,0));

	SetPaletteBG(BARRACKS_COLOR, RGB(15,0,0));
	SetPaletteBG(BARRACKS_COLOR2, RGB(15,0,0));
	SetPaletteBG(BARRACKS_COLOR3, RGB(15,0,0));
	SetPaletteBG(BARRACKS_COLOR4, RGB(31,31,0));
	SetPaletteBG(BARRACKS_COLOR5, RGB(20,0,0));
	SetPaletteBG(BARRACKS_COLOR6, RGB(25,0,0));
	SetPaletteBG(BARRACKS_COLOR7, RGB(15,0,0));

	SetPaletteBG(UNIT_COLOR, RGB(0,31,0));
}

// This draws the cursor at a location
void drawCursor(int cursorXLocation, int cursorYLocation)
{
	PlotPixel8(cursorXLocation,cursorYLocation,CURSOR_INNER_COLOR);
}

// This decides what building the passed GameEntity is
void drawBuilding(GameEntity*& building)
{
	switch(building->contents)						// Based on the contents, calls the corresponding function
	{
	case BARRACKS:
		drawBarracks(building->x,building->y);
		return;
	case POWERPLANT:
		drawPowerPlant(building->x,building->y);
		return;
	case CONCRETE:
		drawConcrete(building->x,building->y);
		return;
	default:
		return;
	}

}

// This draws the Barracks at a location
void drawBarracks(int cursorXLocation, int cursorYLocation)
{
	for(int x = cursorXLocation-BARRACKS_SIZE_OFFSET;x<=cursorXLocation+BARRACKS_SIZE_OFFSET;x++)
	{
		for(int y=cursorYLocation-BARRACKS_SIZE_OFFSET+1;y<=cursorYLocation+BARRACKS_SIZE_OFFSET-1;y++)
		{
			PlotPixel8(x,y,BARRACKS_COLOR);
		}
	}

	for(int x = cursorXLocation-BARRACKS_SIZE_OFFSET;x<=cursorXLocation+BARRACKS_SIZE_OFFSET;x++)
	{
		PlotPixel8(x,cursorYLocation-BARRACKS_SIZE_OFFSET,BARRACKS_COLOR2);
		PlotPixel8(x,cursorYLocation+BARRACKS_SIZE_OFFSET,BARRACKS_COLOR2);
	}

	PlotPixel8(cursorXLocation,cursorYLocation-BARRACKS_SIZE_OFFSET,BARRACKS_COLOR3);
	PlotPixel8(cursorXLocation,cursorYLocation+BARRACKS_SIZE_OFFSET,BARRACKS_COLOR3);

	PlotPixel8(cursorXLocation+1,cursorYLocation+1,BARRACKS_COLOR4);
}

// This draws the Power Plant at a location
void drawPowerPlant(int cursorXLocation, int cursorYLocation)
{
	for(int x = cursorXLocation-POWERPLANT_SIZE_OFFSET;x<=cursorXLocation+POWERPLANT_SIZE_OFFSET;x++)
	{
		for(int y=cursorYLocation-POWERPLANT_SIZE_OFFSET;y<=cursorYLocation+POWERPLANT_SIZE_OFFSET;y++)
		{
			PlotPixel8(x,y,POWERPLANT_COLOR);
		}
	}
	
	PlotPixel8(cursorXLocation-1,cursorYLocation,POWERPLANT_COLOR2);
	PlotPixel8(cursorXLocation+1,cursorYLocation,POWERPLANT_COLOR2);
	PlotPixel8(cursorXLocation,cursorYLocation-1,POWERPLANT_COLOR2);
	PlotPixel8(cursorXLocation,cursorYLocation+1,POWERPLANT_COLOR2);

	PlotPixel8(cursorXLocation-2,cursorYLocation,POWERPLANT_COLOR3);
	PlotPixel8(cursorXLocation+2,cursorYLocation,POWERPLANT_COLOR3);
	PlotPixel8(cursorXLocation,cursorYLocation-2,POWERPLANT_COLOR3);
	PlotPixel8(cursorXLocation,cursorYLocation+2,POWERPLANT_COLOR3);
	
}

// This draws Concrete at a location
void drawConcrete(int cursorXLocation, int cursorYLocation)
{
	for(int x = cursorXLocation-CONCRETE_SIZE_OFFSET;x<=cursorXLocation+CONCRETE_SIZE_OFFSET;x++)
	{
		for(int y=cursorYLocation-CONCRETE_SIZE_OFFSET;y<=cursorYLocation+CONCRETE_SIZE_OFFSET;y++)
		{
			PlotPixel8(x,y,CONCRETE_COLOR);
		}
	}
}

// This draws a single unit at a location
void drawUnit(int x, int y)
{
	PlotPixel8(x,y,UNIT_COLOR);
}

// This draws units and buildings
void render(GameEntity*& buildingsContainer,GameEntity*& unitsContainer)
{
	if(buildingsContainer!=NULL)
	{
		for(GameEntity* buildingsIterator = buildingsContainer; buildingsIterator!=NULL; buildingsIterator=buildingsIterator->next)
		{
			drawBuilding(buildingsIterator);
		}
	}

	if(unitsContainer!=NULL)
	{
		for(GameEntity* unitsIterator = unitsContainer; unitsIterator!=NULL; unitsIterator=unitsIterator->next)
		{
			drawUnit(unitsIterator->x,unitsIterator->y);
		}
	}
}

void animateBarracks(uint16_t& frame)
{
	if(frame>20 && frame<80)
	{
		if(frame%2==0)
		{
			SetPaletteBG(BARRACKS_COLOR2,BARRACKS_COLOR5);
			SetPaletteBG(BARRACKS_COLOR3,BARRACKS_COLOR6);
		}
		if(frame%5==0)
		{
			SetPaletteBG(BARRACKS_COLOR5,BARRACKS_COLOR2);
			SetPaletteBG(BARRACKS_COLOR6,BARRACKS_COLOR3);
		}
	}

	if(frame%10==0)
		SetPaletteBG(BARRACKS_COLOR4,BARRACKS_COLOR7);
	else
		SetPaletteBG(BARRACKS_COLOR7,BARRACKS_COLOR4);
}

void animatePowerPlant(uint16_t& frame)
{
	if(frame%3==0)
	{
		SetPaletteBG(POWERPLANT_COLOR2,GetPaletteBG(POWERPLANT_COLOR3));
	}
	else
	{
		SetPaletteBG(POWERPLANT_COLOR2,GetPaletteBG(POWERPLANT_COLOR));
	}
}




