#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject> //to
#include <QMainWindow> //to be
#include <player.h> //to display štít
#include <second.h> //second
#include <servo.h> //servo
#include <gamepadmonitor.h> //to read from gamepad
#include <dialog.h> //dialog
#include <tcpserver.h>
#include <sliders.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int timerId;
    void sendDataTcp();
    void updateLabels();
    GamepadMonitor *monitor;
    Second *second; //second
    Dialog *dialog; //dialog
    Sliders *sliders; //sliders
    Servo servo; //serialPort controller

    Player* player0; //cameraview0
    Player* player1; //cameraview1
    Player* player2; //cameraview2
    Player* player3; //cameraview3

    int tcpTimer = 0; // used with timer, goes off everytime it reaches 200
    int freq = 5; //frequency of the timer going off in ms

    unsigned char* command;
    unsigned char checkSum;

    bool serialIsOpen = false;

public Q_SLOTS:
    void msgReceived(QString message);
    void zmenaReceived(QString message);
    void on_checkBox_toggled(bool checked);
    void on_ob0_clicked();
    void on_ob1_clicked();
    void on_ob2_clicked();

protected:
   void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
