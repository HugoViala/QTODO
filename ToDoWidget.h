#if !defined(TODOWIDGET_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Casey Muratori $
   $Notice: (C) Copyright 2014 by Molly Rocket, Inc. All Rights Reserved. $
   ======================================================================== */

#define TODOWIDGET_H
#include <QGroupBox>
#include <QVBoxLayout>
#include <QListWidget>
#include <QVector>
#include <QString>

#include <QDebug>


#include <QFile>


//NOTE(hugo): A ToDo list is just a
//           vector<pair<string, vector<string> > >
struct ToDoCategory
{
    QString name;
    //NOTE(hugo): Can maybe be optimized with an array rather than a vector
    QVector<QString> items;
};



class ToDoWidget
{
public:
    ToDoWidget(QString filename, QWidget* window);
    ~ToDoWidget();
    QVector<ToDoCategory*> GetCategories() const {return m_categories;}
    QGroupBox *GetMainGroupBox() const {return m_mainGroupBox;}

private:
    QString m_filename;
    QVector<ToDoCategory*> m_categories;
    QGroupBox* m_mainGroupBox;
    QHBoxLayout *m_mainGroupBoxLayout;
    

    void LoadFile();
};

#endif
