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

#include "../headers/cograph.h"
void graph::verticeUnion(unsigned long long* dest, unsigned long long* other, unsigned short size){

    for(int i = 0; i < (int)(((int)size)/((int)DATA_SIZE)) + 1 ; i++){
        dest[i] |= other[i];
    }
}
void graph::verticeInverseUnion(unsigned long long* dest, unsigned long long* other, unsigned short size){
    for(int i = 0; i <  (int)(((int)size)/((int)DATA_SIZE)) + 1 ; i++){
        dest[i] |= ~ other[i];
    }
}

void graph::verticeInversion(unsigned long long* dest, unsigned short size){
    for(int i = 0; i < (int)(((int)size)/((int)DATA_SIZE)) + 1; i++){
        dest[i] = ~dest[i];
    }
}


void graph::verticeInverseXOR(unsigned long long * dest, unsigned long long * other, unsigned short size){
    for(int i = 0; i < (int)(((int)size)/((int)DATA_SIZE)) + 1; i++){
        dest[i] ^= ~other[i];
    }
}

vector<unsigned long long*> graph::getConnections(bool invert, unsigned long long* lookAt){
    
    unsigned short numVerts = this->verticePointers.size(); //number of verts in the graph

    unsigned long long * visited = (unsigned long long*)calloc((int) (((int) numVerts)/((int)DATA_SIZE)),DATA_SIZE); //stores visited vertices
    
    verticeInverseUnion(visited, lookAt, numVerts); //fill visited with stuff we do not want to visit
    vector<vertice*> verticePointers = this->verticePointers;
    vector<unsigned long long*> components;


    for(int i=0; i < numVerts ; i++ ){
        if( ((unsigned long long)visited[(int)(((int) i)/ ((int)DATA_SIZE))] >> ((int)DATA_SIZE - 1 - (int)(((int)i) % ((int)DATA_SIZE)))) % 2 == 0){ //is the vertex[i] not visited? 
  
            unsigned long long * component = (unsigned long long*)calloc((int) (((int) numVerts)/((int)DATA_SIZE)),DATA_SIZE); //component data
            
            verticeInverseUnion(component, lookAt,numVerts); //All Vertices not to look at will be 1    (*)
            
            vertice* current = verticePointers.at(i); // take current vertice
            
            searchAllConnected(current, component , invert,verticePointers); //create component
            
            verticeInverseXOR(component, lookAt,numVerts); //reverse step (*)
            
            verticeUnion(visited,component, numVerts); // write the component to the visited
            
            components.push_back(component); //add the component to our components vector
        }
        
    }
    
    return components;
}
void graph::searchAllConnected(vertice* vert, unsigned long long* binary,bool invert,vector<vertice*> verticePointers){
    
    unsigned short numVerts= verticePointers.size(); //graph size
    
    unsigned short numOfThisVert = vert->getNum(); //takes the index of this vertex
    
    unsigned long long disjunion[(int) (((int) numVerts)/((int)DATA_SIZE)) + 1]; //variable where we store wich vertices we have to visit from this vertex
    
    unsigned long long * realConnected = vert->getConnections(); //take the bitrepresentation for connected vertices
    
    unsigned long long connectedCopy[(int) (((int) numVerts)/((int)DATA_SIZE)) +1];
    
    for(int i = 0; i < (int) (((int) numVerts)/((int)DATA_SIZE)) + 1;i++){ //loop over our Windows of the Bitrepr of connected vertices
        connectedCopy[i] = (invert)? ~realConnected[i]: realConnected[i]; //invert if that shit has to be inverted 
        disjunion[i] = connectedCopy[i] ^ (binary[i] & connectedCopy[i]); //calculates the vertices we haveent visited but can visit from this vertex
        binary[i] |= connectedCopy[i]; // adds the vertices that will be visited from this vertex to the visited variable
    }
    
    binary[(int) (((int) numOfThisVert)/((int)DATA_SIZE))] |=  ((unsigned long long)1) << ((int)DATA_SIZE) - 1  - (int)(((int)numOfThisVert) % ((int)DATA_SIZE));  //adds the vertex itseklf to the visited
    
    if(disjunion){ //do the loop only if there are vertices to visit
        
        for(int i = 0; i < numVerts; i++){//könnte man nachdem nur noch nullen kommen + mod DATA_SIZE - 1  ^-1 skippen
            
            unsigned long long currentVertice = disjunion[(int)(((int) i)/((int) DATA_SIZE))] >> ((int) DATA_SIZE) - 1 - (int)(((int) i) % ((int) DATA_SIZE)); //vertex(i) to index DATA_SIZE - 1 
            
            if( currentVertice % 2 == 1 && i != numOfThisVert){ //should we visit this vertex?
                
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

unsigned int graph::countBinaryOnes(unsigned long long binary){
    unsigned int count;
    for(count = 0; binary; count++ ){
        binary &= binary - 1;
    }
    return count;
}
unsigned int graph::countBinaryOnes(unsigned long long* binary){
    unsigned int count = 0;
    unsigned int  n = this->numberVertices;
    for(unsigned int i=0; i < ((int)((int)(n*n))/((int)DATA_SIZE));i++){
        count += this->countBinaryOnes(binary[i]);
    }
    return count;
}
bool graph::getBitByNum(short num, unsigned long long data){
    return (data >> DATA_SIZE - num - 1 ) & 1;
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
        //std::cout << i/data.number << std::endl;
        //std::cout <<(int)(((int)i) % ((int)DATA_SIZE)) << std::endl;
        if(this->getBitByNum((int)(((int)i) % ((int)DATA_SIZE)) ,data.edges[(int)(((int)i)/((int)DATA_SIZE))])){
            //std::cout << "1 at num = " << (int)((int)i/(int)data.number) <<" : "<< i % data.number<< std::endl;
            
            this->vertices[(int)((int)i/(int)data.number)].setOneInOut(i % data.number);
        }
    }
    
}



unsigned short graph::getSize(){
    return (unsigned short) this->verticePointers.size();
}

vertice * graph::getVerticeByNumber(unsigned short num){
    return this->verticePointers.at(num);
}