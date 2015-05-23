#ifndef MAPPER_H
#define MAPPER_H

#include <QStringList>

class Mapper
{
public:
    static QStringList registers(){
        return QStringList()
                << "MAR0"
                << "MAR1"
                << "R0"
                << "R1"
                << "R2"
                << "R3"
                << "R4"
                << "R5"
                << "R6"
                << "R7";
    }

    static QStringList instructions(){
        return QStringList()
                << "LOAD"
                << "STORE"
                << "SAVE"
                << "INC"
                << "DEC"
                << "ADD"
                << "SUB"
                << "MUL"
                << "DIV"
                << "CMP"
                << "AND"
                << "OR"
                << "NOT"
                << "XOR"
                << "JE"
                << "JG"
                << "JL"
                << "JMP";
    }

    static bool writesTo(int ins, int param){
        if(param==0){
            if(ins==1||ins==9)
                return false;
        }else if(param==1){
            return false;
        }
        return true;
    }

    static bool readsFrom(int ins, int param){
        if(param==0){
            if(ins==9)
                return true;
        }else{
            if(ins<=13 && ins != 0 && ins != 2)
                return true;
        }
        return false;
    }

    Mapper();
};

#endif // MAPPER_H
