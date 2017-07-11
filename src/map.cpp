/*
 *  QSokoban - Sokoban for Qtopia
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <string.h>

#include "map.h"

Map::Map() : mManX(0), mManY(0), mWidth(0), mHeight(0), mObjectives(0), mGoals(0)
{
	memset(mMap, 0, sizeof(mMap));
}

bool Map::move(int x, int y)
{
	int offx = x - mManX, offy = y - mManY;
	bool couldpush = false;

	// Next is wall, cannot move
	if (mMap[x][y] & WALL)
		return false;

	if (mMap[x][y] & OBJECT)
	{
		if ((mMap[x+offx][y+offy] & OBJECT) || (mMap[x+offx][y+offy] & WALL))
			// Next of Next is object or wall, cannot move
			return false;
		else
			// OK, we can push it
			couldpush = true;
	}
	
	// Make a step
	mMap[mManX][mManY] &=  ~MAN;
	mMap[x][y] |= MAN;
	mManX = x;
	mManY = y;

	if (couldpush)
	{
		// Move object forward
		mMap[x][y] &= ~OBJECT;
		mMap[x+offx][y+offy] |= OBJECT;

		// Calculate objectives
		if (mMap[x][y] & GOAL)
			mObjectives--;
		if (mMap[x+offx][y+offy] & GOAL)
			mObjectives++;
	}

	return true;
}

void Map::clear()
{
	memset(mMap, 0, sizeof(mMap));
	mManX = 0;
	mManY = 0;
	mWidth = 0;
	mHeight = 0;
	mObjectives = 0;
	mGoals = 0;
}

bool Map::isCompleted()
{
	if (mObjectives < mGoals)
		return false;
	else
		return true;
}

bool Map::setBit(int x, int y, int value)
{
	mMap[x][y] = value;
	
	// Calculate width and height
	if ((value != 0))
	{
		if (mWidth < (x + 1))
			mWidth = x + 1;
		if (mHeight < (y + 1))
			mHeight = y + 1;
	}

	// Oh, here is the man
	if (value & MAN)
	{
		mManX = x;
		mManY = y;
	}

	// Calculate target positions
	if (value & GOAL)
	{
		mGoals++;

		if (value & OBJECT)
			mObjectives++;
	}
}

bool Map::fillFloor(int x, int y)
{
	if ((mMap[x][y] & (WALL | FLOOR)) != 0) 
		return true;

	mMap[x][y] |= FLOOR;

	bool a = fillFloor (x, y-1);
	bool b = fillFloor (x, y+1);
	bool c = fillFloor (x-1, y);
	bool d = fillFloor (x+1, y);

	return a && b && c && d;
}



