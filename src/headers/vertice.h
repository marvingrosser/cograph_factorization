/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vertice.h
 * Author: marvin
 *
 * Created on October 27, 2021, 11:56 AM
 */

#ifndef VERTICE_H
#define VERTICE_H
#include <string>
#include <vector>
#include "cograph.h"

#define DATA_SIZE sizeof(unsigned long long)*8
class graph;
using namespace std;
using std::vector;
using std::string;
class vertice {
public:
    graph* getGraph();
    /**
     * Sets the graph pointer
     * @param g
     */
    void setGraph(graph * g);
    /**
     * Sets the bit with index to 1
     * @param index
     */
    void setOneInOut(unsigned short index);
    /**
     * Inits Binary data for vertice-output
     * @param number
     */
    void initOut(unsigned short number);
    vertice();
    /**
     * Construct vertice with given number
     * @param num (label)
     */
    vertice(int num);
    virtual ~vertice();
    /**
     * Returns number of vert as string
     * @return 
     */
    string to_string();
    /**
     * returns Connected-vertices as strings
     * @return 
     */
    string out_to_string();
    /**
     * Return Label
     * @return 
     */
    int getNum();
    /**
     * Sets numberlabel
     * @param num
     */
    void setNum(int num);

    /**
     * Returns binary Representation of Connections
     * @return binary repr. as Char-array
     */
    unsigned long long* getConnections();
private:
    /**
     * Label
     */
    int num;
    /**
     * the parent graph
     */
    graph * g;
    /**
     *Connections to other vertices
     */
    unsigned long long * out;

};

#endif /* VERTICE_H */

