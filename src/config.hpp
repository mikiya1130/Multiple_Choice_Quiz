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
        static const Glib::ustring LICENSE = "MIT License\n"
                                             "\n"
                                             "Copyright (c) 2021 Morisaki Mikiya\n"
                                             "\n"
                                             "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                                             "of this software and associated documentation files (the \" Software \"), to deal\n"
                                             "in the Software without restriction, including without limitation the rights\n"
                                             "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
                                             "copies of the Software, and to permit persons to whom the Software is\n"
                                             "furnished to do so, subject to the following conditions:\n"
                                             "\n"
                                             "The above copyright notice and this permission notice shall be included in all\n"
                                             "copies or substantial portions of the Software.\n"
                                             "\n"
                                             "THE SOFTWARE IS PROVIDED \" AS IS \", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
                                             "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
                                             "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
                                             "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
                                             "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                                             "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
                                             "SOFTWARE.\n";
    };
};

#endif
