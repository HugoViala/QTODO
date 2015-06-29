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
	    CurrentCategoryWidget->Layout = new QVBoxLayout();
	    //IMPORTANT(hugo): Parent ? Is there a way to insert the
	    // list widget without creating a layout ?
	    CurrentCategoryWidget->Items =  new QListWidget();

	    for(int ItemIndex = 0;
		ItemIndex < CurrentCategory->items.size();
		++ItemIndex)
		{
		    CurrentCategoryWidget->Items->addItem(
							  new QListWidgetItem(CurrentCategory->items[ItemIndex],
									      CurrentCategoryWidget->Items));
		}
        
	    CurrentCategoryWidget->Layout->addWidget(CurrentCategoryWidget->Items);
	    CurrentCategoryWidget->GroupBox->setLayout(CurrentCategoryWidget->Layout);
	    m_mainGroupBoxLayout->addWidget(CurrentCategoryWidget->GroupBox);

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

//TODO(hugo): Test this.
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
}

//TODO(hugo): Test this.
void
ToDoWidget::deleteToDoItem()
{
    QString ItemName = toDoNameLineEdit->text();
    qDebug(ItemName.toLatin1());
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
			    break;
			}
		}

	    if(FoundIndex != -1)
		m_QCategories[CategoryIndex]->
		    Items->takeItem(FoundIndex);
	}

    delete actionWindow;
}


void
ToDoWidget::SaveFile()
{
}

void
ToDoWidget::addPressed()
{
    
    actionWindow = new QWidget();
    actionWindow->setVisible(true);
    actionWindow->setWindowTitle("What to add ?");

    //TODO(hugo): Set the window size
    
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

#include "ToDoWidget.moc"
		       
		       
