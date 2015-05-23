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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QThread>
#include <QFontMetrics>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p = new AssemblyParser();
    r = new Registers();
    m = new Memory();
    clock = new QTimer();
    connect(clock, SIGNAL(timeout()), this, SLOT(nextState()));
    connect(this, SIGNAL(endState()), clock, SLOT(stop()));

    ui->registerTable->setModel(r);
    ui->memoryTable->setModel(m);

    QGraphicsScene *scene = new QGraphicsScene();
    int w = 150;
    scene->addRect(0,0,w,100);
    scene->addRect(w+20,0,w,100);
    scene->addRect(2*w+40,0,w,100);
    QGraphicsTextItem *t;
    t = scene->addText("Fetch");
    t->setPos(0 + (w/2) - 20, 0);
    ppFetch = scene->addText("");
    ppFetch->setPos(0 + 20, 40);

    t = scene->addText("Decode");
    t->setPos(w+20 + (w/2) - 28, 0);
    ppDecode = scene->addText("");
    ppDecode->setPos(w + 40, 40);

    t = scene->addText("Execute");
    t->setPos(2*w+40 + (w/2) - 28    , 0);
    ppExecute = scene->addText("");
    ppExecute->setPos(2*w +60, 40);

    ui->pipeline->setScene(scene);


    highlighter = new SyntaxHighlighter(ui->assemblyCode->document());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete highlighter;
}

void MainWindow::setItemToState(int row, int column, char state)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(QString(state));
    QFontMetrics fm(ppFetch->font());
    switch(state){
    case 'F':
        ppFetch->document()->setPlainText(p->queue->at(row)->code);
        ppFetch->setPos(75-fm.width(p->queue->at(row)->code)/2,40);
        item->setBackground(QBrush(QColor::fromRgb(255,200,200)));
        break;
    case 'D':
        item->setBackground(QBrush(QColor::fromRgb(200,255,200)));
        ppDecode->setPos(170+75-fm.width(p->queue->at(row)->code)/2,40);
        ppDecode->document()->setPlainText(p->queue->at(row)->code);
        break;
    case 'E':
        item->setBackground(QBrush(QColor::fromRgb(200,200,255)));
        ppExecute->setPos(340+75-fm.width(p->queue->at(row)->code)/2,40);
        ppExecute->document()->setPlainText(p->queue->at(row)->code);
        break;
    case 'S':
        item->setBackground(QBrush(QColor::fromRgb(255,255,200)));
        break;
    default:
        item->setText("");
    }
    ui->cycle->setItem(row, column, item);
}

void MainWindow::nextState()
{
    if(!p->queue->empty() && p->checkState(p->queue->size()-1)!=4){
        ui->cycle->setColumnCount(ui->cycle->columnCount()+1);
        for(int i=p->queue->size()-1;i>=0;i--)
            setItemToState(i, ui->cycle->columnCount()-1, p->nextState(i));
    } else {
        ui->executeButton->setEnabled(true);
        ui->assemblyCode->setEnabled(true);
        ui->nextStateButton->setEnabled(false);
        emit endState();
    }
}

void MainWindow::on_executeButton_clicked()
{
    int lineError=0;
    if((lineError=p->parse(ui->assemblyCode->document()->toPlainText()))==0){
        ui->cycle->setRowCount(p->queue->size());
        for(int i=0;i<p->queue->size();i++)
            ui->cycle->setVerticalHeaderItem(i, new QTableWidgetItem(p->queue->at(i)->code));
        ui->cycle->setColumnCount(0);
        ui->executeButton->setEnabled(false);
        ui->assemblyCode->setEnabled(false);
        ui->nextStateButton->setEnabled(true);
    } else {
        QMessageBox::critical(this, "Execution Failed", QString("An error has been found while executing code at line ") + QString::number(lineError) + ".");
    }
    //this->clock->start(500);
}

void MainWindow::on_nextStateButton_clicked()
{
    nextState();
}

void MainWindow::on_actionOpen_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    ".",
                                                    tr("Assembly File (*.asm)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    ui->assemblyCode->clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->assemblyCode->append(line);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    ".",
                                                    tr("Assembly File (*.asm)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->assemblyCode->document()->toPlainText();
}
