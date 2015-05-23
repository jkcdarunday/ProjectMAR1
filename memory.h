#ifndef MEMORY_H
#define MEMORY_H

#include <QAbstractTableModel>
#include <QHash>

class Memory : public QAbstractTableModel
{
public:
    Memory();
    void set(int r, int v);
    int read(int r);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QHash<int,int> *h;
};

#endif // MEMORY_H
