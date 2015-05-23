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
