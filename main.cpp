/*
    Copyright (C) 2010  Marco Ballesio <gibrovacco@gmail.com>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <QtCore/QCoreApplication>  //simple
#include "mediaapp.h"               //player
#include "gamepadmonitor.h"         //simple
#include <QApplication>             //simple
#include <QGst/Init>                //player
#include <stdint.h>                 //simple
#include <mainwindow.h>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QGst::init(&argc, &argv);

    MainWindow w;
    w.showMaximized();

    return app.exec();
}
