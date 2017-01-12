#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSlider>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include <QGraphicsScene>

#include <QVector>
#include <math.h>

#include "table.h"

class Table;

class Window : public QDialog
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

    Table *table;

protected:
            virtual void paintEvent(QPaintEvent *ev);
            virtual void mousePressEvent(QMouseEvent *ev);
            virtual void mouseReleaseEvent(QMouseEvent *ev);
            virtual void mouseMoveEvent(QMouseEvent *ev);
            virtual void keyPressEvent(QKeyEvent *ev);

private:
        QVector<QPointF> points1, points2;
        QPoint pos, posr;
        void Tab();

        QListWidget *list();
        int item_choise;

        QLabel *label(QString title);

        QSlider *slider();
        QSlider *bg_color, *fun_color;

        QCheckBox *gade, *cross;
        QPushButton *button(QString title);
        bool buttonClicked;

        QSpinBox *spin();
        QSpinBox *coefX, *coefY;

        void Layout();

private slots:
                void Changer();
                void buttonSlot();
                void ListClicked(QListWidgetItem*);
public slots:
                void RecieveData(QVector<QPointF> &vec);

};

#endif // WINDOW_H
