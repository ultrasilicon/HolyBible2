#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//text
#include <QString>
#include <QTextStream>
#include <QRegExp>

//file
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QIcon>

//layout
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

//widget
#include <QComboBox>
#include <QCheckbox>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QGroupBox>
#include <QListWidget>
#include <QLineEdit>
#include <QTabWidget>
#include <QSlider>



class Search : public QWidget
{
    Q_OBJECT

public:
    Search(QWidget *parent = 0);
    ~Search();

protected:

    //QWidget      *subWindow;
    QHBoxLayout  *center_widget_layout;
    QVBoxLayout  *display_visual_layout;
    QVBoxLayout  *display_block_layout;

    const QString      bible_version_qstr[6] =
    {
      "American Standard Version",
      "Basic English",
      "Darby",
      "King James Version",
      "World English Bible",
      "Young's Literal Translation"
    };
    const QString      old_testament_qstr[39] =
    {
      "Genesis",
      "Exodus",
      "Leviticus",
      "Numbers",
      "Deuteronomy",
      "The Book of Joshua",
      "The Book of Judges",
      "The Book of Ruth",
      "The First Book of Samuel",
      "The Second Book of Samuel",
      "The First Book of Kings",
      "THe Second Book of Kings",
      "The First Book of Chronicles",
      "The Second Book of Chronicles",
      "The Book of Ezra",
      "The Book of Nehemiah",
      "The Book of Esther",
      "The Book of Job",
      "The Psalms",
      "The Proverbs",
      "Ecclesiastes",
      "The Song of Songs",
      "The Book of Isaiah",
      "The Book of Jeremiah",
      "The Lamentations of Jeremiah",
      "The Book of Ezekiel",
      "The Book of Daniel",
      "The Book of Hosea",
      "The Book of Joel",
      "The Book of Amos",
      "The Book of Obadiah",
      "The Book of Jonah",
      "The Book of Micah",
      "The Book of Nahum",
      "The Book of Habakkuk",
      "The Book of Zephaniah",
      "The Book of Haggai",
      "The Book of Zechariah",
      "The Book of Malachi"
    };
    const QString      new_testament_qstr[27] =
    {
      "The Gospel according to Matthew",
      "The Gospel according to Mark",
      "The Gospel according to Luke",
      "The Gospel according to John",
      "The Acts of the Apostles",
      "The Letter of Paul to the Romans",
      "The First Letter of Paul to the Corinthians",
      "The Second Letter of Paul to the Corinthians",
      "The Letter of Paul to the Galatians",
      "The Letter of Paul to the Ephesians",
      "The Letter of Paul to the Philippians",
      "The Letter of Paul to the Colossians",
      "The First Letter of Paul to the Thessalonians",
      "The Second Letter of Paul to the Thessalonians",
      "The First Letter of Paul to the Timothy",
      "The Second Letter of Paul to the Timothy",
      "The Letter of Paul to the Titus",
      "The Letter of Paul to the Philemon",
      "The Letter of Paul to the Hebrews",
      "The Letter of James",
      "The First Letter of Peter",
      "The Second Letter of Peter",
      "The First Letter of John",
      "The Second Letter of John",
      "The Third Letter of John",
      "The Letter of Jude",
      "The Revelation to John"
    };
    const QString      bible_file_path[6] =
    {
      ":/bibles/asv.txt",
      ":/bibles/basicenglish.txt",
      ":/bibles/darby.txt",
      ":/bibles/kjv.txt",
      ":/bibles/web.txt",
      ":/bibles/ylt.txt"
    };
    const QString      old_testament_chapter_qstr[39] =
    {
      "Genesis",
      "Exodus",
      "Leviticus",
      "Numbers",
      "Deuteronomy",
      "Joshua",
      "Judges",
      "Ruth",
      "1 Samuel",
      "2 Samuel",
      "1 Kings",
      "2 Kings",
      "1 Chronicles",
      "2 Chronicles",
      "Ezra",
      "Nehemiah",
      "Esther",
      "Job",
      "Psalms",
      "Proverbs",
      "Ecclesiastes",
      "Song of Solomon",
      "Isaiah",
      "Jeremiah",
      "Lamentations",
      "Ezekiel",
      "Daniel",
      "Hosea",
      "Joel",
      "Amos",
      "Obadiah",
      "Jonah",
      "Micah",
      "Nahum",
      "Habakkuk",
      "Zephaniah",
      "Haggai",
      "Zechariah",
      "Malachi"
    };
    const QString      new_testament_chapter_qstr[27] =
    {
      "Matthew",
      "Mark",
      "Luke",
      "John",
      "Acts",
      "Romans",
      "1 Corinthians",
      "2 Corinthians",
      "Galatians",
      "Ephesians",
      "Philippians",
      "Colossians",
      "1 Thessalonians",
      "2 Thessalonians",
      "1 Timothy",
      "2 Timothy",
      "Titus",
      "Philemon",
      "Hebrews",
      "James",
      "1 Peter",
      "2 Peter",
      "1 John",
      "2 John",
      "3 John",
      "Jude",
      "Revelation"
    };

    //variables
    bool         oldOrNew       = false;
    int          rowNum         = 0;
    int          chapterNum     = 0;
    QFile        *bFile;
    QString      cutNumber;
    QString      fileName;
    QString      chosen_chapter_qstr;

    //layout
    QVBoxLayout  *bibles_tab_layout;

    //widget
    QLabel       *bible_version_label;
    QComboBox    *bible_version_combo;

    QRadioButton *old_testament_radio;
    QComboBox    *old_testament_combo;

    QRadioButton *new_testament_radio;
    QComboBox    *new_testament_combo;

    QLabel       *chapter_label;
    QLineEdit    *chapter_line_edit;

    QPushButton  *search_button;
    QRegExp      *search_regexp = new QRegExp("",Qt::CaseInsensitive);
/*
Regular Expresion:

^: match from the beginning of the string

$: ! to the end

\w: match a char from range [a~z] & [A~Z] & [_] & [0~9]

\t: match a tab key (ASCII: 0x09)

\d: match A number

{n,m}: "n" means the least number of char; "m" means the max number of char

*/
    QTabWidget   *selection_tab;
      QWidget      *selection_tab_widget;

    QGroupBox    *display_block_group;
      QListWidget  *display;

    QGroupBox    *visual_block_group;
      QHBoxLayout  *visual_block_layout;
      QSlider      *background_color_slider;
      QLabel       *background_color_label;
      QSlider      *font_size_slider ;
      QLabel       *font_size_label;
      QCheckBox    *font_bold_check;



    void openFile();
    void Read(QString Filename);
    void get_row_number(QString NameNeeded);
    void get_chapter_index();


private slots:
    void on_testament_radio_changed();
    void on_search_button_clicked();
    void set_display_parameter();
};



#endif // WIDGET_H
