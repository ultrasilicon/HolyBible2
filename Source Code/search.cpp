#include "search.h"
#include <QDebug>

Search::Search(QWidget *parent) : QWidget(parent)
{
  /* SubWindow
  QSize *mysize = new QSize(400,200);
  subWindow = new QWidget();
  subWindow->setParent(parent);

  //subWindow->setBaseSize(100,500);
  //subWindow->setBaseSize(mysize);    //err.

  subWindow->show();*/

  center_widget_layout         = new QHBoxLayout(this);
  display_visual_layout        = new QVBoxLayout();
  display_block_layout         = new QVBoxLayout();



  //////selection_tab
  selection_tab                = new QTabWidget();
  selection_tab_widget         = new QWidget;

  selection_tab->setMaximumWidth(200);
  selection_tab->addTab(selection_tab_widget," Bibles");


  {
    ///layout

    bibles_tab_layout                   = new QVBoxLayout();

    ///version
    //obj
    bible_version_label          = new QLabel("Bible Version:");
    bible_version_combo          = new QComboBox();

    //init
    bible_version_label->setMaximumHeight(30);
    for(int i = 0; i < 6; i++)
      {
        bible_version_combo->addItem(bible_version_qstr[i],i);
      }

    ///old_testament
    //obj
    old_testament_radio          = new QRadioButton("Old Testament");
    old_testament_combo          = new QComboBox();

    //init
    old_testament_radio->setObjectName(QStringLiteral("old_testament_radio"));
    old_testament_combo->setEnabled(false);
    for(int i = 0; i < 39; ++i)
      {
        old_testament_combo->addItem(old_testament_qstr[i],i);
      }

    
    ///new_testament
    //obj
    new_testament_radio          = new QRadioButton("New Testament");
    new_testament_combo          = new QComboBox();

    //init
    new_testament_combo->setEnabled(false);
    for(int i = 0; i < 27; ++i)
      {
        new_testament_combo->addItem(new_testament_qstr[i],i);
      }

    //connect


    ///chapter_edit
    //obj
    chapter_label                = new QLabel("Chapter: ");
    chapter_line_edit            = new QLineEdit();

    //init
    chapter_label->setMaximumHeight(30);
    chapter_line_edit->setMinimumHeight(20);

    ///search_button
    //obj
    search_button                = new QPushButton("Search");

    //init
    search_button->setEnabled(false);

    //connnect
    connect(search_button,SIGNAL(clicked()),this,SLOT(on_search_button_clicked()));

    ///layout
    bibles_tab_layout->addWidget(bible_version_label);
    bibles_tab_layout->addWidget(bible_version_combo);
    bibles_tab_layout->addWidget(old_testament_radio);
    bibles_tab_layout->addWidget(old_testament_combo);
    bibles_tab_layout->addWidget(new_testament_radio);
    bibles_tab_layout->addWidget(new_testament_combo);
    bibles_tab_layout->addWidget(chapter_label);
    bibles_tab_layout->addWidget(chapter_line_edit);
    bibles_tab_layout->addWidget(search_button);

    chapter_line_edit->setEnabled(false);
    selection_tab_widget->setLayout(bibles_tab_layout);
  }

  connect(old_testament_radio, SIGNAL(clicked()), this, SLOT(on_testament_radio_changed()));
  connect(new_testament_radio,SIGNAL(clicked()),this,SLOT(on_testament_radio_changed()));

  //////display_block_group
  display_block_group          = new QGroupBox("Display");
  display                      = new QListWidget();

  display->setWordWrap(true);
  display_block_group->setLayout(display_block_layout);
  display_block_layout->addWidget(display);


  /////////////////////////////////////////////////////////display

  //////visual_block_group
  visual_block_group           = new QGroupBox("Visual Settings");
  visual_block_layout          = new QHBoxLayout();
  background_color_slider      = new QSlider(Qt::Horizontal);
  background_color_label       = new QLabel("Background Color");
  font_size_slider             = new QSlider(Qt::Horizontal);
  font_size_label              = new QLabel("Font Size");
  font_bold_check              = new QCheckBox("Bold");

  background_color_label->setMaximumWidth(120);
  background_color_slider->setValue(0);
  background_color_slider->setRange(0,50);
  background_color_slider->setMaximumWidth(50);
  font_size_label->setMaximumWidth(70);
  font_size_slider ->setValue(13);
  font_size_slider ->setRange(9,20);
  font_size_slider ->setMaximumWidth(50);
  visual_block_layout->setAlignment(Qt::AlignLeft);
  visual_block_layout->addWidget(background_color_label);
  visual_block_layout->addWidget(background_color_slider);
  visual_block_layout->addWidget(font_size_label);
  visual_block_layout->addWidget(font_size_slider );
  //visual_block_layout->addWidget(font_bold_check);
  visual_block_group->setFixedHeight(65);
  visual_block_group->setLayout(visual_block_layout);

  connect(font_size_slider,SIGNAL(valueChanged(int)),this,SLOT(set_display_parameter()));
  connect(background_color_slider,SIGNAL(valueChanged(int)),this,SLOT(set_display_parameter()));
  connect(font_bold_check,SIGNAL(released()),this,SLOT(set_display_parameter()));



  //////display_visual_layout
  display_visual_layout->addWidget(display_block_group);
  display_visual_layout->addWidget(visual_block_group);

  /////////center_widget_layout
  center_widget_layout->setContentsMargins(12,12,12,12);
  center_widget_layout->addWidget(selection_tab);
  center_widget_layout->addLayout(display_visual_layout);

  set_display_parameter();


}

Search::~Search()
{
    deleteLater();
}



void Search::openFile()
{
  fileName = bible_file_path[bible_version_combo->currentIndex()];
  Read(fileName);
}

void Search::Read(QString Filename)
{
    QFile bFile(Filename);

    if(!bFile.open(QFile::ReadOnly | QFile::Text))
    {
        //qDebug()<<"error open file"<<Filename;
        return;
    }

    QTextStream in(&bFile);
    QString mText;

    QString chapterNumStr = QString::number(chapterNum);
    const int     chapter_num_length = chapterNumStr.length();
    int     removing_part_length = chosen_chapter_qstr.length();

    get_row_number(bFile.fileName());//int rowNum = 0; global variable initiallzed in the heading

    search_regexp->setPattern("^("+chosen_chapter_qstr+")(\\t)("+chapterNumStr+")(\\t)*");

    if(chapter_num_length == 1)
    {
        removing_part_length += 3;
        for(int i = 0; i <= rowNum; ++i)
        {
            mText = in.readLine();
            if(search_regexp->indexIn(mText) == 0)
            {
                mText.remove(0,removing_part_length);
                display->addItem(mText);
            }
        }

    }else if(chapter_num_length == 2)
    {
        removing_part_length += 4;
        for(int i = 0; i <= rowNum; ++i)
        {
            mText = in.readLine();
            if(search_regexp->indexIn(mText) == 0)
            {
                mText.remove(0,removing_part_length);
                display->addItem(mText);
            }
        }

    }else if(chapter_num_length == 3)
    {
        removing_part_length += 5;
        for(int i = 0; i <= rowNum; ++ i)
        {
            mText = in.readLine();
            if(search_regexp->indexIn(mText) == 0)
            {
                mText.remove(0,removing_part_length);
                display->addItem(mText);
            }
        }
    }

    mText = in.readLine();
    bFile.flush();
    bFile.close();
}

void Search::get_row_number(QString NameNeeded)
{
    QFile rowFile(NameNeeded);

    if(!rowFile.open(QFile::ReadOnly | QFile::Text))
    {
        //qDebug()<<"error";
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

void Search::get_chapter_index()
{
    if(oldOrNew)
    {
        chosen_chapter_qstr = old_testament_chapter_qstr[old_testament_combo->currentIndex()];
    }
    else if(!oldOrNew)
    {
        chosen_chapter_qstr = new_testament_chapter_qstr[new_testament_combo->currentIndex()];
    }
}


/////////////////privat slot//////////////////

void Search::on_testament_radio_changed()
{
    search_button->setEnabled(true);
    chapter_line_edit->setEnabled(true);
    if(sender() == old_testament_radio)
    {
        //in
        new_testament_combo->setEnabled(false);
        old_testament_combo->setEnabled(true);
        oldOrNew = true;
    }
    else
    {
        //in
        old_testament_combo->setEnabled(false);
        new_testament_combo->setEnabled(true);
        oldOrNew = false;
    }
}

void Search::on_search_button_clicked()
{
    display->clear();
    rowNum = 0;
    chapterNum = chapter_line_edit->text().toInt();
    get_chapter_index();
    openFile();
}

void Search::set_display_parameter()
{
  int background_color_increment = background_color_slider->value();
  if(font_bold_check->isChecked())
    {
      display->setStyleSheet("font:"+QString::number(font_size_slider->value())+"px bold;"+"background-color: rgb("+QString::number(222-background_color_increment)+","+QString::number(203-background_color_increment)+","+QString::number(157-background_color_increment)+");");
    }
  else
    {
      display->setStyleSheet("font:"+QString::number(font_size_slider->value())+"px bold;"+"background-color: rgb("+QString::number(222-background_color_increment)+","+QString::number(203-background_color_increment)+","+QString::number(157-background_color_increment)+");");
    }
}

