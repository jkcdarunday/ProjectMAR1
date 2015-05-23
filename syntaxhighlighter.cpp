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
#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *document) :
    QSyntaxHighlighter(document)
{
    instructionFormat.setFontWeight(QFont::Bold);
    instructionFormat.setForeground(Qt::darkYellow);

    registerFormat.setFontWeight(QFont::Bold);
    registerFormat.setForeground(Qt::darkMagenta);

    constFormat.setForeground(Qt::darkBlue);

    insPattern = "\\b(";
    for(int i=0;i<Mapper::instructions().size()-1;i++)
        insPattern += Mapper::instructions()[i] + "|";
    insPattern += Mapper::instructions().last();
    insPattern += ")\\b";

    regPattern = "\\b(";
    for(int i=0;i<Mapper::registers().size()-1;i++)
        regPattern += Mapper::registers()[i] + "|";
    regPattern += Mapper::registers().last();
    regPattern += ")\\b";



}

void SyntaxHighlighter::highlightBlock(const QString &text)
{

    QRegExp regExpression(regPattern,Qt::CaseInsensitive);
    QRegExp insExpression(insPattern,Qt::CaseInsensitive);
    QRegExp constExpression("\\b\\d+\\b");

    int index = text.indexOf(regExpression);
    while (index >= 0) {
        int length = regExpression.matchedLength();
        setFormat(index, length, registerFormat);
        index = text.indexOf(regExpression, index + length);
    }

    index = text.indexOf(insExpression);
    while (index >= 0) {
        int length = insExpression.matchedLength();
        setFormat(index, length, instructionFormat);
        index = text.indexOf(insExpression, index + length);
    }

    index = text.indexOf(constExpression);
    while (index >= 0) {
        int length = constExpression.matchedLength();
        setFormat(index, length, constFormat);
        index = text.indexOf(constExpression, index + length);
    }
}

