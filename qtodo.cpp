#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

int
main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Test window title");
    window.resize(300,90);

    QPushButton quitButton("Quit", &window);
    QLabel testLabel(&window);
    testLabel.setText("AAAAAAAAA");
    testLabel.setFrameRect(QRect(0,0, 10, 30));
    testLabel.setFrameStyle(QFrame::Panel);
    testLabel.setLineWidth(2);
    testLabel.move(50,15);
    quitButton.move(200,15);
    //quitButton.resize(300,90);

    QLineEdit line("Type text", &window);
    line.move(50,60);
    
    window.show();


    QObject::connect(&line, SIGNAL(textChanged(QString)), &testLabel, SLOT(setText(QString)));
    QObject::connect(&quitButton, &QPushButton::clicked, &app, &QApplication::quit);
    
    return(app.exec());
}
