#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QKeySequence>
#include <QMenuBar>
#include <QMenu>

#include <QVector>
#include <QString>
#include <QStringList>

#include <QFile>
#include <QTextStream>


#include <QDebug>
#include <QtGlobal>

#include "ToDoWidget.h"

//TODO(hugo): Add a system to create, edit and delete ToDoS
//TODO(hugo): Maybe stock the todos in a better structure
// rather than a text file... Lua ? XML ? JSON ?


int
main(int argc, char** argv)
{
    QApplication app(argc, argv);

    //NOTE(hugo): Creating Window
    QMainWindow window;
    window.setWindowTitle("QTODO");
    window.resize(400,500);

    
    //NOTE(hugo): Creating main layout
    //IMPORTANT(hugo): Should we set the parent of mainLayout to window ?
    QVBoxLayout mainLayout;

    //NOTE(hugo): Just a token to have a control structure.
    QWidget* centralWidget = new QWidget(&window);
    centralWidget->setLayout(&mainLayout);
    
    ToDoWidget* mainWidget = new ToDoWidget("test.txt", &window); 

    window.setCentralWidget(centralWidget);
    

    //NOTE(hugo): Creating the Menu Bar
    //TODO(hugo): Make a more beautiful bar
    QMenuBar* menuBar = new QMenuBar(centralWidget);
    menuBar->setNativeMenuBar(true);
    menuBar->setDefaultUp(true);
    QMenu* menu = new QMenu("ToDoS");

    //NOTE(hugo): we could add a key shortcut here
    
    menu->addAction("Add ToDo", mainWidget,
		    SLOT(addPressed()));
    menu->addAction("Delete ToDo", mainWidget,
		    SLOT(delPressed()));
    menuBar->addMenu(menu);

    //NOTE(hugo): Adding it all to the layout
    mainLayout.addWidget(menuBar);
    mainLayout.addWidget(mainWidget->GetMainGroupBox());

        
    //NOTE(hugo): Setting the layout and displaying the window
    //window.setLayout(&mainLayout);
    window.show();

    
    return(app.exec());
}


