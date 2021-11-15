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
#include <string.h>
#include <pthread.h>
#include <vector>
using namespace std;
using std::string;

struct GraphBinary;
struct PGraph{
    vector<vertice*> verts;
};

class graph {
public:
    
    graph(vector<vertice*> g);
    graph();
    
    /**
     * New Graph from File
     * @param path filepath (local)
     */
    graph(string path);
    
    graph(const graph& orig);
    
    virtual ~graph();
    /**
     * Returns String with the Data represented in Ascii-Visualized Data
     * @return 
     */
    string get_string();
    graph invert();
    vector<vector<vertice*>> getConnected();
    graph(vector<vertice*> vert, unsigned short numberVerts);

    
private:
    
    void printPGraph(vector<vertice*> g);
    void searchAllConnected(vertice *vert, vector<vertice*> *g, bool invert);
    
    
    
    void constructFromBinary(GraphBinary data);
    /**
     * Counts binary Ones on Char-Array (binary Data of Char array)
     * @param binary the binary data in Char array 
     * @return number of ones in Chararray
     */
    unsigned int countBinaryOnes(char* binary);
    /**
     * Counts binaray ones on Char in O(m) with m being the number of ones
     * @param binary the binary data as CHar array
     * @return number of ones in Char
     */
    unsigned int countBinaryOnes(char binary);
    /**
     * Returns the State of the bit on the num place in the Char (num>7 --> false)
     * @param num   Index of the bit in the Char
     * @param byte  the binary data in Char
     * @return the corrosponding boolean value
     */
    bool getBitByNum(short num, char byte);
    /**
     * Calculates the fast Gaussian sum 
     * @param n
     * @return 
     */
    unsigned int gaussianSum(unsigned short n);
    
    //Array of actual hold Vertices in the Graph
    vertice* vertices;
    //array of pointers pointing to actual vertices, if the graph has no actual data, but operates on other graphs (eg. it's subgraph)
    vector<vertice*> verticePointers;
    //at the moment senseless
    unsigned int numberEdges;
    //Number of Vertices saved in "vertices" 
    unsigned short numberVertices; 
    

};

#endif /* GRAPH_H */

