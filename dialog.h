#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsLineItem>



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QTimer *timer;
    void changeLine(float x, int y);

private Q_SLOTS:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void randomHeight ();



private:
    int randomTimer();
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *line;

};

#endif // DIALOG_H
