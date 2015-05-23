#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include "mapper.h"

class SyntaxHighlighter : public QSyntaxHighlighter
{
public:
    SyntaxHighlighter(QTextDocument *document);

    // QSyntaxHighlighter interface
protected:
    void highlightBlock(const QString &text);
    QTextCharFormat instructionFormat;
    QTextCharFormat registerFormat;
    QTextCharFormat constFormat;
    QString insPattern;
    QString regPattern;
};

#endif // SYNTAXHIGHLIGHTER_H
