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

#include <stdlib.h>
#include <ctype.h>

#include <QFile>

#include "internalcollections.h"

InternalCollections::InternalCollections() : mData(NULL)
{
	// Load level data
	QFile file(":image/level.data");
	if (!file.open(QIODevice::ReadOnly))
	{
		qWarning("Cannot open level.data.png!");
		return;
	}
	
	QByteArray ba = file.readAll();
	if (ba.size() <= 0)
	{
		qWarning("Empty file!");
		file.close();
		return;
	}

	mData = (char*) malloc(ba.size() + 1);
	memcpy(mData, ba.data(), ba.size());

	file.close();

	int levelid=0, start = 0, end = 0;
	enum {NAME, DATA} state = NAME;
	static QString levelname;

	// Parse level data file
	while(end < ba.size())
	{
		switch(state)
		{
			case NAME:
      			if (mData[end] == '\n') 
				{
					mData[end] = '\0';
					state = DATA;
      			}

				levelname.append(mData[end]);
      			
				end++;
      			start = end;
				break;

			case DATA:
				if (isalpha(mData[end]))
				{	
					add(new LevelCollection(mData + start, end - start, levelname, levelid));

					levelname.clear();
					levelname.append(mData[end]);
					
					levelid++;
					state = NAME;
						
					end++;
				}else
				{
					end++;
				}
				break;
		}
	}

	if (state == DATA)
	{
		add(new LevelCollection(mData + start, end - start, levelname, levelid));
	}
}

InternalCollections::~InternalCollections()
{
	if (mData)
	{
		for (int i = 0; i < mCollections.size(); i++)
			delete mCollections[i];

		delete mData;
	}
}

void InternalCollections::loadLevel(int collection, int level, Map* map)
{
	if ((collection < mCollections.size()) && (level < mCollections[collection]->levelCount()))
	mCollections[collection]->loadLevel(level, map);
}

void InternalCollections::add(LevelCollection* cl)
{
	unsigned int s = mCollections.size();

	mCollections.insert(s, cl);
}
