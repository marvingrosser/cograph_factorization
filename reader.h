/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reader.h
 * Author: marvin
 *
 * Created on October 25, 2021, 2:33 PM
 */

#ifndef READER_H
#define READER_H
#include <string.h>
#include <fstream>
#include <sstream>

#include "graph.h"
#include <iostream>
using namespace std;
using std::string;

struct GraphBinary{
    int number;
    char * edges;
    char ** edgesPerVertice;
};

class reader {
public:
    reader(string path);
    reader(const reader& orig);
    virtual ~reader();
    GraphBinary getData();
private:
    string readFileToString(string path);
    GraphBinary readBinaryFromFile();
    GraphBinary readBinaryFromGraphFile();
    string path;
    
};

#endif /* READER_H */

