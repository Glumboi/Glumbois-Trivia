#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void RefreshTrivia();
    ~MainWindow();

private slots:
    void on_pushButton_Skip_clicked();

    void on_pushButton_Verify_clicked();

    void on_pushButton_Reset_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
