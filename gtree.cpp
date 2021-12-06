/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gtree.cpp
 * Author: marvin
 * 
 * Created on November 1, 2021, 2:12 PM
 */

#include "gtree.h"
string gtree::get_string(){
    return this->get_string("",true);
}
string gtree::get_string(string intendation, bool isLast){
    string me_s = intendation;
    
    if(isLast){
        me_s.append("└─");
        intendation.append("  ");
    }else{
        me_s.append("├─");
        intendation.append("| ");
    }
    me_s.append(this->state? "1\n": "0\n");
    for(unsigned short i = 0; i < this->childs.size(); i++){
        me_s.append(this->childs.at(i)->get_string(intendation,(this->childs.size()-1 == i) ));
    }
    return me_s;
    
}
gtree::gtree() {
}

gtree::gtree(const gtree& orig) {
}
gtree::gtree(graph* g){
    unsigned short size = g->getSize();
    unsigned long long* lookAtAll = (unsigned long long *)calloc( size/ DATA_SIZE,DATA_SIZE);
    g->verticeInversion(lookAtAll, size);
    vector<unsigned long long*> components= g->getConnections(false,lookAtAll);
    
    if(components.size() == 1){
        this->state = true;
        components= g->getConnections(true,lookAtAll);
    }else{
        this->state = false;
    }
    for(unsigned long long* component: components){
        gtree* child = new gtree(g, component, !this->state);
        this->childs.push_back(child);
    }
    
}
gtree::gtree(graph* g, unsigned long long* component, bool state){
    this->state = state;
    vector<unsigned long long*> components = g->getConnections(state, component);
    if(components.size() > 1){
        for(unsigned long long* thiscomponent: components){
            gtree* child = new gtree(g, thiscomponent, !this->state);
            this->childs.push_back(child);
        }
    }
}
gtree::~gtree() {
}
gtree::gtree(bool state){
    this->state = state;
}

vector<gtree*> gtree::getChilds(){
    return childs;
}

bool gtree::getState(){
    return this->state;
}
void gtree::setState(bool state){
    this->state = state;
}
void gtree::addChild(gtree* child){
    this->childs.push_back(child);
}

gtree* gtree::getChild(unsigned short i){
    return this->childs.at(i);
}