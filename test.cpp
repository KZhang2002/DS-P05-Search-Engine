//
// Created by Kenny on 4/15/2022.
//
#include "catch.hpp"
#include "rapidjson/document.h"
#include "avlTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

TEST_CASE( "avlTree Testing", "[avlTree]") {

    SECTION("Insertion/Rotation Testing") {
        //Testing rotateWRChild
        avlTree<int> spronkus;
        spronkus.insert(3);
        spronkus.insert(2);
        spronkus.insert(4);
        spronkus.insert(5);
        spronkus.print2D();
        spronkus.insert(6);
        cout << "Spronkus before: " << endl;
        spronkus.print2D();
        spronkus.deleteNode(4);
        cout << "Spronkus after: " << endl;
        spronkus.print2D();

        //Testing rotateWLChild
        avlTree<int> springus;
        springus.insert(3);
        springus.insert(2);
        springus.insert(4);
        springus.insert(1);
        springus.print2D();
        springus.insert(0);
        cout << "Springus before: " << endl;
        springus.print2D();
        springus.deleteNode(2);
        cout << "Springus after: " << endl;
        springus.print2D();

        //Testing doubleWRChild
        avlTree<int> sprungus;
        sprungus.insert(3);
        sprungus.insert(6);
        sprungus.insert(2);
        sprungus.insert(5);
        sprungus.print2D();
        sprungus.insert(4);
        cout << "Sprungus before: " << endl;
        sprungus.print2D();
        sprungus.deleteNode(2);
        cout << "Sprungus after: " << endl;
        sprungus.print2D();

        //Testing doubleWLChild
        avlTree<int> sprinkus;
        sprinkus.insert(3);
        sprinkus.insert(0);
        sprinkus.insert(4);
        sprinkus.insert(1);
        sprinkus.print2D();
        sprinkus.insert(2);
        cout << "Sprinkus before: " << endl;
        sprinkus.print2D();
        sprinkus.deleteNode(4);
        cout << "Sprinkus after: " << endl;
        sprinkus.print2D();

        //Testing all rotations
        avlTree<int> ultTest;
        ultTest.insert(50);
        ultTest.insert(80);
        ultTest.insert(70);
        ultTest.insert(85);
        ultTest.insert(90);
        ultTest.insert(68);
        ultTest.insert(21);
        ultTest.insert(23);
        ultTest.insert(25);
        ultTest.insert(24);
        ultTest.insert(67);
        cout << "UltTest" << endl;
        ultTest.print2D();
    }

    /*SECTION("RapidJson Testing") {
        ///Based off christian's code
        // declare the document object
        rapidjson::Document doc;

        // initialize the input file
        ifstream streamy("C:/Users/kenne/CLionProjects/Data_Structures/New_Code/22s-final-project-kenny-zhang/data");

        cout << streamy.is_open() << endl;

        // put the whole file's data into fileText
        string fileText;
        string temp;
        while (getline(streamy, temp)) { fileText += temp; }
        streamy.close();

        //cout << fileText << endl;

        // call parse_folder on the string
        doc.Parse(fileText.c_str());
        // make sure the parsing worked
        cout << doc.HasMember("entities") << endl;
        if (doc.IsObject()) cout << "ITS AN OBJECT" << endl << endl;

        //* Getting the values of a string object


        // check that notArray is an object
        //doc["metadata"]["notArray"].IsObject();
        // get the value of notArray in the form of a String
        *//*string notArr = doc["metadata"]["notArray"].GetString();
        cout << "notArr: " << notArr << endl << endl;*//*


        //* Getting the values inside an array of string objects


        // check that Array is an object
        doc["entities"]["organizations"].IsObject();
        // check that Array is an array
        doc["entities"]["organizations"].IsArray();
        // loop over all the values of array
        for (auto &v: doc["entities"]["organizations"].GetArray()) {
            cout << "name: " << v["name"].GetString() << endl;
        }
    }*/
}