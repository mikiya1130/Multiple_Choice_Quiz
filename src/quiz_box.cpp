#include "quiz_box.hpp"
#include <iostream> // TODO remove

QuizBox::QuizBox() : header_box(Gtk::ORIENTATION_HORIZONTAL),
                     right_side_box(Gtk::ORIENTATION_VERTICAL),
                     controll_box(Gtk::ORIENTATION_HORIZONTAL),
                     choice_button_box(Gtk::ORIENTATION_VERTICAL),
                     question_number_label("○問目"),
                     statistics_label("正解数/出題数：○問/○問 (正解率：○%)"),
                     previous_button("←"),
                     home_button("Home"),
                     next_button("→"),
                     choice_label("選択肢")
{
    pack_start(header_box, Gtk::PACK_SHRINK);
    pack_start(vertical_separator, Gtk::PACK_SHRINK);
    pack_start(horizontal_paned);

    header_box.pack_start(question_number_label);
    header_box.pack_start(statistics_label);
    header_box.set_margin_top(QuizBox::PADDING);
    header_box.set_margin_right(QuizBox::PADDING * 2);
    header_box.set_margin_bottom(QuizBox::PADDING);
    header_box.set_margin_left(QuizBox::PADDING * 2);
    question_number_label.set_halign(Gtk::Align::ALIGN_START);
    statistics_label.set_halign(Gtk::Align::ALIGN_END);

    horizontal_paned.pack1(qa_notebook);
    horizontal_paned.pack2(right_side_box, true, false);
    horizontal_paned.set_position(9999);
    horizontal_paned.set_wide_handle(true);

    qa_notebook.append_page(question_box, "問題");
    qa_notebook.append_page(explanation_box, "解説");
    qa_notebook.signal_switch_page().connect(
        sigc::mem_fun(*this, &QuizBox::onQaNotebookSwitchPage));

    right_side_box.pack_start(controll_box, Gtk::PACK_SHRINK);
    right_side_box.pack_start(vertical_right_side_box_separator, Gtk::PACK_SHRINK);
    right_side_box.pack_start(choice_button_box);
    right_side_box.set_margin_top(QuizBox::PADDING);
    right_side_box.set_margin_right(QuizBox::PADDING);
    right_side_box.set_margin_bottom(QuizBox::PADDING);
    right_side_box.set_margin_left(QuizBox::PADDING);

    controll_box.pack_start(previous_button, Gtk::PACK_SHRINK);
    controll_box.pack_start(home_button, Gtk::PACK_SHRINK);
    controll_box.pack_start(next_button, Gtk::PACK_SHRINK);
    controll_box.set_spacing(QuizBox::PADDING);
    controll_box.set_halign(Gtk::Align::ALIGN_CENTER);

    previous_button.signal_clicked().connect(sigc::mem_fun(*this, &QuizBox::onPreviousButtonClicked));
    home_button.signal_clicked().connect(sigc::mem_fun(*this, &QuizBox::onHomeButtonClicked));
    next_button.signal_clicked().connect(sigc::mem_fun(*this, &QuizBox::onNextButtonClicked));

    vertical_right_side_box_separator.set_margin_top(QuizBox::PADDING);
    vertical_right_side_box_separator.set_margin_bottom(QuizBox::PADDING);

    choice_button_box.pack_start(choice_label, Gtk::PACK_SHRINK);

    std::array<Glib::ustring, 4> choice_text{"A1", "A2", "A3", "A4"};
    for (int i = 0; i < choice_text.size(); i++)
    {
        choice_button_vector.emplace_back(Gtk::Button(choice_text[i]));
        choice_button_box.pack_start(choice_button_vector.back(), Gtk::PACK_EXPAND_WIDGET, QuizBox::PADDING);
        choice_button_vector.back().signal_clicked().connect(
            [this, i]
            { onChoiceButtonClicked(i); });
    }
}

QuizBox::typeSignalHomeButtonClicked QuizBox::signalHomeButtonClicked()
{
    return signal_home_button_clicked;
}

void QuizBox::onQaNotebookSwitchPage(Gtk::Widget *page, guint page_num)
{
    std::cout << "page: " << page_num << std::endl; // TODO remove
}

void QuizBox::onPreviousButtonClicked()
{
    std::cout << "previous button clicked" << std::endl; // TODO remove
}

void QuizBox::onHomeButtonClicked()
{
    signal_home_button_clicked.emit();
}

void QuizBox::onNextButtonClicked()
{
    std::cout << "next button clicked" << std::endl; // TODO remove
}

void QuizBox::onChoiceButtonClicked(int number)
{
    std::cout << "choiced number: " << number << std::endl; // TODO remove
}
