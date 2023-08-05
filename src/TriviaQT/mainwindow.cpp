#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triviagame.h"

TriviaGame* game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette Palette(QColor(230, 230, 230));
    Palette.setColor(QPalette::Active, QPalette::Button, QColor(0, 0, 0, 50));
    Palette.setColor(QPalette::Active, QPalette::Shadow, QColor(Qt::black));
    qApp->setPalette(Palette);

    game = new TriviaGame(ui->label_Points,
                          ui->label_Skipped,
                          ui->label_Correct,
                          ui->pushButton_Verify,
                          ui->listWidget_Answers,
                          ui->textEdit_Question,
                          ui->groupBox_Genre);
    game->RefreshTrivia();
    game->UpdateStats();
}

void MainWindow::on_pushButton_Skip_clicked()
{
    game->SkipCurrentQuestion(false, 1);
}


void MainWindow::on_pushButton_Verify_clicked()
{
    game->Verify();
}


void MainWindow::on_pushButton_Reset_clicked()
{
    game->ResetStats();
    game->UpdateStats();
}


MainWindow::~MainWindow()
{
    delete ui;
}
