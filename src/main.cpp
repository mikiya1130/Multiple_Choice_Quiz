#include "app_window.hpp"

#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
    try
    {
        auto app = Gtk::Application::create(argc, argv, "com.morisakimikiya");
        AppWindow app_window;
        return app->run(app_window);
    }
    catch (std::runtime_error &)
    {
        close(-1);
    }
}
