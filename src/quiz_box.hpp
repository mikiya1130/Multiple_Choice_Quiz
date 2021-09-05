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

    /**
     * @brief HomeButtonのクリックシグナルを扱う
     */
    typedef sigc::signal<void> typeSignalHomeButtonClicked;

    /**
     * @brief signal accessor
     *
     * @return typeSignalHomeButtonClicked
     */
    typeSignalHomeButtonClicked signalHomeButtonClicked();

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
    typeSignalHomeButtonClicked signal_home_button_clicked;

    /**
     * @brief qa_notebookのquestion_boxとexplanation_boxを切り替える
     *
     * @param page // TODO write
     * @param page_num // TODO write
     */
    void onQaNotebookSwitchPage(Gtk::Widget *page, guint page_num);

    /**
     * @brief 前の問題に切り替える
     */
    void onPreviousButtonClicked();

    /**
     * @brief HomeButtonのクリックシグナルを送る
     */
    void onHomeButtonClicked();

    /**
     * @brief 次の問題に切り替える
     */
    void onNextButtonClicked();

    /**
     * @brief 選択肢の選択
     *
     * @param number 選択肢の番号
     */
    void onChoiceButtonClicked(int number);
};

#endif
