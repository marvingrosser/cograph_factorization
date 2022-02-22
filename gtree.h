/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gtree.h
 * Author: marvin
 *
 * Created on November 1, 2021, 2:12 PM
 */

#ifndef GTREE_H
#define GTREE_H
#include "vertice.h"
#include <vector>
#include <string.h>
#define DATA_SIZE sizeof(unsigned long long)
class gtree {
public:
    unsigned int getId();
    void setId(unsigned int id);
    vector<unsigned int> getKnuthTuple(unsigned int depth);
    vector<vector<gtree*>> getFactors();
    void writeInDepthDict(vector<vector<gtree*>> *depthdict);
    gtree();
    /**
     * Construct Cotree from graph
     * @param g
     */
    gtree(graph* g);
    /**
     * Construct cotree from graph and pass inversions
     * @param g
     * @param component
     * @param state
     */
    gtree(graph* g, unsigned long long* component, bool state, unsigned int* pdepth, vector<vector<gtree*>> *depthdict);
    gtree(bool state);
    gtree(const gtree& orig);
    vector<gtree*> getChilds();
    /**
     * Construct String representing the graph
     * @return 
     */
    string get_string();
    /**
     * Construct String representing the graph per node
     * @param intendation  
     * @param isLast
     * @return 
     */
    string get_string(string intendation, bool isLast);
    /**
     * Returns state 
     * @return 
     */
    bool getState();
    /**
     * Sets state
     * @param state
     */
    void setState(bool state);
    /**
     * adds Child to Childs
     * @param child
     */
    void addChild(gtree * child);
    /**
     * returns child with certain indeces
     * @param i
     * @return 
     */
    gtree* getChild(unsigned short i);
    virtual ~gtree();
private:
    unsigned int id;
    unsigned int* depth;
    bool state; 
    vector<gtree*> childs;
    vector<vector<gtree*>> depthdict;
};

#endif /* GTREE_H */

