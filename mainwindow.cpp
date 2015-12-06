#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimeEdit"
#include "QTableWidget"
#include "QPushButton"
#include "QLineEdit"
#include "QTextEdit"
#include "QTime"
#include "QTimer"
#include "QDebug"
#include "QMessageBox"
#define table ui->mainWidget
#define spItem ui->spItem
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mTimer = new QTimer();
    ui->txtNoteContext->setEnabled(true);
}
void MainWindow::AddNote()
{
    StickyCount++;
    QStringList strList;
    QTextEdit * textEdit = new QTextEdit();
    QTimeEdit * timeEdit = new QTimeEdit();
    QLineEdit * lineEdit = new QLineEdit();
    strList << "便利贴内容" << "提示时间" << "是否提示";
    timeEdit->setTime(ui->stickyTime->time());
    textEdit->setText(ui->txtNoteContext->toPlainText());
    lineEdit->setText("否");
    lineEdit->setEnabled(false);
    lineEdit->setAlignment(Qt::AlignCenter);
    table->setRowCount(StickyCount);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(strList);
    table->setCellWidget(StickyCount - 1,0,textEdit);
    table->setCellWidget(StickyCount - 1,1,timeEdit);
    table->setCellWidget(StickyCount - 1,2,lineEdit);
    spItem->setMaximum(StickyCount);
    if(!mTimer->isActive())
    {
        connect(mTimer,SIGNAL(timeout()),this,SLOT(ManageNote()));//链接到定时器
        mTimer->start(800);
    }
}
void MainWindow::ManageNote()
{
    for(int i=0;i<StickyCount;i++)
    {
        QTextEdit *textEdit = (QTextEdit *)table->cellWidget(i,0);
        QTimeEdit *timeEdit = (QTimeEdit *)table->cellWidget(i,1);
        QLineEdit *lineEdit = (QLineEdit *)table->cellWidget(i,2);
        if(QString::compare(lineEdit->text(),"否") == 0 && timeEdit->time().hour() == QTime::currentTime().hour() && timeEdit->time().minute() == QTime::currentTime().minute())
        {
            qDebug() << "便利贴提示时间到！这是第："<< QString::number(i) <<"条便利贴";
            QMessageBox::information(this,"Sticky Quick",textEdit->toPlainText());
            lineEdit->setText("是");
        }
    }
}
void MainWindow::DeleteNote()
{
    if(StickyCount == 0)return;
    int rows = spItem->value() - 1;
    mTimer->stop();
    table->removeCellWidget(rows,0);
    table->removeCellWidget(rows,1);
    table->removeCellWidget(rows,2);
    table->removeRow(rows);
    spItem->setMaximum(StickyCount);
    StickyCount--;
    mTimer->start();
}
MainWindow::~MainWindow()
{
    delete ui;
}
