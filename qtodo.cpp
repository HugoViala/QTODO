#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>

#include <QVector>
#include <QString>

//NOTE(hugo): A ToDo list is just a
//           vector<pair<string, vector<string> > >
struct ToDoCategory
{
    QString name;
    //NOTE(hugo): Can maybe be optimized with an array rather than a vector
    QVector<QString> items;
};

QVector<ToDoCategory*>
ReadFile(char* fileName)
{
    //TODO(hugo): Implement

    return(QVector<ToDoCategory*>());
}

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
    //IMPORTANT(hugo): For now, I decided that the datas will be
    // stored in a .td file
    QVector<ToDoCategory*> todolist = ReadFile("test.txt");

    //NOTE(hugo): Creating main layout
    //IMPORTANT(hugo): Should we set the parent of mainLayout to window ?
    QVBoxLayout mainLayout;

    //NOTE(hugo): Creating the main groupBox containing all the 
    //IMPORTANT(hugo): What should the parent of this widget be ?
    QGroupBox mainGroupBox("ToDo", &window);

    //IMPORTANT(hugo): Parent ?
    QHBoxLayout mainGroupBoxLayout;

    //TODO(hugo): Process todolistvector and display it
    // in the proper widget (QListView ??)

    mainGroupBox.setLayout(&mainGroupBoxLayout);

    //NOTE(hugo): Adding it all to the layout
    mainLayout.addWidget(&mainGroupBox);
    
    //NOTE(hugo): Setting the layout and displaying the window
    window.setLayout(&mainLayout);    
    window.show();
    
    return(app.exec());
}
