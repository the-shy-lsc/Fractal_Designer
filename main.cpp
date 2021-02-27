//#include <QTextCodec>
#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QSettings>

void defaultOpen(QString appPath, QString className, QString ext, QString extDes)
{
    QString baseUrl("HKEY_CURRENT_USER\\Software\\Classes");
    QSettings settingClasses(baseUrl, QSettings::NativeFormat);
    settingClasses.setValue("/" + className + "/Shell/Open/Command/.", "\"" + appPath + "\" \"%1\"");
    settingClasses.setValue("/" + className + "/.", extDes);
    settingClasses.setValue("/" + className + "/DefaultIcon/.", appPath + ",0");
    settingClasses.setValue("/" + ext + "/OpenWithProgIds/" + className, "");
    settingClasses.sync();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings lastopen(QCoreApplication::applicationDirPath() + "LastOpen.ini", QSettings::IniFormat);
    QString Last_Open_Time = lastopen.value("LASTOPEN/Time", "").toString();

    if(Last_Open_Time.isEmpty())
    {
        QString appPath(QString(argv[0]).toStdString().c_str());
        QString className("FRD");
        QString ext(".frd");
        QString extDes("Fractal Designer File");
        defaultOpen(appPath, className, ext, extDes);
        qDebug() << "Default setting";
    }

    QSettings setting(QCoreApplication::applicationDirPath() + "LastOpen.ini", QSettings::IniFormat);
    setting.beginGroup("LASTOPEN");
    setting.setValue("Time", QTime::currentTime());
    setting.endGroup();

    MainWindow w;
    w.setOpenLocation(argc > 1 ? argv[1] : "");
    w.show();
    return a.exec();
}
