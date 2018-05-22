#include "mainwindow.h"
#include "ui_mainwindow.h"


QString pipeDescr0 = "v4l2src ! xvimagesink";
//QString pipeDescr1 = "udpsrc port=5000 ! application/x-rtp, payload=96 ! rtph264depay ! queue ! avdec_h264 ! videoconvert ! ximagesink";
QString pipeDescr1 = "udpsrc port=5000 caps=\'application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264\' ! rtph264depay ! avdec_h264 ! videoconvert ! ximagesink";
QString pipeDescr2 = "udpsrc port=5001 ! application/x-rtp,enconding-name=H264,payload=96 ! queue ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! ximagesink";
QString pipeDescr3 = "udpsrc port=5002 ! application/x-rtp,enconding-name=H264,payload=96 ! queue ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! ximagesink";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    second = new Second(this);//second
    dialog = new Dialog(this);//dialog

    sliders = new Sliders(this);//sliders
    connect(sliders , SIGNAL(zmena(QString)), this, SLOT(zmenaReceived(QString)));

    monitor = new GamepadMonitor(this);
    connect(monitor, SIGNAL(msg(QString)), this, SLOT(msgReceived(QString)));
    connect(&monitor->server, SIGNAL(msg(QString)), this, SLOT(msgReceived(QString)));
    monitor->server.startServer();

    //setWindowFlags(Qt::WindowStaysOnTopHint); //makes the window always on top

    if (servo.start())
    {
        serialIsOpen = true;
        ui->console->append("serial detected");
    }
    else
    {
        ui->console->append("no serial detected");
    }

    player0 = new Player;
    player0->setPipelineDescription(pipeDescr0);
    player0->createPipeline();
    player0->play();
    ui->videoLayout->addWidget(player0, 0, 0);
    ui->videoLayout->addWidget(second, 0, 0);
    second->hide();
    ui->videoLayout->addWidget(dialog, 0, 0);
    dialog->hide();
    ui->videoLayout->addWidget(sliders, 1, 1);

    player1 = new Player;
    player1->setPipelineDescription(pipeDescr1);
//    player1->createPipeline();
    player1->play();
    ui->videoLayout->addWidget(player1, 0, 1);

    player2 = new Player;
    player2->setPipelineDescription(pipeDescr2);
//    player2->createPipeline();
    player2->play();
    ui->videoLayout->addWidget(player2, 1, 0);

    player3 = new Player;
    player3->setPipelineDescription(pipeDescr3);
    //player3->createPipeline();
    player3->play();
    ui->videoLayout->addWidget(player3, 1, 1);
    player3->hide();

    if (!monitor->hasGamepad) ui->console->append("no gamepad detected");

    timerId = startTimer(freq);
}

void MainWindow::timerEvent(QTimerEvent *event) //update labels and send data every (freq) ms
{
    tcpTimer++;
    if (tcpTimer > 1000 / freq){
        //sendDataTcp();
        tcpTimer = 0;
    }
    updateLabels();

    dialog->changeLine(monitor->turn, monitor->rsdv); // rotates the line in GUI

    // second hold
    if (monitor->pendingShow)
    {
        monitor->pendingShow = false;
        player0->hide();
        second->show();
    }
    if (monitor->pendingHide)
    {
        monitor->pendingHide= false;
        second->hide();
        player0->show();
    }

    //dialog toggle
    if (monitor->dialog == 1)
    {
        monitor->dialog = 2;
        player0->hide();
        dialog->show();
    }
    if (monitor->dialog == 3)
    {
        monitor->dialog = 0;
        dialog->hide();
        player0->show();
    }
}

void MainWindow::sendDataTcp(){
    if (!monitor->motorSwitch) //if the ROV is not primed, assign default values
        {
        monitor->gripper1 = 1; // 0-2
        monitor->gripper2 = 4; // 0-8
        monitor->fwdbwd = 128; // 0-256
        monitor->strafe = 128; // 0-256
        monitor->rsdv = 128; // %-256
        monitor->turn = 128; // 0-256
        }
    QString commandTcp[9] = {
        "FWBW=" + QString::number(monitor->fwdbwd),
        "STRF=" + QString::number(monitor->strafe),
        "RSDV=" + QString::number(monitor->rsdv),
        "TURN=" + QString::number(monitor->turn),
        "GAIN=" + QString::number(monitor->gain),
        "LITE=" + QString::number(monitor->light),
        "CAMV=" + QString::number(monitor->camera),
        "GP=" + QString::number(monitor->gripper1),
        "GR=" + QString::number(monitor->gripper2)
    };

    if(monitor->obsEnabled)
        commandTcp[8] = "OR=" + QString::number(monitor->gripper2);

    for (int i = 0; i<9; i++) {
        monitor->send(commandTcp[i]);
    }
}

//used by QTimer
void MainWindow::updateLabels()
{
    ui->label_fwdbwd->setText("FWBW: "+QString::number(monitor->fwdbwd));
    ui->label_strafe->setText("STRF: "+QString::number(monitor->strafe));
    ui->label_rsdv->setText("RSDV: "+QString::number(monitor->rsdv));
    ui->label_turn->setText("TURN: "+QString::number(monitor->turn));
    ui->label_gain->setText("GAIN: "+QString::number(monitor->gain)+"%");
    QString lajt;
    if (monitor->light > 0)lajt="ON"; else lajt="OFF";
    ui->label_light->setText("LITE: "+lajt);
    ui->label_camera->setText("CAMV: "+QString::number(monitor->camera));
    ui->label_gripper1->setText("GP: "+QString::number(monitor->gripper1));
    if (!monitor->obsEnabled)
        ui->label_gripper2->setText("GR: "+QString::number(monitor->gripper2));
    else
        ui->label_gripper2->setText("OR: "+QString::number(monitor->gripper2));

    ui->label_fwdbwd->setVisible(monitor->motorSwitch);
    ui->label_turn->setVisible(monitor->motorSwitch);
    ui->label_rsdv->setVisible(monitor->motorSwitch);
    ui->label_strafe->setVisible(monitor->motorSwitch);
    ui->label_gripper1->setVisible(monitor->motorSwitch);
    ui->label_gripper2->setVisible(monitor->motorSwitch);

    QString motorHead;
    if (monitor->motorSwitch)
    {
        motorHead="ON";//this->activateWindow();
    }
        else
        {motorHead="OFF";}
    ui->label_motors->setText("motors: "+motorHead);
}

void MainWindow::msgReceived(QString message){
    ui->console->append(message);
}
void MainWindow::zmenaReceived(QString message){
    monitor->send(message);
}

//ondestroy
MainWindow::~MainWindow()
{
    monitor->send("STOP");
    delete ui;
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked)
        monitor->send("LR=0");
    else
        monitor->send("LR=1");
}

void MainWindow::on_ob0_clicked()
{
    monitor->send("OB=0");
}
void MainWindow::on_ob1_clicked()
{
    monitor->send("OB=1");
}
void MainWindow::on_ob2_clicked()
{
    monitor->send("OB=2");
}
