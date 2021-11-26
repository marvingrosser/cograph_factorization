/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vertice.cpp
 * Author: marvin
 * 
 * Created on October 27, 2021, 11:56 AM
 */

#include "vertice.h"
graph* vertice::getGraph(){
    return this->g;
}
void vertice::visit(){
    this->visited =true;
}
bool vertice::isVisited(){
    return this->visited;
}

void vertice::unvisit(){
    this->visited=false;
}


vertice::vertice(int num) {
    this->num =num;
    this->visited = false;
}
vertice::vertice(){
    this->num = 0;
this->visited = false;}

void vertice::setNum(int num){
    this->num = num;
}

string vertice::to_string(){
    return std::to_string(this->num);
}


string vertice::out_to_string(){
    string outs = "";
    for(int i=0 ; i < this->g->getSize();i++ ){
        if((this->out[i/8] >> (7 - i % 8))%2 ){
            outs.append("\t --> \t");
            outs.append(this->g->getVerticeByNumber(i)->to_string());
            outs.append("\n");
        }
    }
    
    return outs;
}
int vertice::getNum(){
    return this->num;
}



vertice::~vertice() {
}
void vertice::setGraph(graph* g){
    this->g = g;
}

void vertice::initOut(unsigned short number){
    this->out = (char *)calloc(number/8,sizeof(char));
    this->out[0] = (char)0;
    
}
void vertice::setOneInOut(unsigned short index){
    this->out[index/8] |= ((unsigned char) 1  << (7 - index % 8))  ;
}

char* vertice::getConnections(){
    return this->out;
}