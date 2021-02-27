#ifndef CREATE_IMAGE_INFO_H
#define CREATE_IMAGE_INFO_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QFile>

namespace Ui {
class Create_Image_Info;
}

class Create_Image_Info : public QDialog
{
    Q_OBJECT

public:
    explicit Create_Image_Info(QWidget *parent = nullptr);
    ~Create_Image_Info();

public slots:
    void set_info(QString name, QString format, int total, int start = 0);

    void updateInfo();

    void close_create_image_info();

private slots:
    void updateTime();

    void closeEvent(QCloseEvent*);

signals:
    void timeOut();

private:
    Ui::Create_Image_Info *ui;

    QTimer* timer;

    QTime time_now = QTime::fromString("0", "s");

    QTime time_left = QTime::fromString("1", "h");

    QTime time_one = QTime::fromString("0", "s");

    QString name, format;

    int total;

    int index;

    int start;
};

#endif // CREATE_IMAGE_INFO_H
