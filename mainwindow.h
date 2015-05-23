#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFileDialog>
#include "assemblyparser.h"
#include "registers.h"
#include "syntaxhighlighter.h"
#include "memory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setItemToState(int row, int column, char state);
public slots:
    void nextState();

signals:
    void endState();

private slots:
    void on_executeButton_clicked();

    void on_nextStateButton_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    AssemblyParser *p;
    SyntaxHighlighter *highlighter;
    Registers *r;
    Memory *m;
    QTimer *clock;

    QGraphicsTextItem *ppFetch;
    QGraphicsTextItem *ppDecode;
    QGraphicsTextItem *ppExecute;
};

#endif // MAINWINDOW_H
