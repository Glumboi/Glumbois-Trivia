#ifndef GENREENUMS_H
#define GENREENUMS_H

#include <QString>
#include <QObject>
#include <QVariant>


class GenreEnums : public QObject
{
    Q_OBJECT
public:
    enum QuestionGenre{
        Any = 8,
        GeneralKnowledge,
        Books,
        Film,
        Music,
        MusicalsAndTheaters,
        Television,
        VideoGames,
        BoardGames,
        ScienceAndNature,
        Computers,
        Maths,
        Mythology,
        Sports,
        Geography,
        History,
        Politics,
        Art,
        Celebreties,
        Animals,
        Vehicles,
        Comics,
        Gadgets,
        AnimeAndManga,
        CartoonAndAnimations
    };
    Q_ENUM(QuestionGenre)

    static QuestionGenre GetQuestionGenre(const QString &text);
    static QString GetQuestionGenreString(const QuestionGenre &enumValue);
};

#endif // GENREENUMS_H
