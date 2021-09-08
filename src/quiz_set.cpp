#include "quiz_set.hpp"

QuizSet::QuizSet() {}

QuizSet::QuizSet(const Glib::ustring &filepath) : filepath(filepath),
                                                  quiz_set_length(0),
                                                  current_num(0),
                                                  correct_sum(0),
                                                  question_sum(0)
{
    std::ifstream i(filepath);
    nlohmann::json j_quiz_set;
    i >> j_quiz_set;

    int count_fault_data = 0;
    for (nlohmann::json &j_quiz_data : j_quiz_set)
    {
        QuizData quiz_data = parseJson(j_quiz_data);
        if (quiz_data.has_fault == false)
        {
            quiz_data_vector.emplace_back(quiz_data);
            quiz_set_length++;
        }
        else
        {
            count_fault_data++;
        }
    }

    if (count_fault_data != 0)
    {
        Gtk::MessageDialog dialog(
            "クイズデータ読み込みエラー", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_CLOSE, false);
        dialog.set_secondary_text(
            std::to_string(j_quiz_set.size()) + "問中" + std::to_string(count_fault_data) + "問の読み込みに失敗しました");
        dialog.run();
    }
}

void QuizSet::shuffleQuizSet(const std::vector<OptionKey> &selected_key)
{
    if (!selected_key.empty())
    {
        std::random_device seed_gen;
        std::mt19937_64 engine(seed_gen());

        for (const OptionKey &key : selected_key)
        {
            switch (key)
            {
            case OptionKey::RandomQuestion:
                std::shuffle(quiz_data_vector.begin(), quiz_data_vector.end(), engine);
                break;
            case OptionKey::RandomChoice:
                for (QuizData &quiz_data : quiz_data_vector)
                {
                    std::shuffle(quiz_data.choice.begin(), quiz_data.choice.end(), engine);
                }
                break;
            default:
                break;
            }
        }
    }
}

QuizData QuizSet::getQuizData()
{
    if (quiz_data_vector.size() == 0)
    {
        throw std::runtime_error("Not Exists QuizData Exception");
    }

    return quiz_data_vector[current_num];
}

QuizData QuizSet::getPreviousQuizData()
{
    if (0 < current_num)
    {
        current_num--;
    }
    return getQuizData();
}

QuizData QuizSet::getNextQuizData()
{
    if (current_num < quiz_set_length - 1)
    {
        current_num++;
    }
    return getQuizData();
}

Glib::ustring QuizSet::getFilepath()
{
    return filepath;
}

void QuizSet::getStatistics(unsigned int &_quiz_num, unsigned int &_quiz_sum, unsigned int &_correct_sum, unsigned int &_question_sum)
{
    _quiz_num = current_num + 1;
    _quiz_sum = quiz_set_length;
    _correct_sum = correct_sum;
    _question_sum = question_sum;
}

bool QuizSet::isFirst()
{
    return current_num == 0;
}

bool QuizSet::isLast()
{
    return current_num == quiz_set_length - 1;
}

void QuizSet::answer(const unsigned int &number)
{
    quiz_data_vector[current_num].answer = number;
    question_sum++;
    if (quiz_data_vector[current_num].choice[number].is_correct)
    {
        correct_sum++;
    }
}

QuizData QuizSet::parseJson(nlohmann::json &j_quiz_data)
{
    QuizData quiz_data;

    quiz_data.has_fault = true;

    if (
        j_quiz_data["question"].is_string() && j_quiz_data["choice"].is_array() && j_quiz_data["correct"].is_number_unsigned() && j_quiz_data["explanation"].is_string())
    {
        quiz_data.question = Glib::locale_to_utf8(j_quiz_data["question"]);
        quiz_data.answer = -1;
        quiz_data.explanation = Glib::locale_to_utf8(j_quiz_data["explanation"]);

        for (const nlohmann::json &j_choice : j_quiz_data["choice"])
        {
            if (j_choice.is_string())
            {
                Choice choice;
                choice.label = Glib::locale_to_utf8(j_choice);
                choice.is_correct = false;
                quiz_data.choice.push_back(choice);
            }
        }
        if (quiz_data.choice.size() == j_quiz_data["choice"].size())
        {
            quiz_data.choice[j_quiz_data["correct"]].is_correct = true;
            quiz_data.has_fault = false;
        }
    }

    return quiz_data;
}
