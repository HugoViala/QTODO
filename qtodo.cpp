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

#include "ToDoWidget.h"

//TODO(hugo): Maybe stock the todos in a better structure
// rather than a text file... Lua ? XML ? JSON ?

// TODO(hugo): Add an "Open File" to chose your own todofile
// TODO(hugo): Add an "Save As..." to chose where to store your own todofile


int
main(int argc, char** argv)
{
    QApplication app(argc, argv);
    /*if(argc == 1)
    {
	return();
	}*/
    //NOTE(hugo): Creating Window
    QMainWindow window;
    window.setWindowTitle("QTODO");
    window.resize(400,500);
    window.setWindowIcon(QIcon("2048.jpg"));
    
    //NOTE(hugo): Creating main layout
    //IMPORTANT(hugo): Should we set the parent of mainLayout to window ?
    QVBoxLayout mainLayout;
    
    //NOTE(hugo): Just a token to have a control structure.
    QWidget* centralWidget = new QWidget(&window);
    centralWidget->setLayout(&mainLayout);
    
    ToDoWidget* mainWidget = new ToDoWidget(QString(), &window); 
    
    window.setCentralWidget(centralWidget);

    //NOTE(hugo): Creating the Menu Bar
    //TODO(hugo): Make a more beautiful bar
    QMenuBar* menuBar = window.menuBar();
    QMenu* FileMenu = menuBar->addMenu("File");
    QMenu* ToDoMenu = menuBar->addMenu("ToDoS");
    QMenu* CatMenu = menuBar->addMenu("Category");


    FileMenu->addAction("New File...", mainWidget,
			SLOT(newFilePressed()),
			QKeySequence("Ctrl+N"));
    FileMenu->addAction("Open File...", mainWidget,
			SLOT(openFilePressed()),
			QKeySequence("Ctrl+O"));
    FileMenu->addAction("Save As...", mainWidget,
			SLOT(saveAsPressed()),
			QKeySequence("Ctrl+S"));
    
    ToDoMenu->addAction("Add ToDo", mainWidget,
			SLOT(addPressed()),
			QKeySequence("Ctrl+A"));
    ToDoMenu->addAction("Delete ToDo", mainWidget,
		    SLOT(delPressed()));
    

    CatMenu->addAction("Add Category", mainWidget,
		       SLOT(addCatPressed()));
    CatMenu->addAction("Delete Category", mainWidget,
		       SLOT(delCatPressed()));
    
    //NOTE(hugo): Adding it all to the layout
    mainLayout.addWidget(mainWidget->GetMainGroupBox());

        
    //NOTE(hugo): Setting the layout and displaying the window
    //window.setLayout(&mainLayout);
    window.show();

    
    return(app.exec());
}


