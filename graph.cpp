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
void graph::verticeUnion(char* dest, char* other, unsigned short size){
    for(int i = 0; i < size/8 + 1; i++){
        dest[i] |= other[i];
    }
}
void graph::verticeInverseUnion(char* dest, char* other, unsigned short size){
    for(int i = 0; i < size/8 + 1; i++){
        dest[i] |= ~ other[i];
    }
}

void graph::verticeInversion(char* dest, unsigned short size){
    for(int i = 0; i < size/8 + 1; i++){
        dest[i] = ~dest[i];
    }
}


void graph::verticeInverseXOR(char * dest, char * other, unsigned short size){
    for(int i = 0; i < size/8 + 1; i++){
        dest[i] ^= ~other[i];
    }
}

vector<char*> graph::getConnections(bool invert, char* lookAt){
    
    unsigned short numVerts = this->verticePointers.size(); //number of verts in the graph

    char * visited = (char*)calloc(numVerts/8,sizeof(char)); //stores visited vertices
    verticeInverseUnion(visited, lookAt, numVerts);
    vector<char*> components;
    for(int i=0; i < numVerts ; i++ ){
        if( ((unsigned char)visited[i / 8] >> (7 - (i % 8))) % 2 == 0){ //is the vertex[i] not visited? 
  
            char * component = (char*)calloc(numVerts/8,sizeof(char)); //component data
            verticeInverseUnion(component, lookAt,numVerts);
            vertice* current = this->verticePointers.at(i); // take current vertice
            
            searchAllConnected(current, component , invert,this->verticePointers); //create component
            verticeInverseXOR(component, lookAt,numVerts);
            verticeUnion(visited,component, numVerts); // write the component to the visited
            
            components.push_back(component); //add the component to our components vector
        }
        
    }
    return components;
}
void graph::searchAllConnected(vertice* vert, char* binary,bool invert,vector<vertice*> verticePointers){
    unsigned short numVerts= verticePointers.size(); //
    unsigned short numOfThisVert = vert->getNum(); //takes the index of this vertex
    char disjunion[numVerts/8+1]; //variable where we store wich vertices we have to visit from this vertex
    char * realConnected = vert->getConnections(); //take the bitrepresentation for connected vertices
    char connectedCopy[numVerts/8+1];
    for(int i = 0; i < numVerts/8 + 1;i++){ //loop over our Windows of the Bitrepr of connected vertices
        connectedCopy[i] = (invert)? ~realConnected[i]: realConnected[i]; //invert if that shit has to be inverted 
        disjunion[i] = connectedCopy[i] ^ (binary[i] & connectedCopy[i]); //calculates the vertices we haveent visited but can visit from this vertex
        binary[i] |= connectedCopy[i]; // adds the vertices that will be visited from this vertex to the visited variable
    }
    binary[numOfThisVert/8] |=  ((char)1) << 7 - (numOfThisVert % 8);  //adds the vertex itseklf to the visited
    if(disjunion){ //do the loop only if there are vertices to visit
        for(int i = 0; i < numVerts; i++){//könnte man nachdem nur noch nullen kommen + mod 7 ^-1 skippen
            unsigned char wtf = disjunion[i/8] >> 7-(i % 8); //vertex(i) to index 7
            if( wtf % 2 == 1 && i!=numOfThisVert){ //should we visit this vertex?
                searchAllConnected(verticePointers.at(i), binary,invert, verticePointers);
            }
        }
    }
}
graph::graph(){}








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



unsigned short graph::getSize(){
    return (unsigned short) this->verticePointers.size();
}

vertice * graph::getVerticeByNumber(unsigned short num){
    return this->verticePointers.at(num);
}