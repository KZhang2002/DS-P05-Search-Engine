///Search Engine cpp file
///Contains function definitions.
///Created by Kenny Zhang

#include "search_engine.h"
#include <utility>

///Main Driver
void search_engine::engineDriver(int argc) {
    cout << "JSON FILE DIRECTORY SEARCH ENGINE" << endl;
    cout << "\tCreated by Kenny Zhang for SMU CS 2341 (4649)" << endl;
    cout << "\tRepo: https://github.com/SMUCSE2341/22s-final-project-kenny-zhang" << endl;

    char* userInput;
    fs::path dataPath;
    bool end = false;

    cout << "Enter an absolute data path to the target directory." << endl;
    cin >> dataPath;

    while (!exists(dataPath) || !dataPath.is_absolute()) {
        cout << "The data path that you entered \"" << dataPath << "\" is not valid." << endl
             << "Please check that your data path is absolute and exists." << endl << endl << endl;

        cin.ignore();
        cout << "Enter an absolute data path to the target directory." << endl;
        cin >> dataPath;
    }

    debugMode = false;

    createStopWordList();

    c::steady_clock::time_point t1 = c::steady_clock::now();
    if (exists(dataPath) && dataPath.is_absolute()) {
        c::steady_clock::time_point t1 = c::steady_clock::now();

        if (debugMode) {
            cout << "exists() = " << fs::exists(dataPath) << "\n"
                 << "root_name() = " << dataPath.root_name() << "\n"
                 << "root_path() = " << dataPath.root_path() << "\n"
                 << "relative_path() = " << dataPath.relative_path() << "\n"
                 << "parent_path() = " << dataPath.parent_path() << "\n"
                 << "filename() = " << dataPath.filename() << "\n"
                 << "stem() = " << dataPath.stem() << "\n"
                 << "extension() = " << dataPath.extension() << "\n";
        }
    }

    parse_folder(dataPath);

    c::steady_clock::time_point t2 = c::steady_clock::now();

    c::duration<double> time_span = c::duration_cast<c::duration<double>>(t2 - t1);

    cout << endl << endl;

    cout << "Stats: " << endl;

    if (time_span.count() > 60.0)
        cout << "Parse duration: " << time_span.count() / 60.0 << " minutes, " << fmod(time_span.count(), 60.0) << " seconds." << endl;
    else
        cout << "Parse duration: " << time_span.count() << " seconds." << endl;

    cout << "Number of Unique Orgs: " << orgNum << endl;
    cout << "Number of Unique Persons: " << personNum << endl;
    cout << "Number of Unique Words: " << wordIndex.numNodes << endl;
    cout << "Number of Unique Articles: " << articleNum << endl;
    cout << endl << endl;


    printPersons();
    printOrgs();

    cout << endl << endl;

    if (debugMode) printWordIndex();

    char query[1024];

    cin.ignore();
    cout << "Enter your query." << endl;
    cin.getline(query, 1024);

    do {
        processQuery(query);
        int i = -1;
        do {
            cout << "Enter document number of document you want to read." << endl;
            cout << "Enter \"-1\" to return to make a new query." << endl;

            cin >> i;
            printDocText(i - 1);

            cout << endl << endl;
        } while (i != -1);

        cout << "Search finished. Enter \"q\" as your query, if you want to exit." << endl;

        cin.ignore();
        cout << "Enter your query." << endl;
        cin.getline(query, 1024);
    } while (strcmp(query, "q") != 0);
}

void search_engine::engineDriver(int argc, char **argv) {
    cout << "JSON FILE DIRECTORY SEARCH ENGINE" << endl;
    cout << "\tCreated by Kenny Zhang for SMU CS 2341 (4649)" << endl;
    cout << "\tRepo: https://github.com/SMUCSE2341/22s-final-project-kenny-zhang" << endl;

    char* userInput;
    fs::path dataPath = argv[2];
    bool end = false;
    bool firstTime = true;

    cout << "Enter an absolute data path to the target directory." << endl;
    cout << argv[2] << endl;

    while (!exists(dataPath) || !dataPath.is_absolute()) {
        cout << "The data path that you entered \"" << dataPath << "\" is not valid." << endl
             << "Please check that your data path is absolute and exists." << endl << endl << endl;

        cin.ignore();
        cout << "Enter an absolute data path to the target directory." << endl;
        cin >> dataPath;
    }

    debugMode = false;

    createStopWordList();

    c::steady_clock::time_point t1 = c::steady_clock::now();
    if (exists(dataPath) && dataPath.is_absolute()) {
        //c::steady_clock::time_point t1 = c::steady_clock::now();

        if (debugMode) {
            cout << "exists() = " << fs::exists(dataPath) << "\n"
                 << "root_name() = " << dataPath.root_name() << "\n"
                 << "root_path() = " << dataPath.root_path() << "\n"
                 << "relative_path() = " << dataPath.relative_path() << "\n"
                 << "parent_path() = " << dataPath.parent_path() << "\n"
                 << "filename() = " << dataPath.filename() << "\n"
                 << "stem() = " << dataPath.stem() << "\n"
                 << "extension() = " << dataPath.extension() << "\n";

            for (int i = 1; i < argc; i++)
                cout << "argv[" << i << "]" << " = " << argv[i] << endl;
        }
    }

    parse_folder(dataPath);

    c::steady_clock::time_point t2 = c::steady_clock::now();

    c::duration<double> time_span = c::duration_cast<c::duration<double>>(t2 - t1);

    cout << endl << endl;

    cout << "Stats: " << endl;

    if (time_span.count() > 60.0)
        cout << "Parse duration: " << time_span.count() / 60.0 << " minutes, " << fmod(time_span.count(), 60.0) << " seconds." << endl;
    else
        cout << "Parse duration: " << time_span.count() << " seconds." << endl;

    cout << "Number of Unique Orgs: " << orgNum << endl;
    cout << "Number of Unique Persons: " << personNum << endl;
    cout << "Number of Unique Words: " << wordIndex.numNodes << endl;
    cout << "Number of Unique Articles: " << articleNum << endl;
    cout << endl << endl;

    if (debugMode) printWordIndex();

    char* query = argv[1];

    cout << "Enter your query." << endl;
    cout << query;

    do {
        processQuery(query);
        int i = -1;
        do {
            cout << "Enter document number of document you want to read." << endl;
            cout << "Enter \"-1\" to return to make a new query." << endl;

            cin.ignore();
            cin >> i;

            if (!std::cin.good())
            {
                cin.ignore(1024, '\n');
                cin.clear();
                cout << "INVALID INPUT." << endl;
            } else {
                printDocText(i - 1);
            }

            cout << endl << endl;
        } while (i != -1);

        cout << "Search finished. Enter \"q\" as your query, if you want to exit." << endl;

        cin.ignore();
        cout << "Enter your query." << endl;
        cin.getline(query, 1024);
    } while (strcmp(query, "q") != 0);
}


///List Creator
/**
 * Adds all words in "stop.h"
 * to stopWordList. Super janky.
 */
void search_engine::createStopWordList() {
    stop List;
    std::stringstream file(List.stopWords);

        while(file.peek() != EOF) {
            char stopWord[1024];

            //gets word
            file.getline(stopWord, 1024);
            string temp = stopWord;
            file.clear();
            //stopWordList.push_back(temp);

            pair<string, int> tempPair (stopWord, 1);
            stopWordMap.insert(tempPair);
        }
}

///Doc Parsers
/**
 * Parses directory and passes documents to parse_doc().
 * Ignores nonjson files. Will parse subfolders of the directory.
 * @param path
 */
void search_engine::parse_folder(const fs::path &path) {
    cout << "accessing path: " << path << endl;

    for (const auto& dirEntry : fs::directory_iterator(path)) {
        //cout << dirEntry.path() << endl;

        if (is_directory(dirEntry.path())) {
            cout << "Parsing folder. . ." << endl;
            parse_folder(dirEntry.path()); //insert element
            cout << "Folder parsed" << endl;
        } else if (dirEntry.path().extension() == ".json") {
            parse_doc(dirEntry.path());
        }
    }
}

/**
 * Parses doc and adds json title words and ID to tree.
 * Ignores nonjson files. Will parse subfolders of the directory.
 * @param path
 */
void search_engine::parse_doc(const fs::path &dir) {
    // declare the document object
    rapidjson::Document doc;

    // initialize the input file
    std::ifstream jsonFile(dir);

    //cout << jsonFile.is_open() << endl;

    // put the whole file's data into fileText
    string fileText;
    string temp;
    while (getline(jsonFile, temp)) { fileText += temp; }
    jsonFile.close();

    doc.Parse(fileText.c_str());

    if (debugMode) if (doc.IsObject()) cout << "Document parsed properly" << endl << endl;

    std::stringstream txt;
    txt << doc["title"].GetString() << " " << doc["text"].GetString();

    const char *delimiters = " ,:()-®|?‘’;\".[]/\\“”!，：？%—\u200B\u200C\u200D\uFEFF–×"; //'’

    char id[256];
    strcpy(id, doc["uuid"].GetString());

    pair<string, string> docPair (id, fileText);
    docMap.insert(docPair);

    articleNum++;

    //if(debugMode) cout << "id: " << docPair.first << "\ntext: " << docPair.second << endl;

    while (txt.peek() != EOF) {
        char text[1024];
        txt.getline(text, 1024, '\n'); //Todo: rename these variables to be less similar
        txt.clear();

        if(debugMode) cout << "Full line: " << text << endl;

        char *buffer = std::strtok(text, delimiters);

        while (buffer) {
            keyWord token;
            token.word = buffer;
            if (debugMode) cout << token.word << " -> ";
            std::for_each(token.word.begin(), token.word.end(), [](char &c) { c = tolower(c);}); //lowercases string //todo implement punctuation clearing
            if (debugMode) cout << token.word << endl;

            if(!stopWordMap.count(token.word)) { //todo replace with unord map std::find(stopWordList.begin(), stopWordList.end(), token.word) == stopWordList.end()

                token.idVect.push_back(pair<string, int> (id, 1));

                if (debugMode) {
                    if (token.word.empty()) {
                        cout << "\n\n" << token.idVect[0].first << "\n\n";
                        continue;
                    }
                }

                if (debugMode) cout << token.word << " -> ";

                Porter2Stemmer::stem(token.word);

                if (debugMode) cout << token.word << " | ";

                wordIndex.insert(token, &compKW);

                /*if (stopWordMap.count(token.word)) { //todo replace with unord map

                }*/
            } else {
                //todo yooo look at dis doood
            }
            buffer = std::strtok(nullptr, delimiters);
        }
        if (debugMode) cout << endl;
    }

    for (auto &v : doc["entities"]["organizations"].GetArray ()) {
        if (debugMode) cout << v["name"].GetString() << endl;
        if (orgMap.count(v["name"].GetString()) == 0) {
            orgNum++;
        }
        std::unordered_map<string, int> &idVect = orgMap[v["name"].GetString()];
        idVect[id];
    }

    for (auto &v : doc["entities"]["persons"].GetArray ()) {
        if (debugMode) cout << v["name"].GetString() << endl;
        if (personMap.count(v["name"].GetString()) == 0) {
            personNum++;
        }
        std::unordered_map<string, int>& idVect = personMap[v["name"].GetString()];
        idVect[id];
    }
}

///Query Functions
/**
 * Processes raw query search.
 * Manages query() function.
 * @param str
 */
void search_engine::processQuery(char* str) {
    rawQuery q;
    string mode = "OR";

    const char *delimiters = "| []";

    char *buffer = std::strtok(str, delimiters);

    //AND/OR check
    if (strcmp(buffer, "AND") == 0) {
        q.isOr = false;
        buffer = std::strtok(nullptr, delimiters);
    }
    else if (strcmp(buffer, "OR") == 0) {
        q.isOr = true;
        buffer = std::strtok(nullptr, delimiters);
    }
    else {
        q.isOr = true;
    }

    //Get base words
    while (buffer) {
        string temp = buffer;
        /*cout << temp << endl;*/

        if (std::find(queryDefinerTerms.begin(), queryDefinerTerms.end(), temp) != queryDefinerTerms.end()) {
            mode = temp;
            buffer = std::strtok(nullptr, delimiters);
            break;
        }

        std::for_each(temp.begin(), temp.end(), [](char &c) { c = tolower(c); }); //lowercases string

        if (stopWordMap.count(buffer)) {
            cout << "Search term \"" << temp << "\" is a stop word and has been removed from the query." << endl;
            buffer = std::strtok(nullptr, delimiters);
            continue;
        }

        q.baseWords.push_back(temp);
        buffer = std::strtok(nullptr, delimiters);
    }

    if (q.baseWords.empty()) {
        cout << R"(No valid search terms.)" << endl;
        return;
    }

    //Get query definers
    while (buffer) {
        string temp = buffer;

        if (std::find(queryDefinerTerms.begin(), queryDefinerTerms.end(), temp) != queryDefinerTerms.end()) {
            mode = temp;
            /*cout << "mode has been set to: " << temp << endl;*/
            buffer = std::strtok(nullptr, delimiters);
            continue;
        }

        if (mode == "NOT") {
            std::for_each(temp.begin(), temp.end(), [](char &c) { c = tolower(c); }); //lowercases string

            if (stopWordMap.count(buffer)) {
                buffer = std::strtok(nullptr, delimiters);
                cout << "Search term \"" << temp << "\" is a stop word and has been removed from the query." << endl;
                continue;
            }

            q.notWord = temp;
        }
        else if (mode == "ORG") q.org = temp;
        else if (mode == "PERSON") q.person = q.person == "NULL" ? q.person = temp : q.person + " " + temp;
        else {
            cout << R"(ERROR HAS OCCURRED. QUERY DEFINER MODE HAS BEEN SET TO INVALID TERM ")" << temp << "\"";
            return;
        }

        buffer = std::strtok(nullptr, delimiters);
    }

    printQuery(q);

    vector<pair<string, int>> idList = query(q);
    curSearch = idList;

    std::sort(idList.begin(), idList.end(), compUses);

    cout << "ID List:" << endl;
    printIDList(idList);
}

/**
 * Takes id vectors from queryKeyWord()
 * and applies rawQuery rules on it.
 * @param str
 */
vector<pair<string, int>> search_engine::query(rawQuery q) {
    vector<pair<string, int>> idList;

    for (auto & baseWord : q.baseWords) {
        optional<vector<pair<string, int>>> temp;
        temp = queryKeyWord(baseWord);

        if (!temp) continue;

        std::sort(temp.value().begin(), temp.value().end(), compID);

        optional<vector<pair<string, int>>> temp2;
        temp2 = idList;

        if (idList.empty()) {
            idList = temp.value();
        } else {
            if (temp) {
                idList.clear();
                if (q.isOr) {
                    std::set_union(temp2.value().begin(), temp2.value().end(), temp.value().begin(), temp.value().end(),
                                   std::back_inserter(idList), compID);
                } else {
                    std::set_intersection(temp2.value().begin(), temp2.value().end(), temp.value().begin(), temp.value().end(),
                                          std::back_inserter(idList), compID);
                }

            }
        }

        std::sort(idList.begin(), idList.end(), compID);
    }

    if (q.notWord != "NULL") {
        optional<vector<pair<string, int>>> temp;
        temp = queryKeyWord(q.notWord);
        if (temp) {
            std::sort(temp.value().begin(), temp.value().end(), compID);

            if (debugMode) {
                cout << endl << "new ids:" << endl;
                printIDList(temp.value());
                cout << endl;
            }

            optional<vector<pair<string, int>>> temp2;
            temp2 = idList;

            idList.clear();
            std::set_difference(temp2.value().begin(), temp2.value().end(), temp.value().begin(), temp.value().end(),
                                std::back_inserter(idList));
        }
    }

    if (q.person != "NULL") {
        std::unordered_map<string, int> m;
        m = personMap[q.person];
        vector<pair<string, int>> temp;
        for (auto& p : m) { temp.push_back(p); }
        std::sort(temp.begin(), temp.end(), compID);

        optional<vector<pair<string, int>>> temp2;
        temp2 = idList;

        idList.clear();
        std::set_intersection(temp2.value().begin(), temp2.value().end(), temp.begin(), temp.end(),
                            std::back_inserter(idList), compID);
    }

    if (q.org != "NULL") {
        std::unordered_map<string, int> m;
        m = orgMap[q.org];
        vector<pair<string, int>> temp;
        for (auto& p : m) { temp.push_back(p); }
        std::sort(temp.begin(), temp.end(), compID);

        optional<vector<pair<string, int>>> temp2;
        temp2 = idList;

        idList.clear();
        std::set_intersection(temp2.value().begin(), temp2.value().end(), temp.begin(), temp.end(),
                            std::back_inserter(idList), compID);
    }

    std::sort(idList.begin(), idList.end(), compID);
    return idList;
}

/**
 * Searches wordIndex for word and outputs
 * all document IDs with that word. Doc IDs
 * are then returned;
 * @param str
 */
optional<vector<pair<string, int>>> search_engine::queryKeyWord(string str) {
    keyWord query;
    query.word = std::move(str);
    stem(query.word);

    optional<keyWord> temp = wordIndex.lookUpKW(query, &compKW);
    optional<vector<pair<string, int>>> toReturn;

    if (temp && !temp->idVect.empty()) {
        toReturn = temp->idVect;
        return toReturn;
    }

    return {};
}

///Print Functions
/**
 * prints ID list
 * @param list
 */
void search_engine::printIDList(const vector<pair<string, int>> &list) {
    if (list.empty()) {
        cout << "Your query did not match any articles." << endl;
    } else {
        cout << "Your query has returned " << list.size() << " article";
        (list.size() == 1) ? cout << "." << endl : cout << "s." << endl;

        int i = 1;
        for (auto &id: list) {
            //Fetch Document
            rapidjson::Document doc;
            doc.Parse(docMap[id.first].c_str());

            //Print header
            cout << "-----" << "Document ";
            if (i / 10 == 0) cout << " "; //implement space system maybe?
            cout << i << "-----" << endl;
            cout << "ID:             " << id.first << endl << endl;

            //Article Info
            cout << "Title:          " << doc["title"].GetString() << endl;

            cout << "Author:         ";
            if ((doc["author"].GetString()[0] == '\0')) cout << "No author listed.";
            else cout << doc["author"].GetString();
            cout << endl;

            cout << "Date Published: " << doc["published"].GetString() << endl;

            cout << "Publication:    " << doc["thread"]["site"].GetString() << endl;
            cout << endl;

            if (i == 15) break;

            i++;
        }
    }
}

/**
 * prints document text
 * @param i
 */
void search_engine::printDocText(int i) {
    cout << endl << endl;
    if (curSearch.empty()) {
        cout << "No articles currently available." << endl;
    } else if (i == -2) {
        cout << "Returning to query." << endl;
    } else if (i >= curSearch.size() || i <= -1) {
        cout << "Invalid index entered." << endl;
    } else {
        string id = curSearch[i].first;

        rapidjson::Document doc;

        doc.Parse(docMap[id].c_str());

        cout << doc["text"].GetString() << endl;
    }
}

/**
 * prints query information
 * @param q
 */
void search_engine::printQuery(rawQuery q) {
    cout << endl << "Parsed query" << endl;

    if (q.isOr) cout << "Or word(s): "; else cout << "And word(s): ";
    for(int i = 0; i < q.baseWords.size(); i++) {
        cout << q.baseWords[i] << " ";
    }
    cout << endl;

    cout << "Not word: " << q.notWord << endl;
    cout << "Person: " << q.person << endl;
    cout << "Organization: " << q.org << endl;
}

/**
 * prints map
 * @param m
 */
void search_engine::print_map(std::unordered_map<string, std::unordered_map<string, int>> const &m) {
    for (auto const &entity: m) {
        std::cout << entity.first << ": " << endl;
        for (auto const &id: entity.second) {
            std::cout << "ids: " << id.first << " | ";
        }
        cout << endl;
    }
}

///Functors
/**
 * Compares strings a and b.
 * Returns num that is < 0 if b comes last alphabetically. (b is left of a.)
 * Returns num that is > 0 if b comes first alphabetically. (b is right of a.)
 * @param a
 * @param b
 * @return
 */
int search_engine::compStr(const string& a, const string& b) {
    return a.compare(b);
}

/**
 * Compares keyWord.word a and keyWord.word b.
 * Returns num that is < 0 if b comes last alphabetically. (b is left of a.)
 * Returns num that is > 0 if b comes first alphabetically. (b is right of a.)
 * @param a
 * @param b
 * @return
 */
int search_engine::compKW(const keyWord &a, const keyWord &b) {
    return a.word.compare(b.word);
}

/**
 * Compares a.first and b.first.
 * Returns num that is < 0 if b comes last alphabetically. (b is left of a.)
 * Returns num that is > 0 if b comes first alphabetically. (b is right of a.)
 * @param a
 * @param b
 * @return
 */
int search_engine::compID(const pair<string, int> &a, const pair<string, int> &b) {
    int result = (a.first).compare(b.first);
    return (result < 0);
}

/**
 * Compares a.second and b.second.
 * Returns num that is < 0 if b comes last alphabetically. (b is left of a.)
 * Returns num that is > 0 if b comes first alphabetically. (b is right of a.)
 * @param a
 * @param b
 * @return
 */
int search_engine::compUses(const pair<string, int> &a, const pair<string, int> &b) {
    return a.second < b.second;
}

///Operator overloads

/**
 * Outputs keyWord.word when
 * input operator is used on keyWord.
 * @param os
 * @param kw
 * @return
 */
std::ostream &operator<<(std::ostream & os, const keyWord & kw) {
    if (kw.word.empty()) {
        os << "[EMPTY]";
    } else {
        os << kw.word << " [" << kw.idVect.size() << "]";
    }
    cout << endl;
    return os;
}



