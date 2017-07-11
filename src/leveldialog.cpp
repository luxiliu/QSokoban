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

#include <QSettings>

#include "leveldialog.h"

LevelDialog::LevelDialog(QWidget* parent, Qt::WindowFlags f) : QDialog(parent, f)
{
	setWindowTitle(tr("Levels"));

	mLayout = new QGridLayout(this);

	mLabelCollection = new QLabel(tr("Collection:"), this);
	mLabelLevel = new QLabel(tr("Level:"), this);
	mComboCollection = new QComboBox(this);
	mComboLevel = new QComboBox(this);

	mLayout->addWidget(mLabelCollection, 0, 0);
	mLayout->addWidget(mComboCollection, 0, 1);
	mLayout->addWidget(mLabelLevel, 1, 0);
	mLayout->addWidget(mComboLevel, 1, 1);
	
	QSettings cfg("Others", "Sokoban");
	cfg.beginGroup("Game");
	mCollection = cfg.value("Collection").toInt();
	mLevel = cfg.value("Level").toInt();
}

LevelDialog::~LevelDialog()
{}

void LevelDialog::setInternalCollections(InternalCollections* ic)
{
	mIC = ic;

	mComboCollection->clear();

	for (int i = 0; i < mIC->collectionCount(); i++)
	{
		mComboCollection->addItem(mIC->collectionName(i));
	}
	mComboCollection->setCurrentIndex(mCollection);
	
	for (int i = 0; i < mIC->levelCount(mCollection); i++)
	{	
		QString _str;
		_str.sprintf("%d", i + 1);
		mComboLevel->addItem(_str);
	}
	mComboLevel->setCurrentIndex(mLevel);
}

void LevelDialog::accept()
{
	QDialog::accept();

	mCollection = mComboCollection->currentIndex();
	mLevel = mComboLevel->currentIndex();

	QSettings cfg("Others", "Sokoban");
	cfg.beginGroup("Game");
	cfg.setValue("Collection", mCollection);
	cfg.setValue("Level", mLevel);
}
