#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timecode.h"

#include "ui_mainwindow.h"
#include "timecode.h"
#include "opal_interface.h"
#include <memory>
#include <QTimer>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    timecode_frame * FRAME;
    std::mutex * issafe;
    std::atomic_bool * run;
    int sr=48000; //sample rate
    int buf=10; // number of buffers
    QTimer m_timer;
    std::atomic_bool * forword;


private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_reset_clicked();
    void update();
    void on_horizontalSlider_valueChanged();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
