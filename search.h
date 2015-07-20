#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QString>
#include <QToolBox>



class Search : public QWidget
{
    Q_OBJECT

public:
    Search(QWidget *parent = 0);
    ~Search();

private:
    //QWidget      *subWindow;
    QHBoxLayout  *mainLayout;
    QVBoxLayout  *leftLayout;
    QHBoxLayout  *leftBibleLayout;
    QVBoxLayout  *leftTestamentLayout;
    QVBoxLayout  *rightLayout;
    QHBoxLayout  *leftBottomLayout;

    QToolBox     *leftToolBox;

    QComboBox    *chooseBible;
    QLabel       *bibleVersion;

    QRadioButton *oldTestament;
    QComboBox    *oldTestamentBox;

    QRadioButton *newTestament;
    QComboBox    *newTestamentBox;
    QLineEdit    *chapterEdit;

    QPushButton  *search;
    QLabel       *chapiterLabel;
    QListWidget  *display;


    int          rowNum = 0;
    int          oldOrNew = 0;
    int          dexNum = 0;
    QFile        *bFile;
    QString      cutNumber;
    QString      fileName;
    QString      dex;

    void openFile();
    void Read(QString Filename);
    void getRowNumber(QString NameNeeded);
    void getChapterIndex();

private slots:
    void on_radiobutton_changed();
    //void on_combobox_changed(QString index);
    void on_searchbutton_clicked();
};

#endif // WIDGET_H
