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

    quiz_set_button_box.signal_button_release_event().connect(
        sigc::mem_fun(*this, &HomeBox::onQuizSetButtonBoxClicked));

    option_button_vector.emplace_back(CheckButtonWithKey::RandomQuestion, "ランダムに出題する");
    option_button_box.pack_start(option_button_vector.back(), Gtk::PACK_SHRINK, HomeBox::PADDING);
    option_button_vector.emplace_back(CheckButtonWithKey::RandomChoice, "選択肢をランダムに並び替える");
    option_button_box.pack_start(option_button_vector.back(), Gtk::PACK_SHRINK, HomeBox::PADDING);
}

Glib::ustring HomeBox::getFilepath()
{
    Glib::ustring filepath = _filepath;
    _filepath = "/";
    return filepath;
}

bool HomeBox::getActive(CheckButtonWithKey::Key key)
{
    for (CheckButtonWithKey &option_button : option_button_vector)
    {
        if (option_button.getKey() == key)
        {
            return option_button.get_active();
        }
    }

    return false;
}

bool HomeBox::onQuizSetButtonBoxClicked(GdkEventButton *)
{
    return false;
}

bool HomeBox::onQuizSetButtonClicked(Glib::ustring filepath)
{
    _filepath = filepath;
    return false;
}
