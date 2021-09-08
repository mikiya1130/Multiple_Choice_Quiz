/**
 * @file quiz_data.hpp
 * @brief クイズデータ
 */
#ifndef QUIZ_DATA_HPP
#define QUIZ_DATA_HPP

#include "../library/nlohmann/json.hpp"

#include <glibmm/ustring.h>
#include <glibmm.h>

#include <vector>

struct Choice
{
    Glib::ustring label; /**< 選択肢の文字列 */
    bool is_correct;     /**< その選択肢が正解か否か */
};

struct QuizData
{
    Glib::ustring question;     /**< 問題文 */
    std::vector<Choice> choice; /**< 選択肢 */
    unsigned int answer;        /**< ユーザーの解答 */
    Glib::ustring explanation;  /**< 解説文 */
    bool has_fault;             /**< データ不備の判別用フラグ */
};

#endif
