/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   graph.cpp
 * Author: marvin
 * 
 * Created on October 25, 2021, 2:32 PM
 */

#include "graph.h"


string graph::get_string(){
    string graphAsString="Vertices:\t { ";
    
    for(int v=0; v < this->numberVertices; v++){
        graphAsString.append(this->vertices[v].to_string());
        
        graphAsString.append(", ");
    }
    graphAsString.append(" }\n\n");
    graphAsString.append("Edges:\n\t");
    for(int e=0; e < this->numberEdges;e++){
        graphAsString.append(this->edges[e].to_string());
        graphAsString.append("\n\t");
    }
    
    return graphAsString;
}
graph::graph(const graph& orig) {
}

graph::~graph() {
}
graph::graph(string path){
    GraphBinary file = (*new reader(path)).getData();
    this->constructFromBinary(file);

}

unsigned int graph::countBinaryOnes(char binary){
    unsigned int count;
    for(count = 0; binary; count++ ){
        binary &= binary - 1;
    }
    return count;
}
unsigned int graph::countBinaryOnes(char* binary){
    unsigned int count = 0;
    unsigned int  n = this->numberVertices;
    for(unsigned int i=0; i < (int)(n*n)/8;i++){
        count += this->countBinaryOnes(binary[i]);
    }
    return count;
}
bool graph::getBitByNum(short num, char byte){
    return (byte << num) & 128;
}
void graph::constructFromBinary(GraphBinary data){
    
    this->numberVertices = (unsigned short)data.number;

    this->numberEdges = (unsigned int) this->countBinaryOnes(data.edges);
    std::cout << "\n" << this->numberEdges << std::endl;
    this->vertices = new vertice[data.number]();
    
    this->edges = new edge[this->numberEdges]();
    
    
    for(int i=0; i < this->numberVertices ;i++ ){
        this->vertices[i] = * new vertice(i);
    }
    
    
    unsigned int edgecounter = 0;
    for(int i = 0; i < data.number * data.number;i++){
        if(this->getBitByNum((i % 8),data.edges[i/8])){
            //std::cout << data.edges[i/8]+0 << std::endl;
            this->edges[edgecounter].set(&vertices[i/data.number],&vertices[i % data.number]);
            edgecounter++;
        }
    }
    
}
