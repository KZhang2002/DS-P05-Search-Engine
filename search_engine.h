///Search Engine header file
///Contains function prototypes.
///Created by Kenny Zhang

#ifndef INC_22S_FINAL_PROJ_SEARCH_ENGINE_H
#define INC_22S_FINAL_PROJ_SEARCH_ENGINE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <functional>
#include "rapidjson/document.h"
#include "avlTree.h"
#include "porter2_stemmer-master/porter2_stemmer.h"
#include "stop.h"

using rapidjson::Document;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using recursive_directory_iterator = std::experimental::filesystem::recursive_directory_iterator;
using Porter2Stemmer::stem;
using std::pair;
using std::experimental::optional;
using std::cin;

using Time = std::chrono::steady_clock;
using ms = std::chrono::milliseconds;
using dur = std::chrono::duration<float>;
namespace c = std::chrono;

namespace fs = std::experimental::filesystem;

struct rawQuery {
    //base words
    vector<string> baseWords;

    //qualifiers
    string person = "NULL";
    string org = "NULL";
    string notWord = "NULL";

    //stats
    bool isOr = true;
};

struct keyWord {
    string word;
    vector<std::pair<string, int>> idVect;
    keyWord() = default;
    keyWord(const keyWord& kw) : idVect(kw.idVect), word(kw.word) {}

    int numUses = 1;

    friend std::ostream& operator<< (std::ostream&, const keyWord&);
};

class search_engine {
private:
    int orgNum = 0;
    int personNum = 0;
    int articleNum = 0;
    vector<pair<string, int>> freq;

    //Engine Databases
    avlTree<keyWord> wordIndex;
    std::unordered_map<string, std::unordered_map<string, int>> personMap;
    std::unordered_map<string, std::unordered_map<string, int>> orgMap;
    std::unordered_map<string, string> docMap;

    //Simple Lookup Lists
    std::unordered_map<string, int> stopWordMap; //weird usage of umap, maybe find better data structure
    vector<string> queryDefinerTerms = {"OR", "AND", "NOT", "ORG", "PERSON"};

    //Current Search Vars
    vector<pair<string, int>> curSearch; //not used currently, use this to create expanded functionality post first search
public:
    bool debugMode = false;

    //Constructor
    search_engine() = default;

    //Driver
    void engineDriver(int argc); //haha get it?
    void engineDriver(int argc, char** argv);


    //List Creator
    void createStopWordList();

    //Doc Parsers
    void parse_folder(const fs::path& path);
    void parse_doc(const fs::path& path);

    //Query Functions
    void processQuery(char* str);
    vector<pair<string, int>> query(rawQuery q);
    optional<vector<pair<string, int>>> queryKeyWord(string str);

    //Print Functions
    void printWordIndex() { wordIndex.print2D(); }
    static void print_map(std::unordered_map<string, std::unordered_map<string, int>> const &m);
    void printPersons() { cout << endl << "Printing person index" << endl; print_map(personMap); }
    void printOrgs() { cout << endl << "Printing organization index" << endl; print_map(orgMap); }
    void printIDList(const vector<pair<string, int>>& list);
    void printDocText(int i);
    static void printQuery(rawQuery q);


    //Functors
    static int compStr(const string& a, const string& b);
    static int compKW(const keyWord& a, const keyWord& b);
    static int compID(const pair<string, int>& a, const pair<string, int>& b);
    static int compUses(const pair<string, int>& a, const pair<string, int>& b);
};


#endif //INC_22S_FINAL_PROJ_SEARCH_ENGINE_H
