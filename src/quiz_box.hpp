/**
 * @file quiz_box.hpp
 * @brief quiz画面のルートにあたるGtk::Boxの派生クラス
 */
#ifndef QUIZ_BOX_HPP
#define QUIZ_BOX_HPP

#include <gtkmm/box.h>
#include <gtkmm/button.h>

/**
 * @brief quiz画面のルートにあたるGtk::Boxの派生クラス
 */
class QuizBox : public Gtk::HBox
{
public:
    /**
     * @brief Construct a new Quiz Box object
     */
    QuizBox();

private:
    Gtk::Button home_button;

    bool onHomeButtonClicked();
};

#endif
