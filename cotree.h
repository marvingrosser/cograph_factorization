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

class cotree {
public:
    unsigned int getId();
    void setId(unsigned int id);
    void deleteAboveDepthAndDivideChilds(unsigned int depth, unsigned int divisor);
    map<unsigned int,unsigned int> getKnuthTuple(unsigned int depth, bool minimal);
    vector<vector<cotree>> getFactors(vector<vector<cotree*>> *depthdict, vector<vector<cotree>> factors);
    void writeInDepthDict(vector<vector<cotree*>> *depthdict);
    cotree();
    cotree(bool state);
    /**
     * Construct fully connected graph with k vertices 
     * @param k
     *
     */
    cotree(unsigned int k,unsigned int id);
    cotree(vector<cotree*>* children, unsigned int from, unsigned int to, unsigned int * depth, unsigned int id, bool state);
    /**
     * Construct Cotree from graph
     * @param g
     */
    cotree(graph* g, vector<vector<cotree*>> depthdict);
    /**
     * Construct cotree from graph and pass inversions
     * @param g
     * @param component
     * @param state
     */
    cotree(graph* g, unsigned long long* component, bool state, unsigned int* pdepth, vector<vector<cotree*>> *depthdict);
    cotree(const cotree& orig);
    cotree(cotree* other);
    vector<cotree*> getChilds();
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
    void addChild(cotree * child);
    /**
     * returns child with certain indeces
     * @param i
     * @return 
     */
    cotree* getChild(unsigned short i);
    unsigned int getChildNum(unsigned int depth);
    virtual ~cotree();
    unsigned int * getDepth();
    vector<vector<cotree*>> getFactors();
    set<vector<unsigned int>> getPrimeFactorizations(unsigned int gcd);
    vector<unsigned int> getPrimeFactorization(unsigned int x, unsigned int i, vector<unsigned int> factors);
    set<vector<unsigned int>> permutateFactorMultiset(vector<unsigned int> factors);
private:
    /**
     * get lexicographic factors for Cotree
     * @param heads
     * @param depth
     * @param divisor
     * @return 
     */
    vector<vector<cotree*>> getFactors(vector<cotree*> heads, unsigned int depth, unsigned int divisor, vector<cotree*>* new_factor);
    vector<cotree*> collectChilds(vector<cotree*> heads, unsigned int depth);
    unsigned int getGCDFromPrimeTuple(map<unsigned int,unsigned int> primeMultiset, map<unsigned int, unsigned int> multiset);
    bool isDivisible(map<unsigned int, unsigned int> divident, map<unsigned int, unsigned int> divisor );
     map<unsigned int,unsigned int> constructLCDTUple( map<unsigned int,unsigned int> tuple, unsigned int gcd);
    unsigned int lcd(unsigned int a, unsigned int b);
    unsigned int gcdTuple(map<unsigned int,unsigned int> gcdTuple);
    int findInMultisetVector(vector< map<unsigned int,unsigned int>> vec,  map<unsigned int,unsigned int> ms);
    void createIndices(vector<vector<cotree*>> depthdict);
    void constructChildren(graph * g, vector<unsigned long long*> * components,vector<vector<cotree*>> *depthdict );
    unsigned int id;
    unsigned int* depth;
    bool state; 
    vector<cotree*> childs;
};

#endif /* GTREE_H */

