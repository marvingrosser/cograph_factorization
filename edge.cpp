/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   edge.cpp
 * Author: marvin
 * 
 * Created on October 27, 2021, 11:56 AM
 */

#include "edge.h"
#include "vertice.h"
string edge::to_string(){
    string str = "";
    str.append(this->from->to_string());
    str.append("\t-->\t");
    str.append(this->to->to_string());
    return str;
}
edge::edge(){};
edge::edge(vertice *from, vertice *to) {
    this->set(from, to);
}
void edge::set(vertice* from, vertice* to){
    this->from = from;
    this->to = to;
}
edge::edge(const edge& orig) {
}

edge::~edge() {
}

