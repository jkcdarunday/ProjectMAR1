/***
 *
 * Project MAR1 - A Machine Visualizer
 * Copyright (C) 2015 Jan Keith Darunday, Kayla Mae Dizon, Marie Bawanan, and Lorelie Miranda

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.

 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***/
#ifndef REGISTERS_H
#define REGISTERS_H

#include <QAbstractTableModel>
#include <QVector>
#include "mapper.h"


/*!
    \class Registers

    \brief The Registers class provides
    a Table Model of the computer's registers.
*/
class Registers : public QAbstractTableModel
{
public:
    Registers();
    void setRegister(int r, int v);
    int readRegister(int r);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QVector<int> *h;
};

#endif // REGISTERS_H
