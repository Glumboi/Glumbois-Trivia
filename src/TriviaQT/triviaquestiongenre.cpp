#include "triviaquestiongenre.h"
#include "qmetaobject.h"

TriviaQuestionGenre::TriviaQuestionGenre(GenreEnums::QuestionGenre& genre)
{
    genreDisplayName = GenreEnums::GetQuestionGenreString(genre);

    if(genre == GenreEnums::QuestionGenre::Any) { apiUrlExpansion = ""; return; };

    apiUrlExpansion = "&category=" + QString::number((int)genre);
}
