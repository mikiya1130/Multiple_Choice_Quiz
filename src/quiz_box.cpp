#include "quiz_box.hpp"

QuizBox::QuizBox() : home_button("home")
{
    pack_start(home_button);
    home_button.signal_clicked().connect(
        [this]
        { onHomeButtonClicked(); });
}

bool QuizBox::onHomeButtonClicked()
{
    return false;
}
