#include "memory.h"

Memory::Memory()
{
    h = new QHash<int,int>();
}

void Memory::set(int a, int v)
{
    h->insert(a, v);
    //QModelIndex *index = createIndex(r,1);
    emit dataChanged(createIndex(a,1),createIndex(a,1));
}

int Memory::read(int r)
{
    return h->value(r);
}

int Memory::rowCount(const QModelIndex &parent) const
{
    return h->size();
}

int Memory::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant Memory::data(const QModelIndex &index, int role) const
{
    QList<int> k = h->keys();
    if(role == Qt::DisplayRole && index.column()<2 && index.row()<h->size()){
        if(index.column()==0)
            return k[index.row()];
        else
            return QString("%1").arg(h->value(k[index.row()]),8,2,QChar('0'));
    } else if(role == Qt::TextAlignmentRole){
        return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant Memory::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Address");
            case 1:
                return QString("Value");
            }
        }
    }
    return QVariant();
}

