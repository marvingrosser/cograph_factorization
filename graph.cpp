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
void graph::searchAllConnected(vertice* vert, char* binary,bool invert){
    *binary |= *vert->getConnections();
    char vertbinary[sizeof(*vert->getConnections())/sizeof(char)];
    *vertbinary = *vert->getConnections();
    unsigned int index = 0;
    for(int i = index; vertbinary; i = index ){
        vertbinary[i/8] &= vertbinary[i/8] - 1;
        index = 0;
    }

}
graph::graph(){}
graph::graph(vector<vertice*> verts){
    this->numberVertices = verts.size();
    this->verticePointers= *new vector<vertice*>(verts.begin(),verts.end());
    //std::cout << "PF"<<  this->get_string() << std::endl;
}

graph graph::invert(){
    return *new graph();
}



graph::graph(vector<vertice*> verts, unsigned short numberVerts){
    this->numberVertices = numberVerts;
    this->verticePointers = verts;
}

string graph::get_string(){
    string graphAsString="Vertices:\n";
    
    for(int v=0; v < this->verticePointers.size(); v++){
        graphAsString.append("\n{");
        graphAsString.append(this->verticePointers.at(v)->to_string());
        graphAsString.append("}\n");
        graphAsString.append(this->verticePointers.at(v)->out_to_string());
        
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
    //std::cout << "\n" << this->numberEdges << std::endl;
    this->vertices = new vertice[data.number]();
    this->verticePointers = *new vector<vertice*>;
    
    
    for(int i=0; i < this->numberVertices ;i++ ){
        this->vertices[i] = * new vertice(i);
        this->vertices[i].initOut(this->numberVertices - 1);
        this->vertices[i].setGraph(this);
        this->verticePointers.push_back(&vertices[i]);
        
    }
    
    
    unsigned int edgecounter = 0;
    for(int i = 0; i < data.number * data.number;i++){
        
        if(this->getBitByNum((i % 8),data.edges[i/8])){
            //std::cout << data.edges[i/8]+0 << std::endl;
            
            this->vertices[i/data.number].setOneInOut(i % data.number);
        }
    }
    
}

unsigned int graph::gaussianSum(unsigned short n){
    return (n*(n+1)) >> 1;
}

unsigned short graph::getSize(){
    return (unsigned short) this->verticePointers.size();
}

vertice * graph::getVerticeByNumber(unsigned short num){
    return this->verticePointers.at(num);
}