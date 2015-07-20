#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  this->setWindowOpacity(0.96);
  this->setWindowTitle("Holy Bible V1.0");

  Search *SearchWidget = new Search();
  this->setCentralWidget(SearchWidget);

}

MainWindow::~MainWindow()
{
  deleteLater();
}
