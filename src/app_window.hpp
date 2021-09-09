/**
 * @file app_window.hpp
 * @brief rootウィンドウクラス
 */
#ifndef APP_WINDOW_HPP
#define APP_WINDOW_HPP

#include "config.hpp"
#include "home_box.hpp"
#include "quiz_box.hpp"

#include <gtkmm/stack.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/aboutdialog.h>

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
    Gtk::Stack app_stack;          /**< Home画面とQuiz画面の切り替え用Stack */
    HomeBox home_box;              /**< このBox以下にHome画面を描画 */
    QuizBox quiz_box;              /**< このBox以下にQuiz画面を描画 */
    Gtk::HeaderBar header_bar;     /**< ヘッダーバー */
    Gtk::Button about_button;      /**< aboutボタン */
    Gtk::AboutDialog about_dialog; /**< aboutダイアログ */

    /**
     * @brief HomeBoxのQuizSetButtonのクリックシグナルを受け取る
     *
     * @param filepath 押されたボタンに対応するファイル
     * @param selected_key チェックをつけたオプションのvector
     */
    void onQuizSetButtonClickedInHomeBox(const Glib::ustring &filepath, const std::vector<OptionKey> &selected_key);

    /**
     * @brief QuizBoxのHomeButtonのクリックシグナルを受け取る
     */
    void onHomeButtonClickedInQuizBox();

    /**
     * @brief AboutButtonのクリックシグナルを受け取る
     */
    void onAboutButtonClicked();
};

#endif
