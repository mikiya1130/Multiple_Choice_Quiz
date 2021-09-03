/**
 * @file check_button_with_key.hpp
 * @brief Keyを持つGtk::CheckButtonの派生クラス
 */
#ifndef CHECK_BUTTON_WITH_KEY_HPP
#define CHECK_BUTTON_WITH_KEY_HPP

#include <gtkmm/checkbutton.h>

/**
 * @brief Keyを持つGtk::CheckButtonの派生クラス
 */
class CheckButtonWithKey : public Gtk::CheckButton
{
public:
    /**
     * @brief このキーの値をインスタンス(CheckButton)の識別に使用する
     */
    enum Key
    {
        RandomQuestion, /**< ランダムに出題するか否かの識別用 */
        RandomChoice,   /**< 選択肢をランダムに並べ替えるか否かの識別用 */
    };

    /**
     * @brief Construct a new Check Button With Key object
     *
     * @tparam Key キー
     * @tparam Args Gtk::CheckButtonの引数
     * @param key キー
     * @param args Gtk::CheckButtonの引数
     */
    template <class Key, class... Args>
    CheckButtonWithKey(Key key, Args... args) : Gtk::CheckButton(args...) { _key = key; };

    /**
     * @brief インスタンスの持つキーを返す
     *
     * @return Key キー
     */
    Key getKey() { return _key; };

private:
    Key _key; /**< キー */
};

#endif
