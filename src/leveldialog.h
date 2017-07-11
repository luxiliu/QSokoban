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

#ifndef _LEVEL_DIALOG_H_
#define _LEVEL_DIALOG_H_

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

#include "internalcollections.h"

class LevelDialog : public QDialog
{
	Q_OBJECT

public:
	LevelDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);
	~LevelDialog();

	void setInternalCollections(InternalCollections* ic);

public slots:
	virtual void accept();

private:
	InternalCollections* mIC;
	int mCollection;
	int mLevel;

	QGridLayout* mLayout;
	QLabel* mLabelCollection;
	QLabel* mLabelLevel;
	QComboBox* mComboCollection;
	QComboBox* mComboLevel;
};

#endif
