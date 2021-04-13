#ifndef CREATE_IMAGE_TASK_H
#define CREATE_IMAGE_TASK_H
#include <QRunnable>
#include <QWidget>
#include <QObject>
#include <QImage>
#include "Complex.h"

#ifndef Create_Images_Task_Pre
#define Create_Images_Task_Pre(task__)       \
if(Version_Higher_Than_4)                    \
{                                            \
    task__->setVersion(true);                \
    task__->setData(curr_info.Colour_Data_1, \
                    curr_info.Colour_Data_2, \
                    curr_info.template_,     \
                    curr_info.min_class_v,   \
                    curr_info.max_class_v,   \
                    curr_info.max_loop_t);   \
}                                            \
else                                         \
{                                            \
    task__->setPath(Project_Name);           \
}
#endif

class Create_Image_Task : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Create_Image_Task(QWidget*);

    void run();

private:

    QString pro_path;

    bool Version_Higher_Than_4 = false;

    double Colour_Data_1[4][29][2], Colour_Data_2[4][29][2];
    double Colour_Data[2][4][29][2] = {0};

    int template_, max_loop_t;

    // Template 2
    Complex c0;

    // Template 4
    Complex Newton_a = 1;
    Complex Newton_xn[10] {0};
    Complex Newton_sin = 0;
    Complex Newton_cos = 0;
    Complex Newton_ex = 0;

    double min_class_v, max_class_v;

    double x, y, x_width, y_height, rotate_angle, t;
    int X, Y;
    QString img_format, img_path, img_title, work_name;

    bool isCancelled = false;

signals:
    void updateImage_preview(QImage);

    void progressInform_preview(double);

    void updateImage_route(QImage);

    void progressInform_route(double);

    void image_build_finished();

    void finished();

    void one_ok();

public: // function
    void setImage(double, double, double, double, int, int, double, double, QString, QString, QString, QString);

    void setPath(QString);

    void setData(double[4][29][2], double[4][29][2], int, double, double, int);

    void setVersion(bool);

    void setTemplate2(const Complex& c);

    void setTemplate4(const Complex& c1, Complex* c2, const Complex& c3, const Complex& c4, const Complex& c5);

public slots:

    void stop();

};

#endif // CREATE_IMAGE_TASK_H
