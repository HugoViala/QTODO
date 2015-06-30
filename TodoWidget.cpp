#include "ToDoWidget.h"


ToDoWidget::ToDoWidget(QString filename, QWidget* window)
    : m_filename(filename), m_categories(), m_QCategories()
{
    QWidget();
    LoadFile();
    
    //NOTE(hugo): Creating the main groupBox containing all the 
    //IMPORTANT(hugo): What should the parent of this widget be ?
    m_mainGroupBox = new QGroupBox("ToDo", window);

    //IMPORTANT(hugo): Parent ?
    m_mainGroupBoxLayout = new QHBoxLayout();;

    for(int CategoryIndex = 0;
	CategoryIndex < m_categories.size();
	++CategoryIndex)
	{
	    ToDoCategory* CurrentCategory = m_categories[CategoryIndex];
	    ToDoCategoryWidget* CurrentCategoryWidget = new ToDoCategoryWidget();
	    //IMPORTANT(hugo): Parent ?
	    CurrentCategoryWidget->GroupBox =
		new QGroupBox(CurrentCategory->name);
	    CurrentCategoryWidget->GroupBox->
		setStyleSheet("color: " + color(CategoryIndex));
	    CurrentCategoryWidget->Layout = new QVBoxLayout();
	    //IMPORTANT(hugo): Parent ? Is there a way to insert the
	    // list widget without creating a layout ?
	    CurrentCategoryWidget->Items =  new QListWidget();

	    for(int ItemIndex = 0;
		ItemIndex < CurrentCategory->items.size();
		++ItemIndex)
		{
		    CurrentCategoryWidget->Items->addItem(new QListWidgetItem(CurrentCategory->items[ItemIndex],
									      CurrentCategoryWidget->Items));
		}
        
	    CurrentCategoryWidget->Layout->
		addWidget(CurrentCategoryWidget->Items);
	    CurrentCategoryWidget->GroupBox->
		setLayout(CurrentCategoryWidget->Layout);
	    m_mainGroupBoxLayout->
		addWidget(CurrentCategoryWidget->GroupBox);

	    m_QCategories.append(CurrentCategoryWidget);
	}

    m_mainGroupBox->setLayout(m_mainGroupBoxLayout);
}

ToDoWidget::~ToDoWidget()
{

}


void
ToDoWidget::LoadFile()
{
    QFile file(m_filename);
    if(file.open(QIODevice::ReadOnly))
	{
	    QTextStream in(&file);
	    uint CategoryCount = in.readLine().toUInt();

	    for(int CategoryIndex = 0;
		CategoryIndex < CategoryCount;
		++CategoryIndex)
		{
		    //NOTE(hugo): Processing the current category in the file
		    ToDoCategory *category = new ToDoCategory();
		    QString categoryLine = in.readLine();
		    QStringList CategoryLineSplitted = categoryLine.split(" ");
		    uint itemCount = CategoryLineSplitted[0].toUInt();
		    category->name = CategoryLineSplitted[1];
		    for(int ItemIndex = 0;
			ItemIndex < itemCount;
			++ItemIndex)
			{
			    category->items.append(in.readLine());
			}

		    m_categories.append(category);
		}
	    file.close();
	}
    else
	{
	    qDebug() << "Could not open file";
	}
}

void
ToDoWidget::addToDoItem()
{
    QString CategoryName = catNameLineEdit->text();
    QString ItemName = toDoNameLineEdit->text();
    
    for(int CategoryIndex = 0;
	CategoryIndex < m_categories.size();
	CategoryIndex++)
	{
	    
	    if(m_categories[CategoryIndex]->name == CategoryName)
		{
		    m_categories[CategoryIndex]->items.push_back(ItemName);

		    //NOTE(hugo): I assume that m_categories and m_QCategories
		    // are correlated concerning the category they represent

		    m_QCategories[CategoryIndex]->Items->addItem(
								 new QListWidgetItem(ItemName,
										     m_QCategories[CategoryIndex]->Items));
		    break;
		}
	}

    delete actionWindow;
    SaveFile();
}

void
ToDoWidget::deleteToDoItem()
{
    QString ItemName = toDoNameLineEdit->text();
    bool found = false;
    for(int CategoryIndex = 0;
	CategoryIndex < m_categories.size();
	CategoryIndex++)
	{
	    int FoundIndex = -1;
	    for(int ItemIndex = 0;
		ItemIndex < m_categories[CategoryIndex]->
		    items.size();
		ItemIndex++)
		{
		    QString currentItem = m_categories[CategoryIndex]->
			items[ItemIndex];
		    if(QString::compare(currentItem,
					ItemName)
		       == 0)
			{
			    FoundIndex = ItemIndex;
			    m_categories[CategoryIndex]->
				items.remove(ItemIndex);
			    found = true;
			    break;
			}
		}

	    if(FoundIndex != -1)
		m_QCategories[CategoryIndex]->
		    Items->takeItem(FoundIndex);

	}
    if(!found)
	QMessageBox::warning(0,
			     "ToDo not found",
			     "ToDo not found");

    delete actionWindow;
    SaveFile();
}


void
ToDoWidget::SaveFile()
{
    //NOTE(hugo) : To avoid any issues, we delete the file
    // each time so that it is not overwritten
    QFile::remove(m_filename);
    
    QString textFile;

    //NOTE(hugo): computing textFile
    textFile += QString::number(m_categories.size());
    textFile += "\n";
    for(int CatIndex = 0;
	CatIndex < m_categories.size();
	CatIndex++)
	{
	    ToDoCategory* currentCategory = m_categories[CatIndex];
	    textFile += QString::number(currentCategory->
					items.size());
	    textFile += " ";
	    textFile += currentCategory->name;
	    textFile += "\n";

	    for(int ItemIndex = 0;
		ItemIndex < currentCategory->items.size();
		ItemIndex++)
		{
		    textFile += currentCategory->items[ItemIndex];
		    textFile += "\n";
		}
	}
    
    QFile file(m_filename);
    if(file.open(QIODevice::ReadWrite))
	{
	    QTextStream stream(&file);
	    stream << textFile;
	}
    else
	{
	    qDebug("Failing to open the file.");
	}
    
}

void
ToDoWidget::addPressed()
{
    
    actionWindow = new QWidget();
    actionWindow->setVisible(true);
    actionWindow->setWindowTitle("What to add ?");
    
    actionWindow->resize(200,100);
    
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QLabel* catNameLabel = new QLabel("Category Name",
				      actionWindow);
    catNameLineEdit = new QLineEdit(actionWindow);
    QLabel* toDoNameLabel = new QLabel("ToDo Name",
				       actionWindow);
    toDoNameLineEdit = new QLineEdit(actionWindow);
    
    QPushButton* okButton = new QPushButton("Valider",
					    actionWindow);
    
    
    mainLayout->addWidget(catNameLabel);
    mainLayout->addWidget(catNameLineEdit);
    mainLayout->addWidget(toDoNameLabel);
    mainLayout->addWidget(toDoNameLineEdit);
    mainLayout->addWidget(okButton);
    
    actionWindow->setLayout(mainLayout);

    QObject::connect(okButton,
		     SIGNAL(clicked()),
			 this,
		     SLOT(addToDoItem()));
}


void
ToDoWidget::delPressed()
{
    
    actionWindow = new QWidget();
    actionWindow->setVisible(true);
    actionWindow->setWindowTitle("What to delete ?");

    actionWindow->resize(200,100);
    
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QLabel* toDoNameLabel = new QLabel("ToDo Name",
				       actionWindow);
    toDoNameLineEdit = new QLineEdit(actionWindow);
    
    QPushButton* okButton = new QPushButton("Valider",
					    actionWindow);
    
    mainLayout->addWidget(toDoNameLabel);
    mainLayout->addWidget(toDoNameLineEdit);
    mainLayout->addWidget(okButton);
    
    actionWindow->setLayout(mainLayout);
    
    QObject::connect(okButton,
		     SIGNAL(clicked()),
		     this,
		     SLOT(deleteToDoItem()));
}

void
ToDoWidget::addCatPressed()
{
    actionWindow = new QWidget();
    actionWindow->setVisible(true);
    actionWindow->setWindowTitle("Category Name");

    actionWindow->resize(200,100);
    
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QLabel* catNameLabel = new QLabel("Category Name",
				       actionWindow);
    catNameLineEdit = new QLineEdit(actionWindow);
    
    QPushButton* okButton = new QPushButton("Valider",
					    actionWindow);
    
    mainLayout->addWidget(catNameLabel);
    mainLayout->addWidget(catNameLineEdit);
    mainLayout->addWidget(okButton);
    
    actionWindow->setLayout(mainLayout);
    
    QObject::connect(okButton,
		     SIGNAL(clicked()),
		     this,
		     SLOT(addCategory()));
}

void
ToDoWidget::delCatPressed()
{
    actionWindow = new QWidget();
    actionWindow->setVisible(true);
    actionWindow->setWindowTitle("What to delete ?");

    actionWindow->resize(200,100);
    
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QLabel* catNameLabel = new QLabel("Category Name",
				       actionWindow);
    catNameLineEdit = new QLineEdit(actionWindow);
    
    QPushButton* okButton = new QPushButton("Valider",
					    actionWindow);
    
    mainLayout->addWidget(catNameLabel);
    mainLayout->addWidget(catNameLineEdit);
    mainLayout->addWidget(okButton);
    
    actionWindow->setLayout(mainLayout);
    
    QObject::connect(okButton,
		     SIGNAL(clicked()),
		     this,
		     SLOT(deleteCategory()));
}

void
ToDoWidget::addCategory()
{
    QString catName = catNameLineEdit->text();
    ToDoCategory* newCategory = new ToDoCategory();
    newCategory->name = catName;
    newCategory->items = QVector<QString>();

    m_categories.append(newCategory);

    ToDoCategoryWidget* newQCategory = new ToDoCategoryWidget();
    newQCategory->GroupBox = new QGroupBox(catName,
					   this);
    newQCategory->GroupBox->
	setStyleSheet("color: " + color(m_QCategories.size()+ 1));
    newQCategory->Layout = new QVBoxLayout();
    newQCategory->Items = new QListWidget();

    newQCategory->Layout->addWidget(newQCategory->Items);
    newQCategory->GroupBox->setLayout(newQCategory->Layout);
    m_mainGroupBoxLayout->addWidget(newQCategory->GroupBox);

    m_QCategories.append(newQCategory);

    
    delete actionWindow;

    SaveFile();
}

void
ToDoWidget::deleteCategory()
{

    QString categoryName = catNameLineEdit->text();
    int FoundIndex = -1;

    for(int CatIndex = 0;
	CatIndex < m_categories.size();
	CatIndex++)
	{
	    QString currentCategoryName =
		m_categories[CatIndex]->name;
	    if(QString::compare(currentCategoryName,
				categoryName) == 0)
		{
		    FoundIndex = CatIndex;
		    break;
		}
	}

    if(FoundIndex != -1)
	{
	    m_mainGroupBoxLayout->removeWidget(
		       m_QCategories[FoundIndex]->GroupBox);
    
	    delete m_QCategories[FoundIndex]->GroupBox;

	    m_categories[FoundIndex]->items.clear();
    
	    delete m_categories[FoundIndex];
	    delete m_QCategories[FoundIndex];
	    m_categories.remove(FoundIndex);
	    m_QCategories.remove(FoundIndex);
	}
    else
	{
	    QMessageBox::warning(0,
				 "Category not found",
				 "Category not found");
	}
    
    delete actionWindow;

    SaveFile();
}

QString
ToDoWidget::color(int i)
{
    if(i == 0)
	return "blue";
    if(i == 1)
	return "darkorange";
    if(i == 2)
	return "green";
    if(i == 3)
	return "gold";
    if(i == 4)
	return "red";

    return "black";
}


#include "ToDoWidget.moc"
		       

