/**
 * @file quiz_set.hpp
 * @brief クイズセットと統計情報の管理
 */
#ifndef QUIZ_SET_HPP
#define QUIZ_SET_HPP

#include "option_key.hpp"
#include "quiz_data.hpp"
#include "../library/nlohmann/json.hpp"

#include <gtkmm/messagedialog.h>
#include <glibmm/ustring.h>

#include <fstream>
#include <random>

/**
 * @brief クイズセットと統計情報の管理
 */
class QuizSet
{
public:
    /**
     * @brief Construct a new Quiz Set object
     */
    QuizSet();

    /**
     * @brief Construct a new Quiz Set object
     *
     * @param filepath ファイルパス
     */
    QuizSet(const Glib::ustring &filepath);

    /**
     * @brief クイズセットをシャッフルする
     *
     * @param selected_key Home画面でチェックをつけたオプションのvector
     */
    void shuffleQuizSet(const std::vector<OptionKey> &selected_key);

    /**
     * @brief Get the Quiz Data object
     *
     * @return QuizData
     */
    QuizData getQuizData();

    /**
     * @brief Get the Previous Quiz Data object
     *
     * @return QuizData
     */
    QuizData getPreviousQuizData();

    /**
     * @brief Get the Next Quiz Data object
     *
     * @return QuizData
     */
    QuizData getNextQuizData();

    /**
     * @brief Get the filepath to QuizSet
     *
     * @return Glib::ustring クイズデータファイルへのパス
     */
    Glib::ustring getFilepath();

    /**
     * @brief Get the statistics object
     *
     * 各引数に値を返す
     *
     * @param _quiz_num 現在のクイズ番号
     * @param _quiz_sum クイズの総数(クイズデータのvectorの要素数)
     * @param _correct_sum 現在までの正解数
     * @param _question_sum 現在までの出題数
     */
    void getStatistics(unsigned int &_quiz_num, unsigned int &_quiz_sum, unsigned int &_correct_sum, unsigned int &_question_sum);

    /**
     * @brief 現在の問題がクイズセットの最初の問題か否か
     *
     * @return true
     * @return false
     */
    bool isFirst();

    /**
     * @brief 現在の問題がクイズセットの最後の問題か否か
     *
     * @return true
     * @return false
     */
    bool isLast();

    /**
     * @brief ユーザーの解答を反映させる
     *
     * @param number 選択番号
     */
    void answer(const unsigned int &number);

private:
    Glib::ustring filepath;                 /**< クイズデータファイルへのパス */
    std::vector<QuizData> quiz_data_vector; /**< クイズデータのvector */
    unsigned int quiz_set_length;           /**< クイズの総数(クイズデータのvectorの要素数) */
    unsigned int current_num;               /**< 現在のクイズ番号 */
    unsigned int correct_sum;               /**< 現在までの正解数 */
    unsigned int question_sum;              /**< 現在までの出題数 */

    /**
     * @brief nlohmann::jsonオブジェクトをQuizData構造体に変換する
     *
     * @param j_quiz_data nlohmann::jsonオブジェクト
     * @return QuizData QuizData構造体
     */
    QuizData parseJson(nlohmann::json &j_quiz_data);
};

#endif
