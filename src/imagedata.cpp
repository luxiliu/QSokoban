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

#include <QPixmap>
#include <QPainter>

#include "imagedata.h"
#include "time.h"

ImageData::ImageData()
{}

void ImageData::draw(Map* map, QPainter& painter, const QRect& rect)
{	
	int wsize = 0, hsize = 0, metasize = 0;
	int xOff, yOff;
	int sindex, lindex;

	if (!map)
		return;

	wsize = rect.width() / (map->width() * 2);
	hsize = rect.height() / (map->height() * 2);

	metasize = (wsize < hsize) ? wsize : hsize;

	xOff = (rect.width() - 2 * metasize * map->width()) / 2;
	yOff = (rect.height()  - 2 * metasize * map->height()) / 2;

	for (int i = 0; i < map->width(); i++)
	{
		for (int j = 0; j < map->height(); j++)
		{
			sindex = (i % 4 + j % 4) / 2 + 1;
			lindex = (i % 6 + j % 6) / 2 + 1;

			if (map->getBit(i, j) == 0)
				continue;

			if (map->getBit(i, j) == WALL)
			{
				QString stoneFile;
				stoneFile.sprintf(":image/stone_%d", lindex);

				QPixmap stonePix =  QPixmap(stoneFile);
				stonePix = stonePix.scaled(2 * metasize, metasize);
				painter.drawPixmap(xOff + metasize * 2 * i, yOff + metasize * 2 * j + metasize, stonePix);

				if (map->getBit(i - 1, j) != WALL)
				{
					stoneFile.clear();
					stoneFile.sprintf(":image/halfstone_%d", sindex);

					stonePix.load(stoneFile);
					stonePix = stonePix.scaled(metasize, metasize);
					painter.drawPixmap(xOff + metasize * 2 * i, yOff + metasize * 2 * j, stonePix);
				}else
				{
					stoneFile.clear();
					stoneFile.sprintf(":image/halfstone_%d", lindex);

					stonePix.load(stoneFile);
					stonePix = stonePix.scaled(2 * metasize, metasize);
					painter.drawPixmap(xOff + metasize * 2 * i - metasize, yOff + metasize * 2 * j, stonePix);
				}

				if (map->getBit(i + 1, j) != WALL)
				{
					stoneFile.clear();
					stoneFile.sprintf(":image/halfstone_%d", sindex);

					stonePix.load(stoneFile);
					stonePix = stonePix.scaled(metasize, metasize);
					painter.drawPixmap(xOff + metasize * 2 * i + metasize, yOff + metasize * 2 * j, stonePix);
				}

				continue;
			}

			if (map->getBit(i, j) & FLOOR)
			{
				QColor color = QColor(0x66, 0x66, 0x66);
				QBrush brush = QBrush(color);

				painter.fillRect(xOff + metasize * 2 * i, yOff + metasize * 2 * j, metasize * 2, metasize * 2, brush);
			}
			
			if ((i == map->manX()) && (j == map->manY()))
			{
				if (map->getBit(i, j) & GOAL)
				{
					QPixmap manPix = QPixmap(":image/saveman");
					manPix = manPix.scaled(2 * metasize, 2 * metasize);
					painter.drawPixmap(xOff + metasize * 2 * i, yOff + metasize * 2 * j, manPix);
				}else
				{
					QPixmap manPix = QPixmap(":image/man");
					manPix = manPix.scaled(2 * metasize, 2 * metasize);
					painter.drawPixmap(xOff + metasize * 2 * i, yOff + metasize * 2 * j, manPix);
				}
				continue;
			}

			if (map->getBit(i, j) & OBJECT)
			{
				if (map->getBit(i, j) & GOAL)
				{
					QPixmap treasurePix = QPixmap(":image/treasure");
					treasurePix = treasurePix.scaled(2 * metasize, 2 * metasize);
					painter.drawPixmap(xOff + metasize * 2 * i, yOff + metasize * 2 * j, treasurePix);
				}else
				{
					QPixmap objectPix = QPixmap(":image/object");
					objectPix = objectPix.scaled(2 * metasize, 2 * metasize);
					painter.drawPixmap(xOff + metasize * 2 * i, yOff + metasize * 2 * j, objectPix);
				}
				continue;
			}

			if (map->getBit(i, j) & GOAL)
			{
				QPixmap goalPix = QPixmap(":image/goal");
				goalPix = goalPix.scaled(2 * metasize, 2 * metasize);
				painter.drawPixmap(xOff + metasize * 2 * i, yOff + metasize * 2 * j, goalPix);
			}
		}
	}
}
