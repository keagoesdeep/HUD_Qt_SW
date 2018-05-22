#include "second.h"
#include "ui_second.h"
#include <QDesktopWidget>

Second::Second(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Second)
{
    setWindowFlags( Qt::CustomizeWindowHint );

    //sets the window to full size
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    move(width, height);

    ui->setupUi(this);
}

Second::~Second()
{
    delete ui;
}

int Second::getCislo() const
{
    return cislo;
}

void Second::setCislo(int value)
{
    cislo = value;
}
