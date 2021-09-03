/**
 * @file app_window.hpp
 * @brief rootウィンドウクラス
 */
#ifndef APP_WINDOW_HPP
#define APP_WINDOW_HPP

#include "home_box.hpp"
#include "quiz_box.hpp"

#include <gtkmm/window.h>
#include <gtkmm/stack.h>
#include <giomm/file.h>

/**
 * @brief rootウィンドウクラス
 */
class AppWindow : public Gtk::Window
{
public:
    /**
     * @brief Construct a new App Window object
     */
    AppWindow();

private:
    Gtk::Stack app_stack; /**< Home画面とQuiz画面の切り替え用Stack */
    HomeBox home_box;     /**< このBox以下にHome画面を描画 */
    QuizBox quiz_box;     /**< このBox以下にQuiz画面を描画 */

    /**
     * @brief ButtonClickedの伝搬
     *
     * (this)
     * ^
     * bool onQuizSetButtonBoxClicked(GdkEventButton *);
     * ^
     * bool onQuizSetButtonClicked(Glib::ustring filepath);
     *
     * @return true Not propagation
     * @return false Propagation (not called)
     */
    bool onHomeBoxClicked(GdkEventButton *);

    bool onQuizBoxClicked(GdkEventButton *);
};

#endif
