#include "sliders.h"
#include "ui_sliders.h"
#include <QDesktopWidget>

Sliders::Sliders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sliders)
{
    setWindowFlags( Qt::CustomizeWindowHint );

    //sets the window to full size
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    move(width, height);

    ui->setupUi(this);
}

Sliders::~Sliders()
{
    delete ui;
}

void Sliders::on_HRH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_HRL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_HYH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_HYL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_HBH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_HBL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}


void Sliders::on_SRH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_SRL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_SYH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_SYL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_SBH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_SBL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}


void Sliders::on_VRH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_VRL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_VYH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_VYL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_VBH_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}
void Sliders::on_VBL_valueChanged(int value)
{
    Q_EMIT zmena("TRC=" + this->objectName() + QString::number(value));
}

/*
void Sliders::on_hue1_valueChanged(int value)
{
    Q_EMIT zmena("hue1=" + QString::number(value));
}
void Sliders::on_hue2_valueChanged(int value)
{
    Q_EMIT zmena("hue2=" + QString::number(value));
}
void Sliders::on_hue3_valueChanged(int value)
{
    Q_EMIT zmena("hue3=" + QString::number(value));
}
void Sliders::on_hue4_valueChanged(int value)
{
    Q_EMIT zmena("hue4=" + QString::number(value));
}
void Sliders::on_hue5_valueChanged(int value)
{
    Q_EMIT zmena("hue5=" + QString::number(value));
}
void Sliders::on_hue6_valueChanged(int value)
{
    Q_EMIT zmena("hue6=" + QString::number(value));
}
void Sliders::on_saturation1_valueChanged(int value)
{
    Q_EMIT zmena("saturation1=" + QString::number(value));
}
void Sliders::on_saturation2_valueChanged(int value)
{
    Q_EMIT zmena("saturation2=" + QString::number(value));
}
void Sliders::on_saturation3_valueChanged(int value)
{
    Q_EMIT zmena("saturation3=" + QString::number(value));
}
void Sliders::on_saturation4_valueChanged(int value)
{
    Q_EMIT zmena("saturation4=" + QString::number(value));
}
void Sliders::on_saturation5_valueChanged(int value)
{
    Q_EMIT zmena("saturation5=" + QString::number(value));
}
void Sliders::on_saturation6_valueChanged(int value)
{
    Q_EMIT zmena("saturation6=" + QString::number(value));
}
void Sliders::on_value1_valueChanged(int value)
{
    Q_EMIT zmena("value1=" + QString::number(value));
}
void Sliders::on_value2_valueChanged(int value)
{
    Q_EMIT zmena("value2=" + QString::number(value));
}
void Sliders::on_value3_valueChanged(int value)
{
    Q_EMIT zmena("value3=" + QString::number(value));
}
void Sliders::on_value4_valueChanged(int value)
{
    Q_EMIT zmena("value4=" + QString::number(value));
}
void Sliders::on_value5_valueChanged(int value)
{
    Q_EMIT zmena("value5=" + QString::number(value));
}
void Sliders::on_value6_valueChanged(int value)
{
    Q_EMIT zmena("value6=" + QString::number(value));
}*/
