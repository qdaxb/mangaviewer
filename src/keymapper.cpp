#include "keymapper.h"
#include <QSettings>
#include <QDebug>
#include <QApplication>
KeyMapper::KeyMapper()
{
    QSettings setting(QApplication::applicationDirPath ()+"/settings.ini",QSettings::IniFormat);
    setting.beginGroup("keys");
    qDebug()<<setting.value("test");
}
