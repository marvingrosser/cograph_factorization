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
    me_s.append(this->state? "1:[": "0:[").append(to_string(this->id)).append("]\n");
    for(unsigned short i = 0; i < this->childs.size(); i++){
        me_s.append(this->childs.at(i)->get_string(intendation,(this->childs.size()-1 == i) ));
    }
    return me_s;
    
}
gtree::gtree() {
}
void gtree::setId(unsigned int newId){
    this->id = newId;
}
unsigned int gtree::getId(){
    return this->id;
    
}
vector<unsigned int> gtree::getOrdinality(gtree* g){
    vector<unsigned int> ord;
    for(gtree* child:g->getChilds()){
        ord.push_back(child->getId());
    }
    return ord;
}
unsigned int gtree::giveIdsFromOrdinality(vector<vector<unsigned int> > ordinality, vector<gtree*> subtrees, unsigned int lastid){
    unsigned int highestIndex = lastid;
    if(lastid==0){return 1;}
    for(int i=0; i < ordinality.size(); i++){
        
        unsigned int biggerAs = 0;
        
        for(int j=0; j < ordinality.size();j++){
            
            int compare = gtree::compareOrdinalitys(ordinality[i],ordinality[j]);
            
            biggerAs = biggerAs + (compare==1?1:0);
        }  
        highestIndex = (highestIndex >= lastid + 1 + biggerAs? highestIndex: lastid + 1 + biggerAs);
        subtrees[i]->setId(lastid + 1 + biggerAs);
    }
    return highestIndex;
}
int gtree::compareOrdinalitys(vector<unsigned int> one, vector<unsigned int> two){
    unsigned int i = 0;
    while(i < one.size() && i < two.size()){
        if(one.at(i) > two.at(i)){
            return 1;
        }else if(one.at(i) < two.at(i)){
            return -1;
        }
        
        i++;
    }
    return one.size() > two.size()? 1: (one.size() == two.size()? 0: -1 );

}
void gtree::makeIdsWithRBD(vector<vector<gtree*> > rbd){
    unsigned int lastid = 0;
    vector<vector<vector<unsigned int>>> ordinality;
    unsigned int ordinalityIndex = 0;
    for(vector<gtree*> depthSubtrees:rbd){
        ordinality.push_back(*new vector<vector<unsigned int>>);
        for(gtree* subtreeWithFixedDepth: depthSubtrees){
            ordinality[ordinalityIndex].push_back(gtree::getOrdinality(subtreeWithFixedDepth));
        }
        
        lastid = gtree::giveIdsFromOrdinality(ordinality[ordinalityIndex], depthSubtrees, lastid);
        ordinalityIndex++;
    }
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
    unsigned int * mydepth = (unsigned int *)calloc(components.size(), sizeof(unsigned int));
    unsigned int d_c = 0;
    vector<vector<gtree*>> rbd;
    for(unsigned long long* component: components){  
        gtree* child = new gtree(g, component, !this->state, &mydepth[d_c],&rbd);
        this->childs.push_back(child);
        d_c++;
    }
    unsigned int max = 0;
        for(int i = 0; i < this->childs.size(); i++){
            max = (max > mydepth[i])?max: mydepth[i];
            gtree::addtoRBD(mydepth[i], this->childs[i],&rbd);
        }
        max++;
        gtree::addtoRBD(max, this,&rbd);
        gtree::makeIdsWithRBD(rbd);
}
void gtree::addtoRBD(unsigned int depth, gtree* child, vector<vector<gtree*> >* rootsbydepth){
    if((*rootsbydepth).size() <= depth){
        (*rootsbydepth).push_back(* new vector<gtree*>);
    }
    (*rootsbydepth)[depth].push_back(child);
}
gtree::gtree(graph* g, unsigned long long* component, bool state, unsigned int * depth, vector<vector<gtree*>> * rbd){
    this->state = state;
    this->id = 0;
    vector<unsigned long long*> components = g->getConnections(state, component);
    if(components.size() > 1){
        unsigned int * mydepth = (unsigned int *)calloc(components.size(), sizeof(unsigned int));
        unsigned int d_c = 0;
        for(unsigned long long* thiscomponent: components){
            gtree* child = new gtree(g, thiscomponent, !this->state,&mydepth[d_c],rbd);
            this->childs.push_back(child);
            d_c++;
        }
        unsigned int max = 0;
        for(int i = 0; i < this->childs.size(); i++){
            max = (max > mydepth[i])?max: mydepth[i];
            gtree::addtoRBD(mydepth[i], this->childs[i],rbd);
        }
        *depth = max + 1;
    }else{
        this->id = 1;
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