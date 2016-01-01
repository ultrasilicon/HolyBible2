#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  this->setWindowOpacity(0.97);
  this->setWindowTitle("Holy Bible V2.0");
  this->setMinimumHeight(500);
  this->setMinimumWidth(900);

  //this->setWindowFlags(Qt::FramelessWindowHint);
  //this->setAttribute(Qt::WA_TranslucentBackground);

  Search *SearchWidget = new Search();
  this->setCentralWidget(SearchWidget);

}

MainWindow::~MainWindow()
{
  deleteLater();
}
