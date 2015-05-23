#include "assemblyparser.h"

AssemblyParser::AssemblyParser()
{
    queue = new QStack<Instruction*>();
    parser = new QRegExp("^\\s*([a-z]+)\\s+(R[0-7]|MAR[01]|\\d+)(\\s+(R[0-7]|MAR[01]|\\d+))?\\s*$", Qt::CaseInsensitive);
    blankParser = new QRegExp("^\\s*$");
}


int AssemblyParser::checkState(int i)
{
    if(queue->at(i)->fetch > 0)
        return 1;
    if(queue->at(i)->decode > 0)
        return 2;
    if(queue->at(i)->execute > 0)
        return 3;
    return 4;
}

char AssemblyParser::nextState(int i)
{
    int currentState = checkState(i);
    // check if current instruction has already finished executing
    if(currentState == 4)
        return '-';

    // stall if there is a conflict with a currently-executing instruction
    int dependency  = queue->at(i)->lastDependent;
    if(dependency>=0 && checkState(dependency)!=4)
        return 'S';

    if(i>0){
        int parentState = checkState(i-1);

        // check if state of previous instruction is more advanced than the current state
        if(parentState > currentState){
            advanceState(i, currentState);
            return stateToFDE(currentState);
        } else {
            return 'S'; // we stall if we conflict with the parent state
        }
    }else{
        // advance state if first instruction hasn't finished terminating
        advanceState(i, currentState);
        return stateToFDE(currentState);
    }
}

void AssemblyParser::advanceState(int i, int s)
{
    switch(s){
    case 1:
        queue->at(i)->fetch--;
        break;
    case 2:
        queue->at(i)->decode--;
        break;
    case 3:
        queue->at(i)->execute--;
        break;
    }
}

char AssemblyParser::stateToFDE(int s)
{
    switch(s){
    case 1:
        return 'F';
    case 2:
        return 'D';
    case 3:
        return 'E';
    }
    return '-';
}



int AssemblyParser::parse(QString str)
{
    queue->clear();
    QStringList s = str.split('\n');
    for (int i = 0; i < s.size(); ++i)
        if(parser->indexIn(s.at(i)) >=0){
            int conflict = -1;
            Instruction *ins = new Instruction(parser->cap(1).toUpper(), parser->cap(2).toUpper(), parser->cap(4).toUpper());
            for(int n=queue->size()-1;n>=0;n--)
                if(ins->checkConflict(queue->at(n))){
                    conflict=n;
                    break;
                }

            ins->setDependency(conflict);

            queue->push(ins);
            queue->top()->printInfo();
        }else if(!(blankParser->indexIn(s.at(i)) >=0)){
            qDebug() << s.at(i);
            return i+1;
        }
    return 0;
}

