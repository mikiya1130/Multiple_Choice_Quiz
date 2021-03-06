/**
 * @file home_box.hpp
 * @brief home画面のルートにあたるGtk::Boxの派生クラス
 */
#ifndef HOME_BOX_HPP
#define HOME_BOX_HPP

#include "config.hpp"
#include "option_key.hpp"

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/separator.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/messagedialog.h>

#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief home画面のルートにあたるGtk::Boxの派生クラス
 */
class HomeBox : public Gtk::Box
{
public:
    /**
     * @brief Construct a new Home Box object
     */
    HomeBox();

    /**
     * @brief QuizSetButtonのクリックシグナルを扱う
     */
    typedef sigc::signal<void, Glib::ustring, std::vector<OptionKey>> typeSignalQuizSetButtonClicked;

    /**
     * @brief signal accessor
     *
     * @return typeSignalQuizSetButtonClicked
     */
    typeSignalQuizSetButtonClicked signalQuizSetButtonClicked();

private:
    Gtk::ScrolledWindow quiz_set_button_scrolled_window;     /**< クイズセットのリストのスクロール用 */
    Gtk::Box quiz_set_button_box;                            /**< クイズセットのボタンを子に持つBox */
    std::vector<Gtk::Button> quiz_set_button_vector;         /**< クイズセットのボタンのvector */
    Gtk::Separator vertical_separator;                       /**< クイズセットとオプションの領域を左右に分けるセパレーター */
    Gtk::Box option_button_box;                              /**< オプションのチェックボックスを子に持つBox */
    std::map<OptionKey, Gtk::CheckButton> option_button_map; /**< オプションのチェックボックスのmap */

    typeSignalQuizSetButtonClicked signal_quiz_set_button_clicked; /**< QuizSetButtonのクリックシグナル */

    /**
     * @brief QuizSetButtonのクリックシグナルを送る
     *
     * @param filepath
     */
    void onQuizSetButtonClicked(const Glib::ustring &filepath);
};

#endif
