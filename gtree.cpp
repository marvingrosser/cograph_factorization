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
unsigned int gtree::getId(){
    return this->id;
}
void gtree::setId(unsigned int id){
    this->id = id;
}
vector<vector<gtree*>> getFactors(){
    return *new vector<vector<gtree*>>;
}
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
    me_s.append(this->state? "1": "0");
    me_s.append("\t [").append(to_string(this->depth[0])).append(", ").append(to_string(this->depth[1])).append("]").append("\n");
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
    this->depth= new unsigned int[2];
        this->depth[0]=-1;
        this->depth[1]=0;
    for(unsigned long long* component: components){
        unsigned int *cdepth = new unsigned int[2];
        
        gtree* child = new gtree(g, component, !this->state, cdepth,& depthdict);
        
        this->depth[0]= (cdepth[0] + 1 < this->depth[0]? cdepth[0] + 1 : this->depth[0]);
        this->depth[1]= (cdepth[1] + 1 > this->depth[1]? cdepth[1] + 1 : this->depth[1]);
        
        this->childs.push_back(child);
    }
    this->writeInDepthDict(&depthdict);
}
gtree::gtree(graph* g, unsigned long long* component, bool state, unsigned int * pdepth,vector<vector<gtree*>> *depthdict){
    this->state = state;
    vector<unsigned long long*> components = g->getConnections(state, component);
    this->depth= new unsigned int[2];
    this->depth[0]=0;
    this->depth[1]=0;
    if(components.size() > 1){
        this->depth[0]=-1;
        for(unsigned long long* thiscomponent: components){
            unsigned int *cdepth = new unsigned int[2];
            gtree* child = new gtree(g, thiscomponent, !this->state,cdepth, depthdict);
            
            this->depth[0]= (cdepth[0] + 1 < this->depth[0]? cdepth[0] + 1 : this->depth[0]);
            this->depth[1]= (cdepth[1] + 1 > this->depth[1]? cdepth[1] + 1 : this->depth[1]);
            
            this->childs.push_back(child);
        }
    }
        pdepth[0] = this->depth[0];
        pdepth[1] = this->depth[1];
        this->writeInDepthDict(depthdict);
}
void gtree::writeInDepthDict(vector<vector<gtree*> >* depthdict){
    for(unsigned int i = this->depth[0]; i <= this->depth[1];i++){
        if(depthdict->size() < i+1 ){
            depthdict->push_back(* new vector<gtree*>);
        }
        depthdict->at(i).push_back(this);
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