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
    void deleteAboveDepthAndDivideChilds(unsigned int depth, unsigned int divisor);
    map<unsigned int,unsigned int> getKnuthTuple(unsigned int depth, bool minimal);
    vector<vector<gtree>> getFactors(vector<vector<gtree*>> *depthdict, vector<vector<gtree>> factors);
    void writeInDepthDict(vector<vector<gtree*>> *depthdict);
    gtree();
    gtree(bool state);
    /**
     * Construct fully connected graph with k vertices 
     * @param k
     *
     */
    gtree(unsigned int k,unsigned int id);
    gtree(vector<gtree*>* children, unsigned int from, unsigned int to, unsigned int * depth, unsigned int id, bool state);
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
    gtree(const gtree& orig);
    gtree(gtree* other);
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
    unsigned int getChildNum(unsigned int depth);
    virtual ~gtree();
    unsigned int * getDepth();
    vector<vector<gtree*>> getFactors();
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
    vector<vector<gtree*>> getFactors(vector<gtree*> heads, unsigned int depth, unsigned int divisor, vector<gtree*>* new_factor);
    vector<gtree*> collectChilds(vector<gtree*> heads, unsigned int depth);
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

