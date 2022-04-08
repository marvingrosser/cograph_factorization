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



vertice::vertice(int num) {
    this->num =num;

}
vertice::vertice(){
    this->num = 0;
}

void vertice::setNum(int num){
    this->num = num;
}

string vertice::to_string(){
    return std::to_string(this->num);
}


string vertice::out_to_string(){
    string outs = "";
    for(int i=0 ; i < this->g->getSize();i++ ){
        if((this->out[i/DATA_SIZE] >> (DATA_SIZE - 1 - i % DATA_SIZE)) % 2 ){
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
    this->out = (unsigned long long *)calloc(number/DATA_SIZE,DATA_SIZE);
    this->out[0] = (unsigned long long)0;
    
}
void vertice::setOneInOut(unsigned short index){
    this->out[index/DATA_SIZE] |= ((unsigned long long) 1  << (DATA_SIZE- 1 - index % DATA_SIZE))  ;
}

unsigned long long* vertice::getConnections(){
    return this->out;
}