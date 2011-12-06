//================
//    HEADERS
//================
#include <stdint.h>
#include "gba.h"

#define SIDEBAR_WIDTH 60
#define MAP_SEPERATOR 100
#define SIDEBAR_START SCREEN_WIDTH-SIDEBAR_WIDTH

//================
//   Function: main()
//      Notes: Main entry point into rom
//================

enum color
{
	SAND_COLOR = 0,
	CURSOR_INNER_COLOR,
	CURSOR_OUTER_COLOR,
	MENU_MAIN_COLOR,
	MENU_BCKGR_COLOR
};

void paintGround();						// [TODO: Refer to exhibit a about painting sand texture]

void moveCursor(int&,int&);				// Move cursor at x,y with end-of-screen check
void drawCursor(int,int);				// Draw cursor at x,y
bool manageWallHit(int&,int&);			// Manages wall hits and returns true if a hit has been detected

void drawSidebar();

void drawMenu();
void drawMap();
	
int main()
{
	//REG_DISPCNT (defined in gba.h) is the main display register that controls
	//the mode of operation which backgrounds are enabled and which buffer is
	//currently being drawn by the GPU.
	//this sets the screen mode to mode three and enables background 2
	//background 2 is required for all bitmap modes(3-5)
	REG_DISPCNT = MODE4 | BG2_ENABLE;

	SetPaletteBG(SAND_COLOR, RGB(26,17,9));		// Initialize base sand color (exhibit a)
	SetPaletteBG(CURSOR_INNER_COLOR, RGB(31,31,31));
	SetPaletteBG(CURSOR_OUTER_COLOR, RGB(0,0,0));
	SetPaletteBG(MENU_MAIN_COLOR, RGB(5,9,22));
	SetPaletteBG(MENU_BCKGR_COLOR, RGB(25,26,20));
		
	drawCursor(10,10);
	
	int cursorXLocation = 10;
	int cursorYLocation = 10;
	
	// hang
	while (true)
	{
		FlipBuffers();
		
		ClearScreen8(SAND_COLOR);
	
		drawSidebar();
	
		moveCursor(cursorXLocation,cursorYLocation);
		
		/*
		if(!(REG_P1 & KEY_RIGHT)==1)
			cursorXLocation++;
		*/
		
		//WaitVSync();
	}

	return 0;
}

void drawSidebar()
{
	for(int line = 0;line<SCREEN_HEIGHT;line++)	// Traverse each line
	{
		// [TODO: Research a way to speed this up ]
		for(int column = SIDEBAR_START;column<SCREEN_WIDTH;column++)
		{
			if((column<SIDEBAR_START+5)||((line>MAP_SEPERATOR) && (line<MAP_SEPERATOR+5)))
				PlotPixel8(column,line,MENU_MAIN_COLOR);				
			else
				PlotPixel8(column,line,MENU_BCKGR_COLOR);
		}	
	}
}

bool manageWallHit(int& x,int& y)
{
	bool hasHitWall = false;
	
	if(x+2>SCREEN_WIDTH)
	{
		x-=2;
		hasHitWall = true;
	}
	else if(x<2)
	{
		x+=2;
		hasHitWall = true;
	}
	
	if(y+2>SCREEN_HEIGHT)
	{
		y-=2;
		hasHitWall = true;
	}
	else if(y<2)
	{
		y+=2;
		hasHitWall = true;
	}
	
	
	return hasHitWall;
}

void moveCursor(int &_x,int &_y)
{
	if(manageWallHit(_x,_y))
	{	
		drawCursor(_x,_y);
		return;
	}
		
	if((REG_P1 & KEY_RIGHT)==0)
		_x+=2;	
	else if((REG_P1 & KEY_LEFT)==0)
		_x-=2;
		
	if((REG_P1 & KEY_UP)==0)
		_y-=2;	
	else if((REG_P1 & KEY_DOWN)==0)
		_y+=2;	
	
	drawCursor(_x,_y);
}

void drawCursor(int _x,int _y)
{
	PlotPixel8(_x,_y,CURSOR_INNER_COLOR);	
	
	for(int i = -1; i<2; i+=2)
	{
		PlotPixel8(_x+i,_y,CURSOR_OUTER_COLOR);
		PlotPixel8(_x,_y+i,CURSOR_OUTER_COLOR);
	}

//		PlotPixel8(_x,_y+i,CURSOR_OUTER_COLOR);
}
