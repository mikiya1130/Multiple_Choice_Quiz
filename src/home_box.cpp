#include "home_box.hpp"

HomeBox::HomeBox() : quiz_set_button_box(Gtk::ORIENTATION_VERTICAL),
                     option_button_box(Gtk::ORIENTATION_VERTICAL)
{
    pack_start(quiz_set_button_box, Gtk::PACK_EXPAND_WIDGET, HomeBox::PADDING * 2);
    pack_start(vertical_separator, Gtk::PACK_SHRINK);
    pack_start(option_button_box, Gtk::PACK_SHRINK, HomeBox::PADDING * 2);

    for (fs::directory_entry file : fs::recursive_directory_iterator(
             HomeBox::PATH, fs::directory_options::skip_permission_denied))
    {
        if (file.is_regular_file() && file.path().extension() == HomeBox::EXT)
        {
            quiz_set_button_vector.emplace_back(file.path().stem().string());
            quiz_set_button_box.pack_start(
                quiz_set_button_vector.back(), Gtk::PACK_EXPAND_WIDGET, HomeBox::PADDING);
            quiz_set_button_vector.back().signal_clicked().connect(
                [this, file]
                { onQuizSetButtonClicked(file.path().string()); });
        }
    }

    option_button_map[OptionKey::RandomQuestion] = Gtk::CheckButton("ランダムに出題する");
    option_button_map[OptionKey::RandomChoice] = Gtk::CheckButton("選択肢をランダムに並び替える");
    for (auto &[key, option_button] : option_button_map)
    {
        option_button_box.pack_start(option_button, Gtk::PACK_SHRINK, HomeBox::PADDING);
    }
}

HomeBox::typeSignalQuizSetButtonClicked HomeBox::signalQuizSetButtonClicked()
{
    return signal_quiz_set_button_clicked;
}

void HomeBox::onQuizSetButtonClicked(Glib::ustring filepath)
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
