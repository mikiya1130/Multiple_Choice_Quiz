#include "app_window.hpp"
#include <iostream> // TODO remove

AppWindow::AppWindow()
{
    set_title("Multiple_Choice_Quiz");
    set_default_size(800, 600);

    add(app_stack);

    app_stack.add(home_box, "home");
    app_stack.add(quiz_box, "quiz");

    home_box.signal_button_release_event().connect(
        sigc::mem_fun(*this, &AppWindow::onHomeBoxClicked));
    quiz_box.signal_button_release_event().connect(
        sigc::mem_fun(*this, &AppWindow::onQuizBoxClicked));

    app_stack.set_visible_child("home");

    show_all_children();
}

bool AppWindow::onHomeBoxClicked(GdkEventButton *)
{
    Glib::ustring filepath = home_box.getFilepath();
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(filepath);

    char *contents = nullptr;
    gsize length = 0;

    try
    {
        file->load_contents(contents, length);
    }
    catch (Glib::Error &)
    {
        g_free(contents);
        return true;
    }

    // TODO remove
    std::cout << "filepath: " << filepath << std::endl;
    std::cout << "contents: " << contents << std::endl;
    std::cout << "length  : " << length << std::endl;
    std::cout << "question: " << home_box.getActive(CheckButtonWithKey::RandomQuestion) << std::endl;
    std::cout << "choice  : " << home_box.getActive(CheckButtonWithKey::RandomChoice) << std::endl;

    app_stack.set_visible_child("quiz");

    g_free(contents);
    return true;
}

bool AppWindow::onQuizBoxClicked(GdkEventButton *)
{
    app_stack.set_visible_child("home");

    return true;
}
