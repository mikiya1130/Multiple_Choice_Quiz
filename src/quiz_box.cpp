#include "quiz_box.hpp"

QuizBox::QuizBox() : header_box(Gtk::ORIENTATION_HORIZONTAL),
                     right_side_box(Gtk::ORIENTATION_VERTICAL),
                     controll_box(Gtk::ORIENTATION_HORIZONTAL),
                     previous_button("←"),
                     home_button("Home"),
                     next_button("→"),
                     choice_label("選択肢"),
                     choice_button_box(Gtk::ORIENTATION_VERTICAL)
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

    question_web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    question_widget = Glib::wrap(GTK_WIDGET(question_web_view));
    explanation_web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    explanation_widget = Glib::wrap(GTK_WIDGET(explanation_web_view));

    qa_notebook.append_page(*question_widget, "問題");
    qa_notebook.append_page(*explanation_widget, "解説");

    right_side_box.pack_start(controll_box, Gtk::PACK_SHRINK);
    right_side_box.pack_start(vertical_right_side_box_separator, Gtk::PACK_SHRINK);
    right_side_box.pack_start(choice_label, Gtk::PACK_SHRINK);
    right_side_box.pack_start(choice_button_scrolled_window);
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

    choice_button_scrolled_window.add(choice_button_box);
}

QuizBox::typeSignalHomeButtonClicked QuizBox::signalHomeButtonClicked()
{
    return signal_home_button_clicked;
}

void QuizBox::loadQuizSet(Glib::ustring filepath, std::vector<OptionKey> selected_key)
{
    quiz_set = QuizSet(filepath);
    quiz_set.shuffleQuizSet(selected_key);
    QuizData quiz_data = quiz_set.getQuizData();
    loadQuizData(quiz_data);
}

void QuizBox::loadQuizData(QuizData quiz_data)
{
    Glib::ustring jsonpath = fs::path(quiz_set.getFilepath()).remove_filename().string();
    setHeader();
    loadHtml(question_web_view, jsonpath, quiz_data.question);
    loadHtml(explanation_web_view, jsonpath, quiz_data.explanation);
    checkFirstOrLast();
    loadChoice(quiz_data.choice);
    if (quiz_data.answer < choice_button_vector.size())
    {
        addChoiceButtonColorAndHide(quiz_data.choice, quiz_data.answer);
    }
    else
    {
        explanation_widget->hide();
        choice_button_box.set_sensitive(true);
    }
}

void QuizBox::setHeader()
{
    unsigned int quiz_num, quiz_sum, correct_sum, question_sum;
    quiz_set.getStatistics(quiz_num, quiz_sum, correct_sum, question_sum);

    Glib::ustring s_quiz_num = std::to_string(quiz_num);
    Glib::ustring s_quiz_sum = std::to_string(quiz_sum);
    Glib::ustring s_correct_sum = std::to_string(correct_sum);
    Glib::ustring s_question_sum = std::to_string(question_sum);
    Glib::ustring s_percentage = question_sum == 0 ? "0" : std::to_string(correct_sum * 100 / question_sum);

    question_number_label.set_label(s_quiz_num + "問目 (全" + s_quiz_sum + "問)");
    statistics_label.set_label("正解数/出題数：" + s_correct_sum + "問/" + s_question_sum + "問 (正解率：" + s_percentage + "%)");
}

void QuizBox::loadHtml(WebKitWebView *web_view, Glib::ustring dir, Glib::ustring html)
{
    if (
        fs::is_regular_file(fs::path(dir + html)) && (fs::path(html).extension() == ".html" || fs::path(html).extension() == ".htm"))
    {
        webkit_web_view_load_uri(web_view, ("file:///" + fs::absolute((dir + html).c_str()).string()).c_str());
    }
    else
    {
        webkit_web_view_load_html(web_view, html.c_str(), "/");
    }
}

void QuizBox::checkFirstOrLast()
{
    if (quiz_set.isFirst())
    {
        previous_button.set_sensitive(false);
    }
    else
    {
        previous_button.set_sensitive(true);
    }

    if (quiz_set.isLast())
    {
        next_button.set_sensitive(false);
    }
    else
    {
        next_button.set_sensitive(true);
    }
}

void QuizBox::loadChoice(std::vector<Choice> choice)
{
    choice_button_vector.clear();
    for (unsigned int i = 0; i < choice.size(); i++)
    {
        choice_button_vector.emplace_back(Gtk::Button(choice[i].label));
        choice_button_box.pack_start(choice_button_vector.back(), Gtk::PACK_EXPAND_WIDGET, QuizBox::PADDING);
        choice_button_vector.back().signal_clicked().connect(
            [this, i]
            { onChoiceButtonClicked(i); });
    }

    show_all_children();
}

void QuizBox::addChoiceButtonColorAndHide(std::vector<Choice> choice, unsigned int answer)
{
    for (unsigned int i = 0; i < choice.size(); i++)
    {
        if (choice[i].is_correct)
        {
            choice_button_vector[i].get_style_context()->add_class("correct");
        }
    }

    choice_button_vector[answer].get_style_context()->add_class("answer");

    choice_button_box.set_sensitive(false);
}

void QuizBox::onPreviousButtonClicked()
{
    QuizData quiz_data = quiz_set.getPreviousQuizData();
    loadQuizData(quiz_data);
}

void QuizBox::onHomeButtonClicked()
{
    signal_home_button_clicked.emit();
}

void QuizBox::onNextButtonClicked()
{
    QuizData quiz_data = quiz_set.getNextQuizData();
    loadQuizData(quiz_data);
}

void QuizBox::onChoiceButtonClicked(int number)
{
    quiz_set.answer(number);
    setHeader();
    addChoiceButtonColorAndHide(quiz_set.getQuizData().choice, number);
    explanation_widget->show();
    qa_notebook.set_current_page(qa_notebook.page_num(*explanation_widget));
}
