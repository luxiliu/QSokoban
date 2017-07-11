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

#ifndef _MAP_H
#define _MAP_H

#define MAX_X 49
#define MAX_Y 49

#define WALL   1
#define GOAL   2
#define OBJECT 4
#define FLOOR  8
#define MAN	   16

class Map 
{
	friend class LevelCollection;

public:
	Map();

	int getBit(int x, int y) { return mMap[x][y]; }

	int manX() { return mManX; }
	int manY() { return mManY; }

	int width() { return mWidth; }
	int height() { return mHeight; }

	bool move(int x, int y);
	void clear();
	bool isCompleted();

protected:
	bool setBit(int x, int y, int value);
	bool fillFloor(int x, int y);

private:
	int mManX;
	int mManY;
	int mWidth;
	int mHeight;
	char mMap[MAX_X][MAX_Y];
	int mObjectives;
	int mGoals;
};

#endif /* _MAP_H */
