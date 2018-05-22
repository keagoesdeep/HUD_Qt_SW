#ifndef GAMEPADMONITOR_H
#define GAMEPADMONITOR_H

#include <QtCore/QObject>
#include <QtGamepad/QGamepad>
#include <QDebug>
#include <tcpserver.h>
#include <sliders.h>

class GamepadMonitor : public QObject
{
   Q_OBJECT
public:
    explicit GamepadMonitor(QObject *parent = 0);
    ~GamepadMonitor();

    QGamepad *m_gamepad;
    TcpServer server;

    //CONFIG
    int motionMid = 128; //strafe, fwdbwd, turn, rsdv
    int motionRadius = 128; // range is <motionMid-motionRadius; motionMid+motionRadius>
    int gripper1Mid = 1;
    int gripper1Radius = 1;
    int gripper2Mid = 4;
    int gripper2Radius = 4;
    int gainMid = 50;
    int gainRadius = 50;
    int gainStep = 10;
    int cameraMid = 1;
    int cameraRadius = 1;
    int deadzone = 30; //radius for when analog stick is in the center

    //MODEL
    int strafe = motionMid;
    int fwdbwd = motionMid;
    int turn =  motionMid;
    int rsdv = motionMid;
    int buttonL2 = gripper2Mid;
    int buttonR2 = gripper2Mid;
    int gripper1 = gripper1Mid;
    int gripper2 = gripper2Mid;
    int light = 0;
    int gain = gainMid;
    int camera = cameraMid;

    //other variables used by QGamepadMonitor and QMainWindow
    bool motorSwitch=false; //if false, input for mechanical functions is disabled
    bool pendingShow = false;//hides cameraview, shows SECOND
    bool pendingHide = false;//hides SECOND, shows cameraview
    int dialog = 0;//toggle for dialog.ui
    bool hasGamepad = false;
    bool obsEnabled = false;// when true, replaces gripper rotation with obs

    void send(QString massage);

private Q_SLOTS:

Q_SIGNALS:
    void msg(QString);

private:
    int mapNumber(double x, double in_min, double in_max, double out_min, double out_max);
    int remap(int x);
    int format(double x);

    QString prefix = "";

};

#endif // GAMEPADMONITOR_H
