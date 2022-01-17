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
    int compareOrdinalitys(vector<unsigned int> one, vector<unsigned int> two);
    unsigned int giveIdsFromOrdinality(vector<vector<unsigned int>> ordinality, vector<gtree*> subtrees, unsigned int lastid);
    vector<unsigned int> getOrdinality(gtree* g);
    void makeIdsWithRBD(vector<vector<gtree*>> rbd);
    void setId(unsigned int newId);
    unsigned int getId();
    void createIds(vector<vector<gtree*>> * rootsbydepth);
    gtree();
    /**
     * Construct Cotree from graph
     * @param g
     */
    void addtoRBD(unsigned int depth, gtree * child ,vector<vector<gtree*>> *   rootsbydepth);
    gtree(graph* g);
    /**
     * Construct cotree from graph and pass inversions
     * @param g
     * @param component
     * @param state
     */
    gtree(graph* g, unsigned long long* component, bool state, unsigned int * id, vector<vector<gtree*>> * rootsbydepth);
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
    bool state; 
    vector<gtree*> childs;
    
};

#endif /* GTREE_H */

