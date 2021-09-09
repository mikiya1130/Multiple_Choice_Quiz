/**
 * @file config.hpp
 * @brief 設定値管理ファイル
 */
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <glibmm/ustring.h>
#include <vector>

namespace Config
{
    static const Glib::ustring APPLICATION_ID = "com.morisakimikiya";
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const Glib::ustring TITLE = "Multiple_Choice_Quiz";

    static const int PADDING = 15;            /**< ButtonやCheckBox同士の間隔 */
    static const std::string PATH = "./data"; /**< クイズデータを読み込むディレクトリ */
    static const std::string EXT = ".json";   /**< クイズデータの保存形式 */

    namespace About
    {
        static const Glib::ustring PROGRAM_NAME = "Multiple_Choice_Quiz";
        static const Glib::ustring VERSION = "1.0.0";
        static const Glib::ustring WEBSITE = "https://github.com/mikiya1130/Multiple_Choice_Quiz";
        static const Glib::ustring WEBSITE_LABEL = "Multiple_Choice_Quiz";
        static const Glib::ustring COPYRIGHT = "© 2021 Morisaki Mikiya";
        static const std::vector<Glib::ustring> AUTHORS({"Morisaki Mikiya"});
        static const Glib::ustring LICENSE = "MIT Lisence";
    };
};

#endif
