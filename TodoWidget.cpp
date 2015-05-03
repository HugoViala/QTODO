#include "ToDoWidget.h"


ToDoWidget::ToDoWidget(QString filename, QWidget* window)
        : m_filename(filename)
{
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
        //IMPORTANT(hugo): Parent ?
        QGroupBox *CategoryGroupBox =
            new QGroupBox(CurrentCategory->name);
        QVBoxLayout *CategoryLayout = new QVBoxLayout();
        //IMPORTANT(hugo): Parent ? Is there a way to insert the
        // list widget without creating a layout ?
        QListWidget *CategoryToDos =  new QListWidget();

        for(int ItemIndex = 0;
            ItemIndex < CurrentCategory->items.size();
            ++ItemIndex)
        {
            CategoryToDos->addItem(new QListWidgetItem(CurrentCategory->items[ItemIndex], CategoryToDos));
        }
        
        CategoryLayout->addWidget(CategoryToDos);
        CategoryGroupBox->setLayout(CategoryLayout);
        m_mainGroupBoxLayout->addWidget(CategoryGroupBox);
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


