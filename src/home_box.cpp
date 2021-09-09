#include "home_box.hpp"

HomeBox::HomeBox() : quiz_set_button_box(Gtk::ORIENTATION_VERTICAL),
                     option_button_box(Gtk::ORIENTATION_VERTICAL)
{
    pack_start(quiz_set_button_scrolled_window, Gtk::PACK_EXPAND_WIDGET);
    pack_start(vertical_separator, Gtk::PACK_SHRINK);
    pack_start(option_button_box, Gtk::PACK_SHRINK, Config::PADDING * 2);

    quiz_set_button_scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    quiz_set_button_scrolled_window.add(quiz_set_button_box);

    quiz_set_button_box.set_margin_left(Config::PADDING);
    quiz_set_button_box.set_margin_right(Config::PADDING);

    try
    {
        for (const fs::directory_entry &file : fs::recursive_directory_iterator(
                 fs::read_symlink("/proc/self/exe").remove_filename().string() + Config::PATH, fs::directory_options::skip_permission_denied))
        {
            if (file.is_regular_file() && file.path().extension() == Config::EXT)
            {
                quiz_set_button_vector.emplace_back(file.path().stem().string());
                quiz_set_button_box.pack_start(
                    quiz_set_button_vector.back(), Gtk::PACK_EXPAND_WIDGET, Config::PADDING);
                quiz_set_button_vector.back().signal_clicked().connect(
                    [this, file]
                    { onQuizSetButtonClicked(file.path().string()); });
            }
        }

        if (quiz_set_button_vector.size() == 0)
        {
            throw std::runtime_error("runtime error: json file not found in " + Config::PATH);
        }
    }
    catch (std::runtime_error &)
    {
        Gtk::MessageDialog dialog(
            "クイズセットが見つかりませんでした", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, false);
        dialog.set_secondary_text(
            "dataディレクトリを用意し、\njson形式のクイズデータを作成してください\n\n"
            "アプリケーションを終了します");
        dialog.run();

        throw std::runtime_error("runtime error: quiz set not found");
    }

    option_button_map[OptionKey::RandomQuestion] = Gtk::CheckButton("ランダムに出題する");
    option_button_map[OptionKey::RandomChoice] = Gtk::CheckButton("選択肢をランダムに並び替える");
    for (auto &[key, option_button] : option_button_map)
    {
        option_button_box.pack_start(option_button, Gtk::PACK_SHRINK, Config::PADDING);
    }
}

HomeBox::typeSignalQuizSetButtonClicked HomeBox::signalQuizSetButtonClicked()
{
    return signal_quiz_set_button_clicked;
}

void HomeBox::onQuizSetButtonClicked(const Glib::ustring &filepath)
{
    std::vector<OptionKey> selected_key;

    for (auto &[key, option_button] : option_button_map)
    {
        if (option_button.get_active())
        {
            selected_key.push_back(key);
        }
    }
    signal_quiz_set_button_clicked.emit(filepath, selected_key);
}
