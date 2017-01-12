#include "table.h"

Table::Table(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(270, 200);
    this->setWindowTitle("Tableset function");
    this->setWindowIcon(QPixmap("logo.png"));

    Layout();
}

Table::~Table()
{

}

QTableWidget *Table::table()
{
    QTableWidget *tbl = new QTableWidget(300,2);
    QTableWidgetItem *item;

    QStringList lst;
    lst << "X" << "Y";
    tbl->setHorizontalHeaderLabels(lst);

    for(int i=0; i<300; i++)
        for(int j=0; j<2; j++)
    {
        item = new QTableWidgetItem("");
        tbl->setItem(i,j, item);
    }


    return tbl;
}


QPushButton *Table::button(QString title)
{
   QPushButton *btn = new QPushButton(title);
   btn->setFont(QFont("Ubuntu", 10, QFont::Bold));
   btn->setCursor(Qt::PointingHandCursor);
   connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));

   return btn;
}

void Table::Layout()
{
    tabl = table();
    QPushButton *btn = button("Ok");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tabl);
    layout->addWidget(btn);
    this->setLayout(layout);
}

void Table::buttonClicked()
{
    QPointF temp;
    for(int i=0; i<300; i++)
    {
        for(int j=0; j<2; j++)
        {
            if(tabl->item(i,0)->text() != "" && tabl->item(i,1)->text() != "")
            {
               if(!j) temp.setX((tabl->item(i, j)->text()).toInt());
               if(j) temp.setY((tabl->item(i, j)->text()).toInt());
            }

        }

        points.push_back(temp);
    }

    emit SendData(points);
    points.clear();

 }

