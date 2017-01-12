#ifndef TABLE_H
#define TABLE_H

#include "window.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QStringList>
#include <QString>

#include <QVector>

class Table : public QDialog
{
    Q_OBJECT

public:
        Table(QWidget *parent = 0);
        ~Table();

        QVector<QPointF> points;
private:
        QTableWidget *table();
        QPushButton *button(QString title);
        void Layout();

        QTableWidget *tabl;

private slots:
               void buttonClicked();
signals:
               void SendData(QVector<QPointF> &vec);
};

#endif // TABLE_H
