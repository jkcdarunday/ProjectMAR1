#ifndef ASSEMBLYPARSER_H
#define ASSEMBLYPARSER_H

#include <QStack>
#include <QString>
#include <QRegExp>
#include <QDebug>
#include "mapper.h"

class AssemblyParser
{
public:
    class Instruction{
    public:
        QString code;
        int instruction;
        int parameter[2];
        int value;
        int fetch;
        int decode;
        int execute;
        int lastDependent;
        Instruction(QString ins, QString p1, QString p2){
            this->code = (ins.trimmed() + " " + p1.trimmed() + " " + p2.trimmed()).toUpper();

            fetch = 1;
            decode = 3;
            execute = 2;

            lastDependent = -1;

            this->instruction = Mapper::instructions().indexOf(ins.trimmed());
            this->parameter[0] = Mapper::registers().indexOf(p1.trimmed());
            if(parameter[0]<0)
                value = p1.toInt();
            this->parameter[1] = Mapper::registers().indexOf(p2.trimmed());
            if(parameter[1]<0)
                value = p2.toInt();
        }

        void setDependency(int i){
            this->lastDependent=i;
        }

        bool checkConflict(Instruction *ins){

            for(int i=0;i<2;i++)
                for(int j=0;j<2;j++){
                    // read after write
                    if(this->parameter[i] == ins->parameter[j]
                            && Mapper::readsFrom(this->instruction,i) && Mapper::writesTo(this->instruction,j)
                            ) return true;
                    // write after read
                    if(this->parameter[i] == ins->parameter[j]
                            && Mapper::readsFrom(this->instruction,j) && Mapper::writesTo(this->instruction,i)
                            ) return true;

                    // write after write
                    if(this->parameter[i] == ins->parameter[j]
                            && Mapper::writesTo(this->instruction,j) && Mapper::writesTo(this->instruction,i)
                            ) return true;
                }
            return false;
        }

        void printInfo(){
            qDebug() << QString("Instruction:") << instruction << QString("Parameter 1:") << parameter[0] << QString("Parameter 2:") << parameter[1] << QString("Value:") << value;
        }

    };
    AssemblyParser();
    int checkState(int i);
    char nextState(int i);
    void advanceState(int i, int s);
    char stateToFDE(int s);
    int parse(QString str);
    QStack<Instruction*> *queue;
private:
    QRegExp *parser;
    QRegExp *blankParser;
    QStringList *instructions;
    QStringList *registers;
};

#endif // ASSEMBLYPARSER_H
