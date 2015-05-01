#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>

//TODO(hugo): How are the data stored ? XML File ? Simple file ?
//TODO(hugo): Add a system to create, edit and delete ToDoS

int
main(int argc, char** argv)
{
    QApplication app(argc, argv);

    //NOTE(hugo): Creating Window
    QWidget window;
    window.setWindowTitle("QTODO");
    window.resize(400,500);

    //TODO(hugo): Loading the file and getting all the infos

    //NOTE(hugo): Creating main layout
    //IMPORTANT(hugo): Should we set the parent of mainLayout to window ?
    QVBoxLayout mainLayout;

    //NOTE(hugo): Creating the main groupBox containing all the 
    //IMPORTANT(hugo): What should the parent of this widget be ?
    QGroupBox mainGroupBox("ToDo", &window);

    //IMPORTANT(hugo): Parent ?
    QHBoxLayout mainGroupBoxLayout;

    mainGroupBox.setLayout(&mainGroupBoxLayout);

    //NOTE(hugo): Adding it all to the layout
    mainLayout.addWidget(&mainGroupBox);
    
    //NOTE(hugo): Setting the layout and displaying the window
    window.setLayout(&mainLayout);    
    window.show();
    
    return(app.exec());
}
