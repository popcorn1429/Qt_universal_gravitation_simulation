#include "window.h"
#include "ui_window.h"
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

const unsigned MAX_FINGERS_SUPPORTED = 5;

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    //resize(450,600);

    qDebug("widget:[%d, %d, %d, %d].\n", ui->widget->x(), ui->widget->width(), ui->widget->y(), ui->widget->height());
    sandbox = new Sandbox(ui->widget->x(), ui->widget->width(), ui->widget->y(), ui->widget->height(),
                          ui->doubleSpinBox_ratio->value(), ui->checkBox_atract->isChecked(),
                          ui->checkBox_reject->isChecked());

    defaultStrength = 5.0;
    initializeFingers();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Window::animate);
    timer->start(50);
}

Window::~Window()
{
    delete ui;
}

void Window::animate()
{
    sandbox->updateNodes(fingers, qobject_cast<QTimer*>(sender())->interval());
    update();
}

void Window::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    sandbox->paint(&painter);
    painter.end();
}

void Window::mousePressEvent(QMouseEvent *event)
{
    if ( event->x() > ui->widget->x() && event->x() < ui->widget->x() + ui->widget->width()
         && event->y() > ui->widget->y() && event->y() < ui->widget->y() + ui->widget->height()) {
        clearFingers();
        fingers[0].setStrength(defaultStrength);
        fingers[0].setPosX(event->x());
        fingers[0].setPosY(event->y());
        fingers[0].press();
    }
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        fingers[0].setPosX(event->x());
        fingers[0].setPosY(event->y());
    }
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    clearFingers();
}

void Window::on_pushButton_init_clicked()
{
    sandbox->initialize(ui->spinBox_row_num->value(), ui->spinBox_col_num->value());
}

void Window::initializeFingers()
{
    for (int i = 0; i < MAX_FINGERS_SUPPORTED; ++i) {
        fingers.push_back(Finger());
    }
}

void Window::clearFingers()
{
    for (int i = 0; i < MAX_FINGERS_SUPPORTED; ++i) {
        fingers[i].release();
    }
}

void Window::on_doubleSpinBox_strength_valueChanged(double arg1)
{
    defaultStrength = ui->doubleSpinBox_strength->value();
}

void Window::on_doubleSpinBox_ratio_valueChanged(double arg1)
{
    sandbox->setRatio(ui->doubleSpinBox_ratio->value());
}


void Window::on_checkBox_atract_toggled(bool checked)
{
    sandbox->setAttract(checked);
}

void Window::on_checkBox_reject_toggled(bool checked)
{
    sandbox->setReject(checked);
}
