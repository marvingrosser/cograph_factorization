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
    for(vertice* vert: this->out){
        outs.append("\t --> \t");
        outs.append(vert->to_string());
        outs.append("\n");
    }
    
    return outs;
}
int vertice::getNum(){
    return this->num;
}

void vertice::addConnection(vertice* vert){
    this->out.push_back(vert);
}

vertice::~vertice() {
}

vector<vertice*>* vertice::getConnections(){
    return &this->out;
}