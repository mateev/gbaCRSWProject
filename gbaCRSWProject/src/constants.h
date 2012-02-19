/*
	This header is for constants definitions
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WALL_BORDER_WIDTH 3			// For mouse-hit-wall mechanic
#define POP_CAP 10					// Population cap - introduced, because of practical reasons

// The followind three are building-placement constants
#define POWERPLANT_SIZE_OFFSET 2
#define BARRACKS_SIZE_OFFSET 4
#define CONCRETE_SIZE_OFFSET 6

// The following controls the time (in frames) that it takes for another unit to be trainable after one has already been trained
#define UNIT_SPAWN_COOLDOWN_PERIOD 20

#endif