#include "search.h"
#include <QDebug>

Search::Search(QWidget *parent) : QWidget(parent)
{
  QSize *mysize = new QSize(400,200);
  /*subWindow = new QWidget();
  subWindow->setParent(parent);

  //subWindow->setBaseSize(100,500);
  //subWindow->setBaseSize(mysize);    //err.

  subWindow->show();*/

  mainLayout          = new QHBoxLayout(this);
  leftLayout          = new QVBoxLayout();
  leftBibleLayout     = new QHBoxLayout();
  leftTestamentLayout = new QVBoxLayout();
  rightLayout         = new QVBoxLayout();
  leftBottomLayout    = new QHBoxLayout();

  //bible version
  bibleVersion        = new QLabel("Bible Version:");

  chooseBible         = new QComboBox();
  chooseBible->blockSignals(true);         //signal blocked
  //connect(chooseBible,SIGNAL(activated(QString)),SLOT(on_combobox_changed(QString)));
  chooseBible->addItem("American Standard Version",0);
  chooseBible->addItem("Basic English",1);
  chooseBible->addItem("Darby",2);
  chooseBible->addItem("King James Version",3);
  chooseBible->addItem("World English Bible",4);
  chooseBible->addItem("Young's Literal Translation",5);
  chooseBible->blockSignals(false);         //signal enabled

  //old testament
  oldTestament        = new QRadioButton("Old Testament");
  connect(oldTestament,SIGNAL(clicked()),this,SLOT(on_radiobutton_changed()));

  oldTestamentBox     = new QComboBox();
  oldTestamentBox->blockSignals(true);         //signal blocked
  oldTestamentBox->setEnabled(false);
  //connect(oldTestamentBox,SIGNAL(activated(QString)),SLOT(on_combobox_changed(QString)));
  oldTestamentBox->addItem("Genesis",0);
  oldTestamentBox->addItem("Exodus",1);
  oldTestamentBox->addItem("Leviticus",2);
  oldTestamentBox->addItem("Numbers",3);
  oldTestamentBox->addItem("Deuteronomy",4);
  oldTestamentBox->addItem("The Book of Joshua",5);
  oldTestamentBox->addItem("The Book of Judges",6);
  oldTestamentBox->addItem("The Book of Ruth",7);
  oldTestamentBox->addItem("The First Book of Samuel",8);
  oldTestamentBox->addItem("The Second Book of Samuel",9);
  oldTestamentBox->addItem("The First Book of Kings",10);
  oldTestamentBox->addItem("THe Second Book of Kings",11);
  oldTestamentBox->addItem("The First Book of Chronicles",12);
  oldTestamentBox->addItem("The Second Book of Chronicles",13);
  oldTestamentBox->addItem("The Book of Ezra",14);
  oldTestamentBox->addItem("The Book of Nehemiah",15);
  oldTestamentBox->addItem("The Book of Esther",16);
  oldTestamentBox->addItem("The Book of Job",17);
  oldTestamentBox->addItem("The Psalms",18);
  oldTestamentBox->addItem("The Proverbs",19);
  oldTestamentBox->addItem("Ecclesiastes",20);
  oldTestamentBox->addItem("The Song of Songs",21);
  oldTestamentBox->addItem("The Book of Isaiah",22);
  oldTestamentBox->addItem("The Book of Jeremiah",23);
  oldTestamentBox->addItem("The Lamentations of Jeremiah",24);
  oldTestamentBox->addItem("The Book of Ezekiel",25);
  oldTestamentBox->addItem("The Book of Daniel",26);
  oldTestamentBox->addItem("The Book of Hosea",27);
  oldTestamentBox->addItem("The Book of Joel",28);
  oldTestamentBox->addItem("The Book of Amos",29);
  oldTestamentBox->addItem("The Book of Obadiah",30);
  oldTestamentBox->addItem("The Book of Jonah",31);
  oldTestamentBox->addItem("The Book of Micah",32);
  oldTestamentBox->addItem("The Book of Nahum",33);
  oldTestamentBox->addItem("The Book of Habakkuk",34);
  oldTestamentBox->addItem("The Book of Zephaniah",35);
  oldTestamentBox->addItem("The Book of Haggai",36);
  oldTestamentBox->addItem("The Book of Zechariah",37);
  oldTestamentBox->addItem("The Book of Malachi",38);
  oldTestamentBox->blockSignals(false);         //signal enabled

  //new testament
  newTestament        = new QRadioButton("New Testament");
  connect(newTestament,SIGNAL(clicked()),this,SLOT(on_radiobutton_changed()));
  newTestamentBox     = new QComboBox();
  newTestamentBox->blockSignals(true);         //signal blocked
  newTestamentBox->setEnabled(false);
  //connect(newTestamentBox,SIGNAL(currentIndexChanged(QString)),SLOT(on_combobox_changed(QString)));
  newTestamentBox->addItem("The Gospel according to Matthew",0);
  newTestamentBox->addItem("The Gospel according to Mark",1);
  newTestamentBox->addItem("The Gospel according to Luke",2);
  newTestamentBox->addItem("The Gospel according to John",3);
  newTestamentBox->addItem("The Acts of the Apostles",4);
  newTestamentBox->addItem("The Letter of Paul to the Romans",5);
  newTestamentBox->addItem("The First Letter of Paul to the Corinthians",6);
  newTestamentBox->addItem("The Second Letter of Paul to the Corinthians",7);
  newTestamentBox->addItem("The Letter of Paul to the Galatians",8);
  newTestamentBox->addItem("The Letter of Paul to the Ephesians",9);
  newTestamentBox->addItem("The Letter of Paul to the Philippians",10);
  newTestamentBox->addItem("The Letter of Paul to the Colossians",11);
  newTestamentBox->addItem("The First Letter of Paul to the Thessalonians",12);
  newTestamentBox->addItem("The Second Letter of Paul to the Thessalonians",13);
  newTestamentBox->addItem("The First Letter of Paul to the Timothy",14);
  newTestamentBox->addItem("The Second Letter of Paul to the Timothy",15);
  newTestamentBox->addItem("The Letter of Paul to the Titus",16);
  newTestamentBox->addItem("The Letter of Paul to the Philemon",17);
  newTestamentBox->addItem("The Letter of Paul to the Hebrews",18);
  newTestamentBox->addItem("The Letter of James",19);
  newTestamentBox->addItem("The First Letter of Peter",20);
  newTestamentBox->addItem("The Second Letter of Peter",21);
  newTestamentBox->addItem("The First Letter of John",22);
  newTestamentBox->addItem("The Second Letter of John",23);
  newTestamentBox->addItem("The Third Letter of John",24);
  newTestamentBox->addItem("The Letter of Jude",25);
  newTestamentBox->addItem("The Revelation to John",26);
  newTestamentBox->blockSignals(false);         //signal enabled

  search              = new QPushButton("Search");
  connect(search,SIGNAL(clicked()),this,SLOT(on_searchbutton_clicked()));
  search->setEnabled(false);

  display             = new QListWidget();
  display->setStyleSheet("color: #543524;background-color: #fed283;");//           qss!
  display->setWordWrap(true);

  chapiterLabel       = new QLabel("Chapter: ");
  chapterEdit         = new QLineEdit();
  chapterEdit->setEnabled(false);

  //right Layout
  rightLayout->addWidget(display);

  //left1
  leftBibleLayout->addWidget(bibleVersion);
  leftBibleLayout->addWidget(chooseBible);
  //left2
  leftTestamentLayout->addWidget(oldTestament);
  leftTestamentLayout->addWidget(oldTestamentBox);
  leftTestamentLayout->addWidget(newTestament);
  leftTestamentLayout->addWidget(newTestamentBox);
  //left3
  leftBottomLayout->addWidget(chapiterLabel);
  leftBottomLayout->addWidget(chapterEdit);
  leftBottomLayout->addWidget(search);
  //left Layout
  leftLayout->addLayout(leftBibleLayout);
  leftLayout->addLayout(leftTestamentLayout);
  leftLayout->addLayout(leftBottomLayout);

  //main Layout
  mainLayout->addLayout(leftLayout);
  mainLayout->addLayout(rightLayout);

}

Search::~Search()
{
    deleteLater();
}

void Search::openFile()
{
    switch (chooseBible->currentIndex())
    {
      // to choose which bible will be opened
      case 0:
          fileName = ":/bibles/asv.txt";
          break;
      case 1:
          fileName = ":/bibles/basicenglish.txt";
          break;
      case 2:
          fileName = ":/bibles/darby.txt";
          break;
      case 3:
          fileName = ":/bibles/kjv.txt";
          break;
      case 4:
          fileName = ":/bibles/web.txt";
          break;
      case 5:
          fileName = ":/bibles/ylt.txt";
          break;
      default:
          qDebug()<<"err01:choose file";
          break;
    }

    Read(fileName);
}

void Search::Read(QString Filename)
{
    QFile bFile(Filename);

    if(!bFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"error open file"<<Filename;
        return;
    }

    QTextStream in(&bFile);
    QString mText;
    QString temp2;
    QString temp3;

    QString dexNumStr = QString::number(dexNum);
    int     dexNumLen = dexNumStr.length();

    getRowNumber(bFile.fileName());//int rowNum = 0; 开头声明全局变量

    if(dexNumLen == 1)
    {
        for(int i = 0; i <= rowNum; i ++)
        {
            mText = in.readLine();

            if(mText.mid(0,dex.length()) == dex)
            {
                if(QString(mText[dex.length()+2]) != QString("\t"))
                {
                    break;
                }

                if(QString(mText[dex.length()+1]) == dexNumStr)
                {
                    mText.remove(0,dex.length()+3);
                    display->addItem(mText);
                }

            }
        }

    }else if(dexNumLen == 2)
    {
        for(int i = 0; i <= rowNum; i ++)
        {
            mText = in.readLine();

            if(mText.mid(0,dex.length()) == dex)
            {
                temp2 = QString(mText[dex.length()+1])+QString(mText[dex.length()+2]);

                if(temp2 == dexNumStr)
                {
                    if(QString(mText[dex.length()+3]) != QString("\t"))
                    {
                        break;
                    }
                    mText.remove(0,dex.length()+4);
                    display->addItem(mText);
                }
            }
        }

    }else if(dexNumLen == 3)
    {
        for(int i = 0; i <= rowNum; i ++)
        {
            mText = in.readLine();

            if(mText.mid(0,dex.length()) == dex)
            {
                temp3 = QString(mText[dex.length()+1])+QString(mText[dex.length()+2]+QString(mText[dex.length()+3]));

                if(temp3 == dexNumStr)
                {
                    if(QString(mText[dex.length()+4]) != QString("\t"))
                    {
                        break;
                    }
                    mText.remove(0,dex.length()+5);
                    display->addItem(mText);
                }

            }
        }
    }

    mText = in.readLine();
    qDebug()<<mText.mid(0,7)+" "+QString::number(rowNum);
    bFile.flush();
    bFile.close();
}

void Search::getRowNumber(QString NameNeeded)
{
    QFile rowFile(NameNeeded);

    if(!rowFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"error";
        return;
    }

    QTextStream in(&rowFile);

    //get rowNum
    while (!in.atEnd())
    {
        in.readLine();   //any problem, add "QString line = "in the front of this line.
        rowNum ++;
    }
}

void Search::getChapterIndex()
{
    if(oldOrNew == 0)
    {
      switch(oldTestamentBox->currentIndex())
      {
        case 0:
            dex = "Genesis";
        case 1:
            dex = "Exodus";
            break;
        case 2:
            dex = "Leviticus";
            break;
        case 3:
            dex = "Numbers";
            break;
        case 4:
            dex = "Deuteronomy";
            break;
        case 5:
            dex = "Joshua";
            break;
        case 6:
            dex = "Judges";
            break;
        case 7:
            dex = "Ruth";
            break;
        case 8:
            dex = "1 Samuel";
            break;
        case 9:
            dex = "2 Samuel";
            break;
        case 10:
            dex = "1 Kings";
            break;
        case 11:
            dex = "2 Kings";
            break;
        case 12:
            dex = "1 Chronicles";
            break;
        case 13:
            dex = "2 Chronicles";
            break;
        case 14:
            dex = "Ezra";
            break;
        case 15:
            dex = "Nehemiah";
            break;
        case 16:
            dex = "Esther";
            break;
        case 17:
            dex = "Job";
            break;
        case 18:
            dex = "Psalms";
            break;
        case 19:
            dex = "Proverbs";
            break;
        case 20:
            dex = "Ecclesiastes";
            break;
        case 21:
            dex = "Song of Solomon";
            break;
        case 22:
            dex = "Isaiah";
            break;
        case 23:
            dex = "Jeremiah";
            break;
        case 24:
            dex = "Lamentations";
            break;
        case 25:
            dex = "Ezekiel";
            break;
        case 26:
            dex = "Daniel";
            break;
        case 27:
            dex = "Hosea";
            break;
        case 28:
            dex = "Joel";
            break;
        case 29:
            dex = "Amos";
            break;
        case 30:
            dex = "Obadiah";
            break;
        case 31:
            dex = "Jonah";
            break;
        case 32:
            dex = "Micah";
            break;
        case 33:
            dex = "Nahum";
            break;
        case 34:
            dex = "Habakkuk";
            break;
        case 35:
            dex = "Zephaniah";
            break;
        case 36:
            dex = "Haggai";
            break;
        case 37:
            dex = "Zechariah";
            break;
        case 38:
            dex = "Malachi";
            break;
        default:
            qDebug()<<"errrrrrrrrrrorrrrrrrrrrrr";
            break;
      }
    }
    else if(oldOrNew == 1)
    {
      switch(newTestamentBox->currentIndex())
      {
        case 0:
            dex = "Matthew";
            break;
        case 1:
            dex = "Mark";
            break;
        case 2:
            dex = "Luke";
            break;
        case 3:
            dex = "John";
            break;
        case 4:
            dex = "Acts";
            break;
        case 5:
            dex = "Romans";
            break;
        case 6:
            dex = "1 Corinthians";
            break;
        case 7:
            dex = "2 Corinthians";
            break;
        case 8:
            dex = "Galatians";
            break;
        case 9:
            dex = "Ephesians";
            break;
        case 10:
            dex = "Philippians";
            break;
        case 11:
            dex = "Colossians";
            break;
        case 12:
            dex = "1 Thessalonians";
            break;
        case 13:
            dex = "2 Thessalonians";
            break;
        case 14:
            dex = "1 Timothy";
            break;
        case 15:
            dex = "2 Timothy";
            break;
        case 16:
            dex = "Titus";
            break;
        case 17:
            dex = "Philemon";
            break;
        case 18:
            dex = "Hebrews";
            break;
        case 19:
            dex = "James";
            break;
        case 20:
            dex = "1 Peter";
            break;
        case 21:
            dex = "2 Peter";
            break;
        case 22:
            dex = "1 John";
            break;
        case 23:
            dex = "2 John";
            break;
        case 24:
            dex = "3 John";
            break;
        case 25:
            dex = "Jude";
            break;
        case 26:
            dex = "Revelation";
            break;
        default:
            qDebug()<<"dafdfsfdgg";
            break;
      }
    }
}

void Search::on_radiobutton_changed()
{
    search->setEnabled(true);
    chapterEdit->setEnabled(true);
    if(sender() == oldTestament)
    {
        //in
        newTestamentBox->setEnabled(false);
        oldTestamentBox->setEnabled(true);
        oldOrNew = 0;
    }
    else
    {
        //in
        oldTestamentBox->setEnabled(false);
        newTestamentBox->setEnabled(true);
        oldOrNew = 1;
    }
}

void Search::on_searchbutton_clicked()
{
    display->clear();
    rowNum = 0;
    dexNum = chapterEdit->text().toInt();
    getChapterIndex();
    openFile();
}
