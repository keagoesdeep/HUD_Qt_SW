#include "gamepadmonitor.h"

GamepadMonitor::GamepadMonitor(QObject *parent)://all the binds
    QObject(parent),
    m_gamepad(0)
{
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty()) {
        return;
    }
    m_gamepad = new QGamepad(*gamepads.begin(), this);
    hasGamepad = true;

    connect(m_gamepad, &QGamepad::axisLeftXChanged, this, [&](double value){//turn
        if(turn != remap(format(value))){
            turn = remap(format(value));
            if(motorSwitch) send("TURN=" + QString::number(turn));
        }
    });
    connect(m_gamepad, &QGamepad::axisLeftYChanged, this, [&](double value){//rsdv
        if(rsdv != remap(format(value))){
            rsdv = remap(format(value));
            if(motorSwitch) send("FWBW=" + QString::number(rsdv));
        }
    });
    connect(m_gamepad, &QGamepad::axisRightXChanged, this, [&](double value){//strafe
        if(strafe != remap(format(value))){
            strafe = remap(format(value));
            if(motorSwitch) send("STRF=" + QString::number(strafe));
        }
    });
    connect(m_gamepad, &QGamepad::axisRightYChanged, this, [&](double value){//fwdbwd
        if(fwdbwd != remap(format(value))){
            fwdbwd = remap(format(value));
            //from float 0-1 to int 1-255 adding deadzone, pulling both ends of the deadzone together
            if(motorSwitch) send("RSDV=" + QString::number(fwdbwd));
        }
    });
    connect(m_gamepad, &QGamepad::buttonR1Changed, this, [&](bool pressed){//gripper1= 2
        if (pressed) gripper1 += gripper1Radius; else gripper1 -= gripper1Radius;
        if(motorSwitch) send("GP=" + QString::number(gripper1));
    });
    connect(m_gamepad, &QGamepad::buttonL1Changed, this, [&](bool pressed){//gripper1= 0
        if (pressed) gripper1 -= gripper1Radius; else gripper1 += gripper1Radius;
        if(motorSwitch) send("GP=" + QString::number(gripper1));
    });
    connect(m_gamepad, &QGamepad::buttonL2Changed, this, [&](double value){//gripper2+this
        buttonL2 = round(value * gripper2Mid) + gripper2Radius;
        if (gripper2 != gripper2Mid + buttonR2 - buttonL2){
            gripper2 = gripper2Mid + buttonR2 - buttonL2;
            if(motorSwitch) {
                if (!obsEnabled)
                    send("GR=" + QString::number(gripper2));
                else
                    send("OR=" + QString::number(gripper2));
            }
        }
    });
    connect(m_gamepad, &QGamepad::buttonR2Changed, this, [&](double value){//gripper2-this
        buttonR2 = round(value * gripper2Mid) + gripper2Radius;
        if (gripper2 != gripper2Mid + buttonR2 - buttonL2){
            gripper2 = gripper2Mid + buttonR2 - buttonL2;
            if(motorSwitch) {
                if (!obsEnabled)
                    send("GR=" + QString::number(gripper2));
                else
                    send("OR=" + QString::number(gripper2));
            }
        }
    });
    connect(m_gamepad, &QGamepad::buttonAChanged, this, [&](bool pressed){//cameraPos= 2
        if (pressed) camera -= cameraRadius; else camera += cameraRadius;
        send("CAMV=" + QString::number(camera));
    });
    connect(m_gamepad, &QGamepad::buttonYChanged, this, [&](bool pressed){//cameraPos= 0
        if (pressed) camera += cameraRadius; else camera -= cameraRadius;
        send("CAMV=" + QString::number(camera));
    });
    connect(m_gamepad, &QGamepad::buttonBChanged, this, [&](bool pressed){
        if(pressed){
            obsEnabled = !obsEnabled;
            if(obsEnabled)
                send("GR=" + QString::number(gripper2Mid));
            else
                send("OR=" + QString::number(gripper2Mid));
        }
    });
    connect(m_gamepad, &QGamepad::buttonXChanged, this, [&](bool pressed){
    //NOTHING
    });
    connect(m_gamepad, &QGamepad::buttonRightChanged, this, [&](bool pressed){//lights ON
        if(pressed){
            light = 1;
            send("LITE=" + QString::number(light));
        }
    });
    connect(m_gamepad, &QGamepad::buttonLeftChanged, this, [&](bool pressed){//lights OFF
        if(pressed){
            light = 0;
            send("LITE=" + QString::number(light));
        }
    });
    connect(m_gamepad, &QGamepad::buttonUpChanged, this, [&](bool pressed){//gain -10%
        if (pressed)
        {
            gain -= gainStep;
            if (gain < gainMid - gainRadius) gain = gainMid - gainRadius;
            send("GAIN=" + QString::number(gain));
        }
    });
    connect(m_gamepad, &QGamepad::buttonDownChanged, this, [&](bool pressed){//gain +10%
        if (pressed)
        {
            gain += gainStep;
            if (gain > gainMid + gainRadius) gain = gainMid + gainRadius;
            send("GAIN=" + QString::number(gain));
        }
    });
    connect(m_gamepad, &QGamepad::buttonGuideChanged, this, [&](bool pressed){//motors ignition
        if (pressed) motorSwitch = !motorSwitch; // only for GUI
    });
    connect(m_gamepad, &QGamepad::buttonSelectChanged, this, [&](bool pressed){
        if(pressed) {if(dialog==0) dialog = 1; else dialog = 3;} // only for GUI
    });
    connect(m_gamepad, &QGamepad::buttonStartChanged, this, [&](bool pressed){
        if (pressed) pendingShow = true; else pendingHide = true; // only for GUI
    });

}// ----------------------------------------END OF CONNECTS-----------------------------------------------

void GamepadMonitor::send(QString massage){
    if(server.hasClient){ // if connected to a client, send over TCP
//        Q_EMIT msg(massage);
        while (massage.length()<16){
            massage.append("_");
        }
        QByteArray datagram = massage.toStdString().c_str();
        server.socket->write(datagram);
        server.socket->flush();
    }
}

//used by remap(int x), taken from internet
int GamepadMonitor::mapNumber(double x, double in_min, double in_max, double out_min, double out_max)
{
    return round( (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min );
}

//closes the gap caused by removing the deadzone
int GamepadMonitor::remap(int x)
{
    if (x < motionMid)
    x = mapNumber(x, motionMid - motionRadius, motionMid-deadzone, motionMid - motionRadius, motionMid);
    else if (x > motionMid)
    x = mapNumber(x, motionMid + deadzone, motionMid + motionRadius, motionMid, motionMid + motionRadius);
    return x;
}

//removes the deadzone
int GamepadMonitor::format(double x)
{
    x = mapNumber(x, -1, 1, motionMid-motionRadius, motionMid+motionRadius);
    if (x < motionMid + deadzone && x > motionMid - deadzone) x = motionMid;
    return x;
}

//ondestroy
GamepadMonitor::~GamepadMonitor()
{
    delete m_gamepad;
}
