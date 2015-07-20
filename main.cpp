#include "mainwindow.h"
#include <QApplication>

int LoadMyStyle()
{
  QFile  qss(":/qss/coffee.qss");    //绿色中为qss资源文件的路径，根据需要更改
  if(!qss.open(QFile::ReadOnly))
  {
      qDebug("can not open qss !");
      return 0;
  }
  //w.setStyleSheet(qss.readAll());
  qApp->setStyleSheet(qss.readAll());
  return (0);
}


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  LoadMyStyle();

  MainWindow w;
  w.show();

  return a.exec();
}
