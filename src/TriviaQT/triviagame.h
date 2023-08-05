#ifndef TRIVIAGAME_H
#define TRIVIAGAME_H
#include <QString>
#include <vector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QRandomGenerator>
#include <iostream>
#include <QTextDocument>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QGroupBox>

class TriviaGame
{
public:
    TriviaGame(QLabel* _pointText,
               QLabel* _skippedText,
               QLabel* _correctText,
               QPushButton* _verifyBtn,
               QListWidget* _answerList,
               QTextEdit* _questionEdit,
               QGroupBox* _genreBox);

    void Load();
    void ResetStats();
    void UpdateStats();
    void SkipCurrentQuestion(bool hasAnsweredCorrectly, uint8_t punishmentAmount);
    void RefreshTrivia();
    void Verify();

    QString question;
    QString category;
    QString difficulty;
    QString correctAnswer;

    QLabel* pointText;
    QLabel* skippedText;
    QLabel* correctText;

    QListWidget* answerList;
    QPushButton* verifyBtn;
    QTextEdit* questionEdit;
    QGroupBox* genreBox;

    std::vector<QString> answers;

    int skippedQuestions = 0;
    int correctAnswers = 0;
    int points = 0;
    int currentTries = 0;

private:
    QString DecodeHtmlEntities(const QString &input);
    QString triviaJsonUrl = "https://opentdb.com/api.php?amount=1";
    bool isBusy = false;

};

#endif // TRIVIAGAME_H
