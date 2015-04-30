#include <QApplication>
#include <QPushButton>

int
main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QPushButton myButton("Hello button", 0);
    myButton.resize(300,90);

    myButton.show();
    return(app.exec());
}
