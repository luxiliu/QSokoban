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

#ifndef _PLAYFIELD_H_
#define _PLAYFIELD_H_

#include <QWidget>
#include <QMenu>
#include <QTimer>
#include <QPainter>
#include <QRect>

#include "internalcollections.h"
#include "map.h"
#include "imagedata.h"

class PlayField : public QWidget
{
	Q_OBJECT

public:
	PlayField(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~PlayField();

	QString collectionName();
	int level();

signals:
	void signalLevel(QString collection, int level);

protected:
	void paintEvent(QPaintEvent* e);
	void keyPressEvent(QKeyEvent* e);

private slots:
	void slotRestart();
	void slotNext();
	void slotTimeout();
	void slotLevels();

private:
	InternalCollections* mInternalCollections;
	Map* mMap;
	ImageData* mImageData;

	int mCollection;
	int mLevel;

	QMenu* mMenu;
	QTimer* mTimer;
};

#endif  /* _PLAYFIELD_H_ */
