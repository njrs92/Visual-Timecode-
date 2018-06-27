#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    issafe = new std::mutex();
    run = new std::atomic_bool;
    *run = false;
    FRAME = new timecode_frame;

    ui->setupUi(this);
    QTimer *m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(100);
    forword = new std::atomic_bool;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete issafe;
    delete FRAME;
    *run = false;
    delete forword;
}



void MainWindow::on_pushButton_start_clicked()
{
    if (!*run){
    int hour = ui->spinBox_H->value();
    int min = ui->spinBox_M->value();
    int sec = ui->spinBox_S->value();
    int frame = ui->spinBox_F->value();

    issafe->lock();
    FRAME->set_hours(hour);
    FRAME->set_minutes(min);
    FRAME->set_seconds(sec);
    FRAME->set_frameNumber(frame);
    issafe->unlock();
    std::thread opalthread(opal_interface,FRAME, sr, buf,run,issafe,forword);
    opalthread.detach();

    *run = true;
    }
}

void MainWindow::on_pushButton_stop_clicked()
{
    issafe->lock();
    ui->spinBox_F->setValue(FRAME->return_frameNum());
    ui->spinBox_M->setValue(FRAME->return_min());
    ui->spinBox_S->setValue(FRAME->return_sec());
    ui->spinBox_H->setValue(FRAME->return_hour());
    *run = false;
    issafe->unlock();
}
void MainWindow::on_pushButton_reset_clicked()
{
    ui->spinBox_F->setValue(0);
    ui->spinBox_M->setValue(0);
    ui->spinBox_S->setValue(0);
    ui->spinBox_H->setValue(0);

    issafe->lock();
    FRAME->set_hours(0);
    FRAME->set_minutes(0);
    FRAME->set_seconds(0);
    FRAME->set_frameNumber(0);
    issafe->unlock();

}


void MainWindow::update(){
    issafe->lock();
    ui->lcdNumber_f->display((FRAME->return_frameNum()));
    ui->lcdNumber_m->display((FRAME->return_min()));
    ui->lcdNumber_s->display((FRAME->return_sec()));
    ui->lcdNumber_h->display((FRAME->return_hour()));
    issafe->unlock();
}


void MainWindow::on_horizontalSlider_valueChanged()
{
    issafe->lock();
    bool temp = ui->horizontalSlider->value();
    *forword = temp;
    issafe->unlock();
}
