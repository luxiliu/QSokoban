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

#ifndef _INTERNALCOLLECTIONS_H
#define _INTERNALCOLLECTIONS_H

#include <QString>
#include <QVector>

#include "levelcollection.h"

class InternalCollections
{
public:
	InternalCollections();
	~InternalCollections();

	int collectionCount() { return mCollections.size(); }
	int levelCount(int collection) { return mCollections[collection]->levelCount(); }
	void loadLevel(int collection, int level, Map* map);
	QString collectionName(int collection) { return mCollections[collection]->name(); }

private:
	void add(LevelCollection* cl);

private:
	char* mData;
	QVector<LevelCollection*> mCollections;
};

#endif /* _INTERNALCOLLECTIONS_H */
