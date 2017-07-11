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

#include "levelcollection.h"

static int minX(const char* data)
{
	int x = 0, min_x = 10000;;

	for (int index = 0; data[index]; index++) 
	{
		switch(data[index])
		{
			case '\n':
				x = 0;
		        break;

		    case ' ':
		 	 	x++;
		    	break;

		    case '\t':
				x = (x+8) & ~7;
				break;

		    case '\r':
				break;

			default:
				if (x < min_x)
					min_x = x;
				break;
		}
	}

	return min_x;
}

LevelCollection::LevelCollection(const char* start, int length, const QString& name, int id) : mName(name), mId(id), mLevelNum(0)
{
	if ((start != NULL) || (length != 0))
	{
		addData(start, length);
		addSeparator();
		indexTextCollection();
	}
}

void LevelCollection::loadLevel(int level, Map* map)
{
	int x = 0, y = 0;
	const char* data = mIndexVector[level];
	int min_x = minX(data);



	for (int index = 0; data[index]; index++)
	{
		switch(data[index])
		{
			case '\n':
				x = 0;
				y++;
				break;

			case ' ':
				x++;
				break;

			case '\t':
				x = (x + 8) & ~7;
				break;

			case '@':
				map->setBit(x - min_x, y, MAN);
				x++;
				break;

			case '$':
				map->setBit(x - min_x, y, OBJECT);
				x++;
				break;

			case '.':
				map->setBit(x - min_x, y, GOAL);
				x++;
				break;

			case '#':
				map->setBit(x - min_x, y, WALL);
				x++;
				break;

			case '+':
				map->setBit(x - min_x, y, GOAL | MAN);
				x++;
				break;

			case '*':
				map->setBit(x - min_x, y, GOAL | OBJECT);
				x++;
				break;

			case 'r':
				break;
		}
	}

	map->fillFloor(map->manX(), map->manY());
	return;
}

void LevelCollection::addData(const char* start, int length)
{
	if ((start != NULL) && (length != 0))
	{
		unsigned int index = mData.size();

		mData.resize(index + length);
		memcpy(mData.data() + index, start, length);
	}
}

void LevelCollection::addSeparator()
{
	unsigned int index = mData.size();

	mData.resize(index + 1);
	mData[index] = '\0';
}

void LevelCollection::addLevel(const char* index)
{
	if (index != NULL)
	{
		unsigned int s = mIndexVector.size();

		mIndexVector.insert(s, index);
		mLevelNum++;
	}
}

void LevelCollection::indexTextCollection()
{
	enum states 
	{
		BEFORE_NONE, BEFORE_VALID, BEFORE_INVALID, 
		DURING_NONE, DURING_VALID, DURING_INVALID
	} state = BEFORE_NONE;

	int levelstart = 0, levelend = 0;

	for (int index = 0; index < (mData.size() - 1); index++)
	{
		switch(state)
		{
			case BEFORE_NONE:
				switch(mData[index])
				{
					case '#': case '.': case '$': case '+': case '*': case '@':
						state = BEFORE_VALID;
						break;

					case ' ': case '\t': case '\r':
						break;

					case '\n':
						levelstart = index + 1;
						break;

					default:
						state = BEFORE_INVALID;
						break;
				}
				break;

			case BEFORE_VALID:
				switch(mData[index])
				{
					case '#': case '.': case '$': case '+': case '*': case '@':
					case ' ': case '\t': case '\r':
						break;

					case '\n':
						addLevel(mData.data() + levelstart);
						levelend = levelstart;
						state = DURING_NONE;
						break;

					default:
						state = BEFORE_INVALID;
				}
				break;

			case BEFORE_INVALID:
				switch(mData[index])
				{
					case '\n':
						levelstart = index + 1;
						state = BEFORE_NONE;
						break;
				}
				break;

			case DURING_NONE:
				switch(mData[index])
				{
					case '#': case '.': case '$': case '+': case '*': case '@':
						state = DURING_VALID;
						break;

					case ' ': case '\t': case '\r':
						break;

					case '\n':
						mData[levelend] = '\0';
						levelstart = index + 1;
						state = BEFORE_NONE;
						break;

					default:
						state = DURING_INVALID;
						break;
				}
				break;

			case DURING_VALID:
				switch(mData[index])
				{
					case '#': case '.': case '$': case '+': case '*': case '@':
					case ' ': case '\t': case '\r':
						break;

					case '\n':
						levelend = index;
						state = DURING_NONE;
						break;

					default:
						state = DURING_INVALID;
						break;
				}
				break;

			case DURING_INVALID:
				switch(mData[index])
				{
					case '\n':
						mData[levelend] = '\0';
						levelstart = index + 1;
						state = BEFORE_NONE;
						break;
				}
				break;

			default:
				break;
		}
	}

	if (state == DURING_NONE || state == DURING_INVALID)
	{
		mData[levelend] = '\0';
	}
}
