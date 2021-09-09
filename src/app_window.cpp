#include "app_window.hpp"

AppWindow::AppWindow()
{
    set_default_size(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);

    add(app_stack);

    app_stack.add(home_box, "home");
    app_stack.add(quiz_box, "quiz");

    home_box.signalQuizSetButtonClicked().connect(
        sigc::mem_fun(*this, &AppWindow::onQuizSetButtonClickedInHomeBox));
    quiz_box.signalHomeButtonClicked().connect(
        sigc::mem_fun(*this, &AppWindow::onHomeButtonClickedInQuizBox));

    Glib::RefPtr<Gtk::CssProvider> correct_css_provider = Gtk::CssProvider::create();
    correct_css_provider->load_from_data(
        ".answer {color: red; border-color: red;} \
        .correct {color: green; border-color: green;}");
    get_style_context()->add_provider_for_screen(
        get_screen(), correct_css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    header_bar.set_title(Config::TITLE);
    header_bar.set_show_close_button(true);
    header_bar.pack_start(about_button);
    set_titlebar(header_bar);

    about_button.set_label("About");
    about_button.signal_clicked().connect(sigc::mem_fun(*this, &AppWindow::onAboutButtonClicked));

    app_stack.set_visible_child("home");

    show_all_children();
}

void AppWindow::onQuizSetButtonClickedInHomeBox(const Glib::ustring &filepath, const std::vector<OptionKey> &selected_key)
{
    app_stack.set_visible_child("quiz");
    try
    {
        quiz_box.loadQuizSet(filepath, selected_key);
    }
    catch (std::exception &e)
    {
        Gtk::MessageDialog dialog(
            "クイズデータが1件も存在しません", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, false);
        dialog.set_secondary_text("クイズセット選択画面へ戻ります");
        dialog.run();

        app_stack.set_visible_child("home");
    }
}

void AppWindow::onHomeButtonClickedInQuizBox()
{
    app_stack.set_visible_child("home");
}

void AppWindow::onAboutButtonClicked()
{
    about_dialog.set_transient_for(*this);
    about_dialog.set_program_name(Config::About::PROGRAM_NAME);
    about_dialog.set_version(Config::About::VERSION);
    about_dialog.set_website(Config::About::WEBSITE);
    about_dialog.set_website_label(Config::About::WEBSITE_LABEL);
    about_dialog.set_copyright(Config::About::COPYRIGHT);
    about_dialog.set_authors(Config::About::AUTHORS);
    about_dialog.set_license(Config::About::LICENSE);
    about_dialog.show();
}
