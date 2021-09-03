#include "app_window.hpp"

#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "com.morisakimikiya");
    AppWindow app_window;
    return app->run(app_window);
}
