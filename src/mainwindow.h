#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0, bool use_cmem = 0);
    ~MainWindow();
    
private slots:
    void on_capture_clicked();

    void on_switch_2_clicked();

    void on_pip_clicked();
    void on_pip_2_clicked();
    void on_pip_3_clicked();
    void on_pip_4_clicked();

    void on_exit_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
