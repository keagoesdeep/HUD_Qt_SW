#ifndef SLIDERS_H
#define SLIDERS_H

#include <QDialog>
#include <qdebug.h>

namespace Ui {
class Sliders;
}

class Sliders : public QDialog
{
    Q_OBJECT

public:
    explicit Sliders(QWidget *parent = 0);
    ~Sliders();

Q_SIGNALS:
    void zmena(QString);


private Q_SLOTS:
    /*
    void on_hue1_valueChanged(int value);
    void on_hue2_valueChanged(int value);
    void on_hue3_valueChanged(int value);
    void on_hue4_valueChanged(int value);
    void on_hue5_valueChanged(int value);
    void on_hue6_valueChanged(int value);
    void on_saturation1_valueChanged(int value);
    void on_saturation2_valueChanged(int value);
    void on_saturation3_valueChanged(int value);
    void on_saturation4_valueChanged(int value);
    void on_saturation5_valueChanged(int value);
    void on_saturation6_valueChanged(int value);
    void on_value1_valueChanged(int value);
    void on_value2_valueChanged(int value);
    void on_value3_valueChanged(int value);
    void on_value4_valueChanged(int value);
    void on_value5_valueChanged(int value);
    void on_value6_valueChanged(int value);*/

    void on_HRH_valueChanged(int value);
    void on_HRL_valueChanged(int value);
    void on_HYH_valueChanged(int value);
    void on_HYL_valueChanged(int value);
    void on_HBH_valueChanged(int value);
    void on_HBL_valueChanged(int value);
    void on_SRH_valueChanged(int value);
    void on_SRL_valueChanged(int value);
    void on_SYH_valueChanged(int value);
    void on_SYL_valueChanged(int value);
    void on_SBH_valueChanged(int value);
    void on_SBL_valueChanged(int value);
    void on_VRH_valueChanged(int value);
    void on_VRL_valueChanged(int value);
    void on_VYH_valueChanged(int value);
    void on_VYL_valueChanged(int value);
    void on_VBH_valueChanged(int value);
    void on_VBL_valueChanged(int value);

private:
    Ui::Sliders *ui;



};


#endif // SLIDERS_H
