#ifndef SECOND_H
#define SECOND_H

#include <QDialog>

namespace Ui {
class Second;
}

class Second : public QDialog
{
    Q_OBJECT

public:
    explicit Second(QWidget *parent = 0);
    ~Second();


    int getCislo() const;
    void setCislo(int value);



private:
    Ui::Second *ui;
    int cislo = 48;




};


#endif // SECOND_H
