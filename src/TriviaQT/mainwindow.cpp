#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triviagame.h"
#include "triviaquestiongenre.h"
#include <QMetaEnum>
#include <QList>

TriviaGame* game;
QList<TriviaQuestionGenre> genres;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Load genres
    for(int i = (int)GenreEnums::QuestionGenre::Any; i < (int)GenreEnums::QuestionGenre::CartoonAndAnimations; i ++)
    {
        GenreEnums::QuestionGenre enumValue = GenreEnums::QuestionGenre(i);
        TriviaQuestionGenre genre = TriviaQuestionGenre(enumValue);
        genres.append(genre);
        ui->comboBox_Genre->addItem(genre.genreDisplayName);
    }

    QPalette Palette(QColor(230, 230, 230));
    Palette.setColor(QPalette::Active, QPalette::Button, QColor(0, 0, 0, 50));
    Palette.setColor(QPalette::Active, QPalette::Shadow, QColor(Qt::black));
    qApp->setPalette(Palette);

    game = new TriviaGame(ui->label_LastCorrect,
                          ui->label_Points,
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
}

void MainWindow::on_comboBox_Genre_currentIndexChanged(int index)
{
    //Update Genre
    if(game == nullptr) return; //Avoid access violation
    game->UppdateGenre(genres[index]);
}

MainWindow::~MainWindow()
{
    delete ui;
}




