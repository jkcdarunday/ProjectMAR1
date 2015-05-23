#ifndef REGISTERS_H
#define REGISTERS_H

#include <QAbstractTableModel>
#include <QVector>
#include "mapper.h"

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
