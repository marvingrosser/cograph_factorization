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
#include <set>
#include <algorithm>
#include <map>
#define DATA_SIZE sizeof(unsigned long long)

class gtree {
public:
    unsigned int getId();
    void setId(unsigned int id);
    
    map<unsigned int,unsigned int> getKnuthTuple(unsigned int depth, bool minimal);
    vector<vector<gtree>> getFactors(vector<vector<gtree*>> *depthdict, vector<vector<gtree>> factors);
    void writeInDepthDict(vector<vector<gtree*>> *depthdict);
    gtree();
    /**
     * Construct Cotree from graph
     * @param g
     */
    gtree(graph* g, vector<vector<gtree*>> depthdict);
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
    unsigned int * getDepth();
private:
    unsigned int getGCDFromPrimeTuple(map<unsigned int,unsigned int> primeMultiset, map<unsigned int, unsigned int> multiset);
    bool isDivisible(map<unsigned int, unsigned int> divident, map<unsigned int, unsigned int> divisor );
     map<unsigned int,unsigned int> constructLCDTUple( map<unsigned int,unsigned int> tuple, unsigned int gcd);
    unsigned int lcd(unsigned int a, unsigned int b);
    unsigned int gcdTuple(map<unsigned int,unsigned int> gcdTuple);
    int findInMultisetVector(vector< map<unsigned int,unsigned int>> vec,  map<unsigned int,unsigned int> ms);
    void createIndices(vector<vector<gtree*>> depthdict);
    void constructChildren(graph * g, vector<unsigned long long*> * components,vector<vector<gtree*>> *depthdict );
    unsigned int id;
    unsigned int* depth;
    bool state; 
    vector<gtree*> childs;
};

#endif /* GTREE_H */

