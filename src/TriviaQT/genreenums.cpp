#include "genreenums.h"

GenreEnums::QuestionGenre GenreEnums::GetQuestionGenre(const QString &text)
{
    return QVariant(text).value<QuestionGenre>();
}

QString GenreEnums::GetQuestionGenreString(const GenreEnums::QuestionGenre &enumValue)
{
    return QVariant::fromValue(enumValue).toString();
}
