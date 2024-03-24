#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new QFileSystemModel(this);
    model->setFilter(QDir::Dirs);
    model->setRootPath("");
    ui->listView->setModel(model);
    this->setWindowTitle("Выберите раздел для форматирования");
}


MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QListView* listView=(QListView*)sender();
    QFileInfo fileInfo=model->fileInfo(index);
    ui->lineEdit->setText(fileInfo.absoluteFilePath());
    if(fileInfo.fileName()==".."){
        QDir dir=fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if(fileInfo.fileName()=="."){
        listView->setRootIndex(model->index(""));
    }
    else if(fileInfo.isDir()){
        listView->setRootIndex(index);
    }
}

