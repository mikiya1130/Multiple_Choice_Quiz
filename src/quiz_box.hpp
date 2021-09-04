/**
 * @file quiz_box.hpp
 * @brief quiz画面のルートにあたるGtk::Boxの派生クラス
 */
#ifndef QUIZ_BOX_HPP
#define QUIZ_BOX_HPP

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/separator.h>
#include <gtkmm/paned.h>
#include <gtkmm/notebook.h>

/**
 * @brief quiz画面のルートにあたるGtk::Boxの派生クラス
 */
class QuizBox : public Gtk::VBox
{
public:
    /**
     * @brief Construct a new Quiz Box object
     */
    QuizBox();

private:
    static const int PADDING = 15;
    Gtk::Box header_box;
    Gtk::Label question_number_label;
    Gtk::Label statistics_label;
    Gtk::Separator vertical_separator;
    Gtk::Paned horizontal_paned;
    Gtk::Notebook qa_notebook;
    Gtk::Box question_box;
    Gtk::Box explanation_box;
    Gtk::Box right_side_box;
    Gtk::Box controll_box;
    Gtk::Button previous_button;
    Gtk::Button home_button;
    Gtk::Button next_button;
    Gtk::Separator vertical_right_side_box_separator;
    Gtk::Label choice_label;
    Gtk::Box choice_button_box;
    std::vector<Gtk::Button> choice_button_vector;

    bool onHomeButtonClicked();
};

#endif
