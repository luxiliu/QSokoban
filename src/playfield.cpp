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

#include <QPaintEvent>
#include <QPainter>
#include <QSoftMenuBar>
#include <QMessageBox>
#include <QSettings>

#include "playfield.h"
#include "leveldialog.h"

PlayField::PlayField(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f), mMap(NULL), mImageData(NULL), mCollection(0), mLevel(0)
{	
	// Set properties
	setAutoFillBackground(true);
	setFocusPolicy(Qt::StrongFocus);

	// Set background image
	QPalette palette;
	QPixmap pixmap = QPixmap(":image/starfield");
	palette.setBrush(backgroundRole(), pixmap);
	setPalette(palette);

	// Load internal level data and draw the first one
	mInternalCollections = new InternalCollections();
	
	if (mInternalCollections->collectionCount() && mInternalCollections->levelCount(mCollection))
	{
		QSettings cfg("Others", "Sokoban");
		cfg.beginGroup("Game");
		mCollection = cfg.value("Collection").toInt();
		mLevel = cfg.value("Level").toInt();

		mMap = new Map();
		mInternalCollections->loadLevel(mCollection, mLevel, mMap);
	
		mImageData = new ImageData();
	
		mMenu = QSoftMenuBar::menuFor(this);
		mMenu->addAction(tr("Restart"), this, SLOT(slotRestart()));
		mMenu->addAction(tr("Levels..."), this, SLOT(slotLevels()));
	}
}

PlayField::~PlayField()
{
	delete mInternalCollections;

	if (mMap != NULL) delete mMap;
	if (mImageData != NULL) delete mImageData;
}

QString PlayField::collectionName()
{
	return mInternalCollections->collectionName(mCollection);
}

int PlayField::level()
{
	return mLevel;
}
	
void PlayField::paintEvent(QPaintEvent* e)
{
	QWidget::paintEvent(e);

	if (mMap != NULL)
	{
		QPainter painter(this);
		mImageData->draw(mMap, painter, e->rect());
	}
}

void PlayField::keyPressEvent(QKeyEvent* e)
{
	QWidget::keyPressEvent(e);

	if (mMap == NULL)
		return;

	switch(e->key())
	{
		case Qt::Key_Up:
			mMap->move(mMap->manX(), mMap->manY() - 1);
			repaint();
			break;

		case Qt::Key_Down:
			mMap->move(mMap->manX(), mMap->manY() + 1);
			repaint();
			break;

		case Qt::Key_Left:
			if (mMap->move(mMap->manX() - 1, mMap->manY()))
				repaint();
			break;

		case Qt::Key_Right:
			if (mMap->move(mMap->manX() + 1, mMap->manY()))
				repaint();
			break;

		default:
			return;
	}

	if (mMap->isCompleted())
	{
		QTimer::singleShot(0, this, SLOT(slotTimeout()));
	}
}

void PlayField::slotRestart()
{
	mMap->clear();
	mInternalCollections->loadLevel(mCollection, mLevel, mMap);
}

void PlayField::slotNext()
{
	if (mLevel == (mInternalCollections->levelCount(mCollection) - 1))
		mLevel = 0;
	else
		mLevel++;

	mMap->clear();
	mInternalCollections->loadLevel(mCollection, mLevel, mMap);

	QSettings cfg("Others", "Sokoban");
	cfg.beginGroup("Game");
	cfg.setValue("Collection", mCollection);
	cfg.setValue("Level", mLevel);

	emit(signalLevel(mInternalCollections->collectionName(mCollection), mLevel));
}

void PlayField::slotTimeout()
{
	QMessageBox::information(this, tr("Sokoban"), tr("Level completed"));
	slotNext();
}

void PlayField::slotLevels()
{
	LevelDialog* mLvlDialog = new LevelDialog(this);
	mLvlDialog->setInternalCollections(mInternalCollections);

	if (QDialog::Accepted == mLvlDialog->exec())
	{
		QSettings cfg("Others", "Sokoban");
		cfg.beginGroup("Game");

		int _collection, _level;
		_collection = cfg.value("Collection").toInt();
		_level = cfg.value("Level").toInt();

		if (!((_collection == mCollection) && (_level == mLevel)))
		{
			mCollection = _collection;
			mLevel = _level;
			mMap->clear();
			mInternalCollections->loadLevel(mCollection, mLevel, mMap);
			emit(signalLevel(mInternalCollections->collectionName(mCollection), mLevel));
		}
	}

	delete mLvlDialog;

}
