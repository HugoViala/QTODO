#if !defined(TODOWIDGET_H)

#define TODOWIDGET_H
#include <QGroupBox>
#include <QVBoxLayout>
#include <QListWidget>
#include <QVector>
#include <QString>
#include <QMenuBar>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

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

struct ToDoCategoryWidget
{
    QGroupBox* GroupBox;
    QVBoxLayout* Layout;
    QListWidget* Items;
};

class ToDoWidget : public QWidget
{
    Q_OBJECT
    
 public:
    ToDoWidget(QString filename, QWidget* window);
    ~ToDoWidget();
    QVector<ToDoCategory*> GetCategories() const {return m_categories;}
    QGroupBox *GetMainGroupBox() const {return m_mainGroupBox;}
    
    public slots:
	void SaveFile();
	void addPressed();
	void delPressed();
	void addToDoItem();
	void deleteToDoItem();
	void addCatPressed();
	void delCatPressed();
	void addCategory();
	void deleteCategory();
 private:
	QString m_filename;
	QVector<ToDoCategory*> m_categories;
	QVector<ToDoCategoryWidget*> m_QCategories;
	QGroupBox* m_mainGroupBox;
	QHBoxLayout *m_mainGroupBoxLayout;
	QWidget* actionWindow;
	QLineEdit* catNameLineEdit;
	QLineEdit* toDoNameLineEdit;
    
	void LoadFile();


};

#endif
