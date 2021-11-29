
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
#include <vector>
using namespace std;
using std::string;
class vertice;
struct GraphBinary;


class graph {
public:
    

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
    
    


    unsigned short getSize();
    /**
     * Returns vertice with corrosponding index
     * @param num index
     * @return vertex[num]
     */
    vertice * getVerticeByNumber(unsigned short num);
    /**
     * Searches for all components inside the graph
     * @param invert Should the graph be inverted
     * @param lookAt which Verts should be looked at?
     * @return vector of binary representation of components
     */
    vector<char*> getConnections(bool invert,char* lookAt);
    /**
     * Inverts the given Vertice-Outputs on the Binary Data
     * @param dest  Given input
     * @param size Graph size
     */
    void verticeInversion(char* dest, unsigned short size);
private:
    
    /**
     * Unites the Output of two vertices
     * @param dest vertdata one and in which to store the value
     * @param other vertdata two
     * @param size size of the graph (length of the arrays)
     */
    void verticeUnion(char* dest, char* other, unsigned short size);
    /**
     * Unites the Output of two vertices where the second one is inverted before
     * @param dest vertdata one and in which to store the value
     * @param other vertdata two (which will get inverted before the union)
     * @param size size of the graph (length of the arrays)
     */
    void verticeInverseUnion(char* dest, char* other, unsigned short size);
    /**
     * XOR's the Output of two vertices where the second one is inverted before
     * @param dest vertdata one and in which to store the value
     * @param other vertdata two (which will get inverted before the XOR)
     * @param size size of the graph (length of the arrays)
     */
    void verticeInverseXOR(char * dest, char * other, unsigned short size);
    
    

    /**
     * Collects the component in which the Vertice lays
     * @param vert Vertice to look at
     * @param binary Vertices already inside the Component/to ignore
     * @param invert Should the graph be inverted?
     * @param pointers Collection ov verticePointers
     */
    void searchAllConnected(vertice *vert,char* binary, bool invert, vector<vertice*> pointers);
    
    
    
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

