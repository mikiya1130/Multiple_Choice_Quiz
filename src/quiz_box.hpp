/**
 * @file quiz_box.hpp
 * @brief quiz画面のルートにあたるGtk::Boxの派生クラス
 */
#ifndef QUIZ_BOX_HPP
#define QUIZ_BOX_HPP

#include "config.hpp"
#include "quiz_set.hpp"

#include <gtkmm/separator.h>
#include <gtkmm/paned.h>
#include <gtkmm/notebook.h>
#include <gtkmm/scrolledwindow.h>
#include <webkit2/webkit2.h>

#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief quiz画面のルートにあたるGtk::Boxの派生クラス
 */
class QuizBox : public Gtk::VBox
{
public:
    /**
     * @brief Construct a new Quiz Box object
     */
    QuizBox();

    /**
     * @brief HomeButtonのクリックシグナルを扱う
     */
    typedef sigc::signal<void> typeSignalHomeButtonClicked;

    /**
     * @brief signal accessor
     *
     * @return typeSignalHomeButtonClicked
     */
    typeSignalHomeButtonClicked signalHomeButtonClicked();

    /**
     * @brief jsonファイルからクイズデータを読み込む
     *
     * @param filepath ファイルパス
     * @param selected_key Home画面でチェックをつけたオプションのvector
     */
    void loadQuizSet(const Glib::ustring &filepath, const std::vector<OptionKey> &selected_key);

private:
    Gtk::Box header_box;                               /**< 情報を表示するヘッダーのBox  */
    Gtk::Label question_number_label;                  /**< 現在の問題番号 */
    Gtk::Label statistics_label;                       /**< 統計情報 */
    Gtk::Separator vertical_separator;                 /**< ヘッダーとメイン領域のセパレーター */
    Gtk::Paned horizontal_paned;                       /**< 問題領域と選択肢領域のセパレーター */
    Gtk::Notebook qe_notebook;                         /**< 問題/解説の切り替え用 */
    WebKitWebView *question_web_view;                  /**< 問題文表示用webview */
    Gtk::Widget *question_widget;                      /**< 問題文表示用ウィジェット */
    WebKitWebView *explanation_web_view;               /**< 解説文表示用webview */
    Gtk::Widget *explanation_widget;                   /**< 解説文表示用ウィジェット */
    Gtk::Box right_side_box;                           /**< コントロールBoxと選択肢Boxのコンテナー */
    Gtk::Box controll_box;                             /**< コントロールボタンを子に持つBox */
    Gtk::Button previous_button;                       /**< 前の問題へ戻るボタン */
    Gtk::Button home_button;                           /**< Home画面へ戻るボタン */
    Gtk::Button next_button;                           /**< 次の問題へ進むボタン */
    Gtk::Separator vertical_right_side_box_separator;  /**< コントロールBoxと選択肢Boxのセパレーター */
    Gtk::Label choice_label;                           /**< "選択肢"の文字列 */
    Gtk::ScrolledWindow choice_button_scrolled_window; /**< 選択肢のスクロール用コンテナー */
    Gtk::Box choice_button_box;                        /**< 選択肢のボタンを子に持つBox */
    std::vector<Gtk::Button> choice_button_vector;     /**< 選択肢のボタンのvector */
    QuizSet quiz_set;                                  /**< クイズセット */

    typeSignalHomeButtonClicked signal_home_button_clicked; /**< HomeButtonのクリックシグナル */

    /**
     * @brief クイズを1問読み込む
     *
     * @param quiz_data クイズデータ
     */
    void loadQuizData(const QuizData &quiz_data);

    /**
     * @brief Set the Header info
     */
    void setHeader();

    /**
     * @brief HTMLデータ(文字列またはファイル)を読み込む
     *
     * @param web_view ロード先のウィジェット
     * @param dir jsonファイルを含むディレクトリへのパス
     * @param html HTMLデータ(文字列またはファイル)
     */
    void loadHtml(WebKitWebView *web_view, const Glib::ustring &dir, const Glib::ustring &html);

    /**
     * @brief 前後の問題が存在するか確認する
     *
     * 存在しなければ、問題の切り替えボタンを無効にする
     */
    void checkFirstOrLast();

    /**
     * @brief 選択肢を読み込む
     *
     * @param choice 選択肢のvector
     */
    void loadChoice(const std::vector<Choice> &choice);

    /**
     * @brief 解答済みにする
     *
     * 選択肢のボタンに色を付け、選択不可にする
     *
     * @param answer ユーザーの解答
     */
    void addChoiceButtonColorAndHide(const std::vector<Choice> &choice, const unsigned int &answer);

    /**
     * @brief 前の問題に切り替える
     */
    void onPreviousButtonClicked();

    /**
     * @brief HomeButtonのクリックシグナルを送る
     */
    void onHomeButtonClicked();

    /**
     * @brief 次の問題に切り替える
     */
    void onNextButtonClicked();

    /**
     * @brief 選択肢の選択
     *
     * @param number 選択肢の番号
     */
    void onChoiceButtonClicked(const unsigned int &number);

    /**
     * @brief ボタン押下イベントを取得
     *
     * ボタンを離したタイミングで発生
     *
     * @param event
     * @return true
     * @return false
     */
    bool on_key_release_event(GdkEventKey *event) override;
};

#endif
