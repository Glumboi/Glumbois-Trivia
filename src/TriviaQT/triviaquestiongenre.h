#ifndef TRIVIAQUESTIONGENRE_H
#define TRIVIAQUESTIONGENRE_H
#include <QString>
#include "genreenums.h"

class TriviaQuestionGenre
{
public:
    QString genreDisplayName;
    QString apiUrlExpansion;
    TriviaQuestionGenre(GenreEnums::QuestionGenre& genre);
};

#endif // TRIVIAQUESTIONGENRE_H
