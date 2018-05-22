#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QtMath>
#include <QTimer>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMinimumSize(680,400);

    line = scene->addLine(QLineF(0, 50, 50, 50));

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(randomHeight()));
    timer->start(500);
}

int Dialog::randomTimer()
{
    return qrand() % ((150 + 1) - 0) + 0;
}

void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    line->setLine(0, 50, 50, 50);
    float degree = arg1.toFloat();
    float radians = qDegreesToRadians(degree);
    int x2 = 25* qCos(radians);
    int y2 = 25* qSin(radians);
    int x1 = -25* qCos(radians);
    int y1 = -25* qSin(radians);
    line->setLine(x1, y1, x2, y2);
}

void Dialog::randomHeight()
{
    int mess = randomTimer();
    if (mess > 150)
    {
        mess = 150;
    }
    line->resetTransform();
    line->setPos(0, mess);
}

void Dialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    int degree = arg1.toInt();
    if (degree > 150)
    {
        degree = 150;
    }
    line->resetTransform();
    line->setPos(0, degree);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeLine(float x, int y)
{
    line->setLine(0, 50, 50, 50);
    float degree = x;
    float radians = qDegreesToRadians(degree);
    int x2 = 25* qCos(radians);
    int y2 = 25* qSin(radians);
    int x1 = -25* qCos(radians);
    int y1 = -25* qSin(radians);
    line->setLine(x1, y1, x2, y2);


    if (false)//(y > 150)
    {
        y = 150;
    }
    line->resetTransform();
    line->setPos(0, y);
}
