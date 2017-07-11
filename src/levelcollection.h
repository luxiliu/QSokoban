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

#ifndef _LEVELCOLLECTION_H_
#define _LEVELCOLLECTION_H_

#include <QString>
#include <QByteArray>
#include <QVector>

#include "map.h"

class LevelCollection
{
public:
	LevelCollection(const char* start, int length, const QString& name, int id);

	int levelCount() { return mLevelNum; }
	void loadLevel(int level, Map* map);
	QString name() { return mName; }

private:
	void addData(const char* start, int length);
	void addSeparator();
	void addLevel(const char* index);
	void indexTextCollection();

private:
	QString mName;
	int mId;
	QByteArray mData;
	QVector<const char*> mIndexVector;
	int mLevelNum;

};

#endif /* _LEVELCOLLECTION_H_ */
