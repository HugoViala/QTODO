#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>

int
main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // Creating Window
    QWidget window;
    window.setWindowTitle("QTODO");
    window.resize(400,500);
    
    window.show();
    
    return(app.exec());
}
