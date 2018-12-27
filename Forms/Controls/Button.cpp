/*
 * This file is part of PokéFinder
 * Copyright (C) 2017 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "Button.hpp"

Button::Button(QWidget *parent)
    : QPushButton(parent)
{
}

void Button::setImage(const QString &path)
{
    svg.load(path);
}

void Button::paintEvent(QPaintEvent *event)
{
    if (event->type() == QPaintEvent::Paint)
    {
        QImage image(svg.defaultSize() * 1.6, QImage::Format_ARGB32);
        image.fill(Qt::transparent);

        QPainter render(&image);
        svg.render(&render, image.rect());
        render.end();

        if (!isChecked())
        {
            image = toGrayScale(image);
        }

        QPainter paint(this);
        paint.drawImage(0, 0, image);
    }
}

QImage Button::toGrayScale(QImage image)
{
    int width = image.width();
    int height = image.height();

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            QRgb pixel = image.pixel(x, y);
            int gray = qGray(pixel);
            image.setPixel(x, y, qRgba(gray, gray, gray, qAlpha(pixel) >> 1));
        }
    }

    return image;
}
