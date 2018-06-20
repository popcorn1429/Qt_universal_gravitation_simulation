#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QVector>

#include "sandbox.h"
#include "finger.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void animate();
protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_pushButton_init_clicked();

    void on_doubleSpinBox_strength_valueChanged(double arg1);

    void on_doubleSpinBox_ratio_valueChanged(double arg1);

    void on_checkBox_atract_toggled(bool checked);

    void on_checkBox_reject_toggled(bool checked);

private:
    void initializeFingers();

    void clearFingers();

private:
    Ui::Window *ui;

    Sandbox* sandbox;
    QVector<Finger> fingers;

    double defaultStrength;
};

#endif // WINDOW_H
