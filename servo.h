#ifndef SERVO_H
#define SERVO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>

class Servo
{
    public:

        void Serial_begin(QString port, uint32_t baud);//
        void Serial_writeString(std::string output);//
        void Serial_writeByte(QByteArray output);//
        void CloseSerialPort();//
        QString getSerialport(uint16_t index);//
        QString Serial_read();//
        bool start();//

    private:
};

#endif // servo_h
