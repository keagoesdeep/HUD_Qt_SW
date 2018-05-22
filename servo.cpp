#include "servo.h"

static QSerialPort serial;

QString Servo::getSerialport(uint16_t index)
{
    QList<QSerialPortInfo> listPorts = QSerialPortInfo::availablePorts();
    for(int i = 0; i < listPorts.size(); i++)
    {
        if(index == i)
        {
            return listPorts.at(i).systemLocation();
        }
    }
}

QString Servo::Serial_read()//UNUSED (keep for reading strings)
{
    QByteArray Data = serial.readAll();
    while (serial.waitForReadyRead(0))
    Data.append(serial.readAll());
    return QString(Data);
}

void Servo::Serial_begin(QString port, uint32_t baud)//called by the start() method
{
    serial.setPortName(port);
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(baud);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setReadBufferSize(10000);
}

void Servo::Serial_writeString(std::string output)//UNUSED (keep for writing strings)
{
    serial.write(output.c_str(), output.length());
    serial.flush();

    fprintf(stdout, output.c_str());
    fflush(stdout);
}

void Servo::Serial_writeByte(QByteArray output)//called as the final command of sendData()
{
    serial.write(output);
    serial.flush();

    fprintf(stdout, output);
    fflush(stdout);
}

bool Servo::start()//called at the start of the program
{
    if ((uint16_t)QSerialPortInfo::availablePorts().size()>0)
    {
        Serial_begin(getSerialport(1),115200);
        return true;
    }
    return false;
}

void Servo::CloseSerialPort()//called on MainWindow destroy
{
    serial.close();
}
