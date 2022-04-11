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
#include <iterator>
#define DATA_SIZE sizeof(unsigned long long)

class cotree {
public:
    
    void setFoundK(unsigned int k);
    unsigned int getFoundK();
    
    int findInMultisetVector(vector< map<unsigned int,unsigned int>> vec, map<unsigned int,unsigned int> ms);
    /**
     * set Multiplicity of the primeTuple found (id multiplicity)
     * @param m multiplicity
     */
    void setMultiplicity(unsigned int m);
    /**
     * set Multiplicity of the primeTuple found
     * @return multiplicity
     */
    unsigned int getMultiplicity();
    /**
     * get per depth assigned isomorphy id
     * @return id
     */
    unsigned int getId();
    /**
     * set per depth assigned isomorphy id
     * @param id 
     */
    void setId(unsigned int id);
    /**
     * Calculates the Knuth-Tuple (childs) for this vertice as multiset represented as map.
     * Children with depth above or equal to argument depth wont be considered  
     * @param depth Children with depth above or equal to wont be considered  
     * @return multiset represented trough a map
     */
    map<unsigned int,unsigned int> getKnuthTuple(unsigned int depth);
    /**
     * Node will write itself in the corresponding depthdict, considering its own depth
     * @param depthdict cotree dictionary for depths
     */
    void writeInDepthDict(vector<vector<cotree*>> *depthdict);
    /**
     * Counts number of childs
     * @return number of childs
     */
    unsigned int getChildNum();
    /**
     * Constructor
     */
    cotree();
    /**
     * Construct with given state
     * @param state which the node should have
     */
    cotree(bool state);
    /**
     * Construct fully connected graph with k vertices 
     * @param k number vertices
     * @param id the node should have
     * @param state the node should have
     */
    cotree(unsigned int k,unsigned int id, bool state);
    /**
     * Construct cotree from given cotree, but just to a certain level
     * @param copy the cotree to copy
     * @param depthtogo the cotree to copy
     */
    cotree(cotree* copy, unsigned int depthtogo);
    /**
     * Construct cotree from given cotree, but just to a certain level, while considering the primeCotree found on this level
     * @param copy the cotree to copy
     * @param depthtogo the cotree to copy
     * @param primeTuple the primeTuple found on that depth
     */
    cotree(cotree* copy, unsigned int depthtogo,map<unsigned int, unsigned int> primeTuple, unsigned int depth);
    

    /**
     * Construct Cotree from graph
     * @param g
     */
    cotree(graph* g, vector<vector<cotree*>> *depthdict);
    /**
     * Construct cotree from graph and pass inversions
     * @param g
     * @param component
     * @param state
     */
    cotree(graph* g, unsigned long long* component, bool state, unsigned int* pdepth, vector<vector<cotree*>> *depthdict);
    cotree(const cotree& orig);
    /**
     * Get children of this node
     * @return 
     */
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
    /**
     * Counts number of childs with depth below cdepth
     * @param cdepth
     * @return 
     */
    unsigned int getChildNum(unsigned int cdepth);
    virtual ~cotree();
    /** 
     * @return Depth intervall from this node
     */
    unsigned int * getDepth();
    /**
    *  Calculates all PrimeFactorizations, order NOT neglected.
    * @param gcd number to factorize
    * @return factorizations
    */
    set<vector<unsigned int>> getPrimeFactorizations(unsigned int gcd);
    /**
     * Calculates prime factorization of given number, order neglected.
     * @param x number to factorize
     * @param i divisor (should be called with 2 if you don't know what you are doing)
     * @param factors factor array, should be empty when calling
     * @return the prime factorization in ascending order 
     */
    vector<unsigned int> getPrimeFactorization(unsigned int x, unsigned int i, vector<unsigned int> factors);
    /**
     * permutate a prime factorizations (every possible order of factors)
     * @param factors factorization
     * @return permutated factorizations
     */
    set<vector<unsigned int>> permutateFactorMultiset(vector<unsigned int> factors);
    /**
     * Calculates factors of this cotree bottom up, while assigning ID's to the nodes.
     * @param depthdict a filled depth-dictionary (from this cotree)
     * @return  (list of factorizations)
     */
    vector<vector<cotree*>> getFactors(vector<vector<cotree*>> depthdict);
private:
        
    /**
     * With a given  prime multiset dividing another one calculate the quotient.
     * for m1 | m2:    calculate k with     k*m1=m2.
     * @param primeMultiset divisor
     * @param multiset dividend
     * @return quotient
     */
    unsigned int getGCDFromPrimeTuple(map<unsigned int,unsigned int> primeMultiset, map<unsigned int, unsigned int> multiset);
    /**
     * Checks if one multiset is divisable by another multiset.
     * 
     * @param divident
     * @param divisor
     * @return true if there exists k in IN with       k*divisor = dividend
     */
    bool isDivisible(map<unsigned int, unsigned int> divident, map<unsigned int, unsigned int> divisor );
    /**
     * Divides an multiset by an integer.
     * @param tuple to be divided
     * @param gcd divisor
     * @return quotient
     */
    map<unsigned int,unsigned int> constructGCDTuple( map<unsigned int,unsigned int> tuple, unsigned int gcd);
   /**
    * Calculate the gcd of a given multiset (knouth-tuple), thats the biggest integer which devides the multiset.
    * @param gcdTuple
    * @return gcd
    */
    unsigned int gcdTuple(map<unsigned int,unsigned int> gcdTuple);

    /**
     * Construct children from given graph and connected components. 
     * @param g graph
     * @param components connected components
     * @param depthdict depth dictionary
     */
    void constructChildren(graph * g, vector<unsigned long long*> * components,vector<vector<cotree*>> *depthdict );
    /**
     * Isomorphy containing ID per depth-layer
     */
    unsigned int id;
    /**
     * Multiplicity of this ID, e.g. if this Node is splitted and if so in how many parts
     */
    unsigned int ids_multiplicity;
    
    unsigned int found_k;
    /**
     * Depth interval (two numbers [from, to]) this node is on.
     * If this Interval contains more than one number, this node is representing multiple Nodes
     * to assure unambiguous depth.
     */
    unsigned int* depth;
    /**
     * The state of the node representing the connectedness all leaves having this as smallest common ancestor.
     */
    bool state;
    /**
     *Array of children this node has.
     */
    vector<cotree*> childs;
};

#endif /* GTREE_H */

