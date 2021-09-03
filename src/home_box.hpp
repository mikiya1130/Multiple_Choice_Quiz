/**
 * @file home_box.hpp
 * @brief home画面のルートにあたるGtk::Boxの派生クラス
 */
#ifndef HOME_BOX_HPP
#define HOME_BOX_HPP

#include "check_button_with_key.hpp"

#include <gtkmm/box.h>
#include <gtkmm/separator.h>
#include <gtkmm/button.h>

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
     * @brief Get the Filepath object
     *
     * @return Glib::ustring ファイルパス文字列
     */
    Glib::ustring getFilepath();

    /**
     * @brief Get the Active object
     *
     * @param key キー
     * @return true キーに対応するCheckBoxにチェックが付いているとき
     * @return false キーに対応するCheckBoxにチェックが付いていないとき
     */
    bool getActive(CheckButtonWithKey::Key key);

private:
    static const int PADDING = 15;                        /**< ButtonやCheckBox同士の間隔 */
    static inline const std::string PATH = "./data";      /**< クイズデータを読み込むディレクトリ */
    static inline const std::string EXT = ".json";        /**< クイズデータの保存形式 */
    Gtk::Box quiz_set_button_box;                         /**< クイズセットのボタンを子に持つBox */
    std::vector<Gtk::Button> quiz_set_button_vector;      /**< クイズセットのボタンのvector */
    Gtk::Separator vertical_separator;                    /**< クイズセットとオプションの領域を左右に分けるセパレーター */
    Gtk::Box option_button_box;                           /**< オプションのチェックボックスを子に持つBox */
    std::vector<CheckButtonWithKey> option_button_vector; /**< オプションのチェックボックスのvector */
    Glib::ustring _filepath = "/";                        /**< 選択されたクイズデータへのファイルパス("/"はダミー) */

    /**
     * @brief ButtonClickedの伝搬
     *
     * bool onHomeBoxClicked(GdkEventButton *);
     * ^
     * (this)
     * ^
     * bool onQuizSetButtonClicked(Glib::ustring filepath);
     *
     * @return true Not propagation (not called)
     * @return false Propagation
     */
    bool onQuizSetButtonBoxClicked(GdkEventButton *);

    /**
     * @brief ButtonClickedイベントを伝搬させる
     *
     * @param filepath 押されたボタンの識別用にfilepathをpublic変数に保存しておく
     * @return true Not propagation (not called)
     * @return false Propagation
     */
    bool onQuizSetButtonClicked(Glib::ustring filepath);
};

#endif
