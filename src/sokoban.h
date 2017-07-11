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

#ifndef _SOKOBAN_H
#define _SOKOBAN_H

#include <QMainWindow>
#include <QSoftMenuBar>
#include <QMenu>

#include "playfield.h"

class Sokoban : public QMainWindow
{
    Q_OBJECT

public:
    Sokoban(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    ~Sokoban();

private slots:
	void slotLevel(QString collection, int level);

private:
	PlayField* mPlayField;
	QMenu* mMenu;

};

#endif /* _SOKOBAN_H */
