#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QListWidget>

#include <QVector>
#include <QString>
#include <QStringList>

#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "ToDoWidget.h"

//TODO(hugo): Add a system to create, edit and delete ToDoS

int
main(int argc, char** argv)
{
    QApplication app(argc, argv);

    //NOTE(hugo): Creating Window
    QWidget window;
    window.setWindowTitle("QTODO");
    window.resize(400,500);

    //NOTE(hugo): Creating main layout
    //IMPORTANT(hugo): Should we set the parent of mainLayout to window ?
    QVBoxLayout mainLayout;

    ToDoWidget* mainWidget = new ToDoWidget("test.txt", &window); 
    
    //NOTE(hugo): Adding it all to the layout
    mainLayout.addWidget(mainWidget->GetMainGroupBox());
    
    //NOTE(hugo): Setting the layout and displaying the window
    window.setLayout(&mainLayout);    
    window.show();
    
    return(app.exec());
}
