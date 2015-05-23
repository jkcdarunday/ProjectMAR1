#include "registers.h"

Registers::Registers()
{
    h = new QVector<int>();
    for(int i=0;i<10;i++)
        h->insert(i,0);
}

void Registers::setRegister(int r, int v)
{
    h->insert(r, v);
    //QModelIndex *index = createIndex(r,1);
    emit dataChanged(createIndex(r,1),createIndex(r,1));
}

int Registers::readRegister(int r)
{
    return h->at(r);
}

int Registers::rowCount(const QModelIndex &parent) const
{
    return h->size();
}

int Registers::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant Registers::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole && index.column()<2 && index.row()<h->size()){
        if(index.column()==0)
            return Mapper::registers().at(index.row());
        else
            return QString("%1").arg(h->at(index.row()),8,2,QChar('0'));
    } else if(role == Qt::TextAlignmentRole){
        return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant Registers::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Register");
            case 1:
                return QString("Value");
            }
        }
    }
    return QVariant();
}
