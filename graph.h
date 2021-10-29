/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.h
 * Author: marvin
 *
 * Created on October 25, 2021, 2:32 PM
 */

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "vertice.h"
#include "reader.h"
#include "edge.h"
#include <string.h>

using namespace std;
using std::string;

struct GraphBinary;


class graph {
public:
    graph(string path);
    graph(const graph& orig);
    virtual ~graph();
    string get_string();
private:
    void constructFromBinary(GraphBinary data);
    unsigned int countBinaryOnes(char* binary);
    unsigned int countBinaryOnes(char binary);
    bool getBitByNum(short num, char byte);
    edge* edges;
    vertice* vertices;
    unsigned int numberEdges;
    
    unsigned short numberVertices; 
    

};

#endif /* GRAPH_H */

