#include "triviagame.h"

TriviaGame::TriviaGame(QLabel* _lastCorrectText,
                       QLabel* _pointText,
                       QLabel* _skippedText,
                       QLabel* _correctText,
                       QPushButton* _verifyBtn,
                       QListWidget* _answerList,
                       QTextEdit* _questionEdit,
                       QGroupBox* _genreBox)
{
    lastCorrectText = _lastCorrectText;
    pointText = _pointText;
    skippedText = _skippedText;
    correctText = _correctText;
    verifyBtn = _verifyBtn;
    answerList = _answerList;
    questionEdit = _questionEdit;
    genreBox = _genreBox;
}

void TriviaGame::Load()
{
    answers.clear();

    if (isBusy)
        return;

    isBusy = true;

    QNetworkAccessManager networkManager;
    QUrl url(triviaJsonUrl);
    QNetworkReply *reply = networkManager.get(QNetworkRequest(url));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    reply->deleteLater();

    QString webpageContent = QString::fromUtf8(data);

    QJsonDocument jsonDocument = QJsonDocument::fromJson(webpageContent.toUtf8());
    if (jsonDocument.isNull() || !jsonDocument.isObject()) {
        qDebug() << "Failed to parse JSON.";
        return;
    }

    QJsonObject jsonObject = jsonDocument.object();

    QJsonValue responseCodeValue = jsonObject.value("response_code");
    if (responseCodeValue.isDouble()) {
        int responseCode = responseCodeValue.toInt();
        qDebug() << "Response Code: " << responseCode;
    }

    QJsonValue resultsValue = jsonObject.value("results");
    if (resultsValue.isArray()) {
        QJsonArray resultsArray = resultsValue.toArray();
        for (const QJsonValue &resultValue : resultsArray) {
            if (resultValue.isObject()) {
                QJsonObject resultObject = resultValue.toObject();

                category = DecodeHtmlEntities(resultObject.value("category").toString());
                difficulty = DecodeHtmlEntities(resultObject.value("difficulty").toString());
                question = DecodeHtmlEntities(resultObject.value("question").toString());
                correctAnswer = DecodeHtmlEntities(resultObject.value("correct_answer").toString());

                answers.push_back(correctAnswer);

                qDebug() << "Category: " << category;
                qDebug() << "Difficulty: " << difficulty;
                qDebug() << "Question: " << question;
                qDebug() << "Correct Answer: " << correctAnswer;

                QJsonValue incorrectAnswersValue = resultObject.value("incorrect_answers");
                if (incorrectAnswersValue.isArray()) {
                    QJsonArray incorrectAnswersArray = incorrectAnswersValue.toArray();
                    qDebug() << "Incorrect Answers:";
                    for (const QJsonValue &incorrectAnswerValue : incorrectAnswersArray) {
                        if (incorrectAnswerValue.isString()) {
                            QString val = DecodeHtmlEntities(incorrectAnswerValue.toString());
                            qDebug() << "   " << val;
                            answers.push_back(val);
                        }
                    }
                }

                qDebug() << "-----------------------------------";
            }
        }
    }

    currentTries = answers.size() / 2;
    isBusy = false;
}

QString TriviaGame::DecodeHtmlEntities(const QString &input)
{
    QTextDocument textDocument;
    textDocument.setHtml(input);
    return textDocument.toPlainText().trimmed(); // Trim potential whitespace
}

void TriviaGame::ResetStats()
{
    points = 0;
    correctAnswers = 0;
    skippedQuestions = 0;
    lastCorrect = "";

    UpdateStats();
}

void TriviaGame::UpdateStats()
{
    lastCorrectText->setText(lastCorrect);
    pointText->setText(QString::number(points));
    skippedText->setText(QString::number(skippedQuestions));
    correctText->setText(QString::number(correctAnswers));
    verifyBtn->setText("Verify Answer (" + QString::number(currentTries) + ")");
}

void TriviaGame::SkipCurrentQuestion(bool hasAnsweredCorrectly = false, uint8_t punishmentAmount = 1)
{
    if(hasAnsweredCorrectly)
    {
        points += answerList->count();
        correctAnswers++;
    }
    else
    {
        skippedQuestions++;
        points -= points > 0 ? punishmentAmount : 0;
    }

    lastCorrect = correctAnswer;
    RefreshTrivia();
    UpdateStats();
}

void TriviaGame::RefreshTrivia()
{
    Load();

    genreBox->setTitle(category + " (" + difficulty + ")");
    questionEdit->setText(question);
    answerList->clear();

    QRandomGenerator *generator = QRandomGenerator::global();

    // Shuffle the vector by randomly swapping elements
    for (int i = answers.size() - 1; i > 0; --i) {
        int j = generator->bounded(i + 1); // Random index between 0 and i
        if (i != j) {
            // Swap elements at indexes i and j
            QString temp = answers[i];
            answers[i] = answers[j];
            answers[j] = temp;
        }
    }

    for(int i = 0; i < answers.size(); i ++)
    {
        answerList->addItem(answers[i]);
    }
}

void TriviaGame::Verify()
{
    if(answerList->selectedItems().count() == 0){ return; }

    if(answerList->selectedItems()[0]->text() == correctAnswer)
    {
        qDebug() << "corrrect!";
        SkipCurrentQuestion(true, 0);
        return;
    }

    currentTries --;

    if(currentTries == 0)
    {
        SkipCurrentQuestion(false, 2);
    }

    UpdateStats();
}

void TriviaGame::UppdateGenre(TriviaQuestionGenre& newGenre)
{
    triviaJsonUrl = "https://opentdb.com/api.php?amount=1" + newGenre.apiUrlExpansion;
    RefreshTrivia();
}

TriviaGame::~TriviaGame()
{
    delete lastCorrectText;
    delete pointText;
    delete skippedText;
    delete correctText;
    delete answerList;
    delete verifyBtn;
    delete questionEdit;
    delete genreBox;
}

