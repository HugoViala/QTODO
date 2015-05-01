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
    window.setWindowTitle("Test window title");
    window.resize(300,90);
    
    // vertLayout is the main layout of the window
    QBoxLayout vertLayout(QBoxLayout::TopToBottom, &window);

    // top groupBox to contain the label and the quit button
    QGroupBox groupBox("Horizontal", &window);
    
    
    // boxLayout is the layout of groupBox
    QBoxLayout boxLayout(QBoxLayout::LeftToRight, &groupBox);  

    // The label to be displayed
    QLabel testLabel(&window);
    testLabel.setFrameRect(QRect(0,0, 10, 30));
    testLabel.setFrameStyle(QFrame::Panel);
    testLabel.setLineWidth(2);
    
    // A quit button
    QPushButton quitButton("Quit", &window);
    quitButton.move(200,15);

    // Adding the widgets to the groupbox layout
    boxLayout.addWidget(&testLabel);
    boxLayout.addWidget(&quitButton);
    
    QLineEdit line("Type text", &window);
    vertLayout.addWidget(&groupBox);
    vertLayout.addWidget(&line);

    
    QObject::connect(&line, &QLineEdit::textChanged,
                     &testLabel, &QLabel::setText);
    QObject::connect(&quitButton, &QPushButton::clicked,
                     &app, &QApplication::quit);

    window.setLayout(&vertLayout);
    window.show();
    
    return(app.exec());
}
