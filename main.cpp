/**
 * Author: Kenny Zhang
 * Github: https://github.com/KZhang2002
 *
 * Project: Search Engine
 * Repository: https://github.com/SMUCSE2341/22s-final-project-kenny-zhang
 *
 * Class: SMU CS 2341 (4649)
 *
 * Desc:
 *
 * Date Released: 5/2/2022
 * Last Updated: 5/2/2022
 */

#include <iostream>
#include <string>
#include <experimental/filesystem>
#include "rapidjson/document.h"
#include "search_engine.h"
#include <chrono>

using std::ifstream;
using std::string;
using std::cin;
namespace fs = std::experimental::filesystem;

using Time = std::chrono::steady_clock;
using ms = std::chrono::milliseconds;
using dur = std::chrono::duration<float>;
namespace c = std::chrono;

int main(int argc, char** argv) {
    search_engine docProcessor;
    if (argc == 1) {
        docProcessor.engineDriver(argc);
    } else if (argc == 3) {
        docProcessor.engineDriver(argc, argv);
    } else {
        cout << "Invalid amount of arguments entered." << endl;
    }
    return 0;
}
