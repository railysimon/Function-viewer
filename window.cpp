#include "window.h"

Window::Window(QWidget *parent) : QDialog(parent), points1(300), pos(500, 100), posr(500, 100), item_choise(1)
{
    this->setFixedSize(640, 480);
    this->setWindowTitle("Function viewer");
    this->setWindowIcon(QPixmap("logo.png"));
    buttonClicked = false;

    Layout();

    table = new Table; // table-widget
    connect(table, SIGNAL(SendData(QVector<QPointF>&)), this, SLOT(RecieveData(QVector<QPointF>&)));
}

Window::~Window()
{

}

void Window::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QRect rec(160, 0, width(), height());
    painter.setRenderHint(QPainter::Antialiasing, true);

    if(ev->region().contains(rec))
    {
            QColor bg(bg_color->value(), bg_color->value(), 255-bg_color->value());
            painter.setBrush(QBrush(bg, Qt::Dense4Pattern)); // Background
            painter.drawRect(160, 0, width(), height());

            if(gade->isChecked())
            {
                painter.setPen(QPen(Qt::gray, 0, Qt::DashLine)); // bg-help-lines
                for(int i=160; i<width(); i=i+20)
                    painter.drawLine(i, 0, i, height());

                for(int i=0; i<height(); i=i+20)
                    painter.drawLine(160, i, width(), i);
            }

            if(cross->isChecked())
            {
                painter.setPen(QPen(Qt::black, 2, Qt::SolidLine)); // cross-lines
                painter.drawLine(80 + width()/2, 0, 80 + width()/2, height());
                painter.drawLine(160, height()/2, width(), height()/2);

                int text_pos = 0;

                for(int i=160; i<width(); i=i+20)
                {
                    painter.drawLine(i, height()/2 - 3, i, height()/2 + 3);
                    if(i == width()/2 + 80)
                    {
                        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                        painter.drawEllipse(i-3, height()/2-3, 6, 6);
                    }
                    painter.setFont(QFont("Ubuntu", 6, QFont::Normal));
                    painter.drawText(i+2, height()-3, QString::number(-240 + text_pos));
                    text_pos += 20;
                }

                for(int i=0; i<height(); i=i+20)
                {
                    if(i == height()/2) continue;
                    painter.drawLine(80 + width()/2 - 3, i, 80 + width()/2 + 3, i);
                    painter.drawText(width()-17, i, QString::number(-240*(-1) - i));
                }
            }
            if(buttonClicked)
            {
                Tab();

                QColor fun(255-fun_color->value(), 255-fun_color->value(), fun_color->value());
                painter.setPen(QPen(fun, 2, Qt::SolidLine)); // functions-build

                for(int i=0; i<points1.size()-1; i++)
                {
                    if((points1[i].x() > 160) && (points1[i].x() < width()))
                      painter.drawLine(points1[i], points1[i+1]);
                }

                painter.setFont(QFont("Ubuntu", 12, QFont::Bold)); // choice-point and help lines
                painter.drawText(width()-120, 20, "X: " + QString::number(posr.x()- width()/2 - 80)
                                 + " Y: " + QString::number((-1)*(posr.y()-height()/2)));
                painter.setPen(QPen(Qt::green, 2, Qt::SolidLine));

                if(posr.x() > 160)
                {
                    painter.drawLine(posr.x(), posr.y(), posr.x(), height()/2);
                    painter.drawLine(posr.x(), posr.y(), 80 + width()/2, posr.y());
                    painter.setBrush(Qt::yellow);
                    painter.drawEllipse(posr, 3, 3);
                }
            }
            else // handmake - function
            {
                if((pos.x() > 160))
                {
                    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern)); // first link with points
                    painter.drawEllipse(pos, 3, 3);
                    painter.drawLine(pos, posr);
                    painter.drawEllipse(posr, 3, 3);
                }

                for(int i=0; i<points2.size()-1; i++) // drawing vector of links
                {
                    painter.drawEllipse(points2[i], 3, 3);
                    painter.drawLine(points2[i], points2[i+1]);
                    painter.drawEllipse(points2[i+1], 3, 3);
                }

            }
    }
}

void Window::mousePressEvent(QMouseEvent *ev)
{
    pos = ev->pos();
    QPointF temp(ev->x(), ev->y());

    if(ev->x() > 160) points2.push_front(temp); // vector of links
}

void Window::mouseReleaseEvent(QMouseEvent *ev)
{
    posr = ev->pos();
    QWidget::update();
}

void Window::mouseMoveEvent(QMouseEvent *ev)
{
    posr = ev->pos();
    QWidget::update();
}

void Window::keyPressEvent(QKeyEvent *ev)
{
    if(ev->modifiers() == Qt::ControlModifier && ev->key() == Qt::Key_Z)
        if(!(points2.isEmpty())) points2.pop_front(); // del last link

    if(ev->key() == Qt::Key_A) posr.setX(posr.x()-1);
    if(ev->key() == Qt::Key_D) posr.setX(posr.x()+1);
    if(ev->key() == Qt::Key_W) posr.setY(posr.y()-1);
    if(ev->key() == Qt::Key_S) posr.setY(posr.y()+1);

    QWidget::update();
}

void Window::Tab() // tabulation of functions
{
    int step = -150;

    for(int i=0; i<points1.size(); i++)
    {
        switch (item_choise)
        {
            case 1: { points1[i].setX(coefX->value()*step + width()/2 + 80);
                      points1[i].setY(coefY->value()*(-1)*pow(step, 2) + height()/2);
                      break;
                    }

            case 2: { points1[i].setX(coefX->value()*step + width()/2 + 80);
                      points1[i].setY(coefY->value()*sin(step) + height()/2);
                      break;
                    }

            case 3: { points1[i].setX(coefX->value()*step + width()/2 + 80);
                      points1[i].setY(coefY->value()*pow(step, 3) + height()/2);
                      break;
                    }

            case 4: { points1[i].setX(coefX->value()*step + width()/2 + 80);
                      points1[i].setY(coefY->value()*cos(step) + height()/2);
                      break;
                    }
        }

        step++;
    }
}

QListWidget *Window::list() // list - factory
{
    QListWidget *lst = new QListWidget;
    lst->setFixedSize(140, 80);
    lst->setCursor(Qt::PointingHandCursor);
    QListWidgetItem *item;

    QString names[] = {"x^2", "sin(x)", "x^3", "cos(x)", "tableset func"};
    lst->setIconSize(QSize(20,20));

    for(int i=0; i<5; i++)
    {
        item = new QListWidgetItem(names[i], lst);
        item->setIcon(QPixmap(names[i] + ".png"));
    }

    connect(lst, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(ListClicked(QListWidgetItem*)));

    return lst;

}

QLabel *Window::label(QString title) // label - factory
{
    QLabel *lbl = new QLabel;
    lbl->setFixedSize(160, 15);
    lbl->setFont(QFont("Ubuntu", 10, QFont::Normal));
    lbl->setText(title);

    return lbl;
}

QSlider *Window::slider() // slider - factory
{
    QSlider *slider = new QSlider;
    slider->setFixedWidth(120);
    slider->setOrientation(Qt::Horizontal);
    slider->setCursor(Qt::PointingHandCursor);
    slider->setMinimum(0);
    slider->setMaximum(255);
    slider->setValue(230);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(Changer()));

    return slider;
}

QPushButton *Window::button(QString title) // button - factory
{
    QPushButton *btn = new QPushButton(title);
    btn->setFont(QFont("Ubuntu", 10, QFont::Bold));
    btn->setCursor(Qt::PointingHandCursor);
    btn->setFixedWidth(140);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonSlot()));

    return btn;
}

QSpinBox *Window::spin() // spinbox - factory
{
    QSpinBox *spn = new QSpinBox;
    spn->setCursor(Qt::PointingHandCursor);
    spn->setMaximum(50);
    spn->setMinimum(1);
    spn->setFixedWidth(65);
    spn->setValue(4);

    static int i = 0;
    if(i) spn->setValue(1);
    i++;

    connect(spn, SIGNAL(valueChanged(int)), this, SLOT(Changer()));

    return spn;
}

void Window::Layout()
{
    QListWidget *lst = list();
    QLabel *lbl = label("Choose function:");

    bg_color = slider();
    fun_color = slider();

    QGroupBox *colors = new QGroupBox("Colors");
    colors->setFixedSize(140, 100);
    QVBoxLayout *group = new QVBoxLayout; // groupbox of colors

    group->addWidget(bg_color);
    group->addWidget(fun_color);;
    colors->setLayout(group);

    gade = new QCheckBox("Gates"); // checkboxes
    gade->setChecked(true);
    gade->setCursor(Qt::PointingHandCursor);

    cross = new QCheckBox("Cross-lines");
    cross->setChecked(true);
    cross->setCursor(Qt::PointingHandCursor);

    connect(gade, SIGNAL(clicked(bool)), this, SLOT(Changer()));
    connect(cross, SIGNAL(clicked(bool)), this, SLOT(Changer()));

    QLabel *coef = label("Coefficientes: "); // spins
    coefX = spin(); coefY = spin();
    QHBoxLayout *coflay = new QHBoxLayout;
    coflay->setAlignment(Qt::AlignLeft);
    coflay->addWidget(coefX);
    coflay->addWidget(coefY);

    QPushButton *paint = button("Paint"); // buttons
    QPushButton *clear = button("Clear");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    layout->addWidget(lbl);
    layout->addWidget(lst);
    layout->addWidget(colors);
    layout->addWidget(gade);
    layout->addWidget(cross);
    layout->addSpacing(20);
    layout->addWidget(coef);
    layout->addLayout(coflay);
    layout->addSpacing(70);
    layout->addWidget(paint);
    layout->addWidget(clear);

    this->setLayout(layout);
}

void Window::Changer()
{
    QWidget::update();
}

void Window::buttonSlot()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    if(btn->text() == "Paint") buttonClicked = true;
    if(btn->text() == "Clear")
    {
        buttonClicked = false;
        points2.clear();
    }

    QWidget::update();
}

void Window::ListClicked(QListWidgetItem *item)
{
    QString names[] = {"x^2", "sin(x)", "x^3", "cos(x)", "tableset func"};

    for(int i=0; i<5; i++)
    {
        if(item->text() == names[i])
        {
            item_choise = i+1;
            break;
        }
    }


    coefX->setEnabled(true);
    coefY->setEnabled(true);

    if(item_choise == 5)
    {
        table->show();
        coefX->setEnabled(false);
        coefY->setEnabled(false);
    }
}

void Window::RecieveData(QVector<QPointF> &vec)
{
    points1.clear();
    points1.resize(300);

    for(int i=0; i<vec.size(); i++)
    {
        vec[i].setX(vec[i].x() + width()/2 + 80);
        vec[i].setY((-1)*vec[i].y() + height()/2);
    }

    for(int i=0; i<vec.size(); i++)
        points1[i] = vec[i];
}
