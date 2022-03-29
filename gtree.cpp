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
//Probably own sorting function on depthdict, or go for gcd in Multiset that we have prob biggest Instance and smallest as well (smallest divisor of gcd)

#include "gtree.h"

unsigned int gtree::getGCDFromPrimeTuple(map<unsigned int,unsigned int> primeMultiset, map<unsigned int,unsigned int> multiset){
    return multiset[(*primeMultiset.begin()).first]/primeMultiset[(*primeMultiset.begin()).first];
}
bool gtree::isDivisible(map<unsigned int,unsigned int> divident, map<unsigned int,unsigned int> divisor){
    if(divident.size() == divisor.size()){
        unsigned int olddiv;
        for(std::map<unsigned int, unsigned int>::iterator divisorIt=divisor.begin(); divisorIt!= divisor.end(); ++divisorIt){
            unsigned int divisorcount = divisor[(*divisorIt).first];
            unsigned int dividentcount = divident[(*divisorIt).first];
            unsigned int div = (unsigned int)dividentcount/divisorcount;
            if((float) div != (float)((float)dividentcount)/((float) divisorcount) || olddiv != div){
                return false;
            }
            
        }
        return true;
    }
    return false;
}
map<unsigned int,unsigned int> gtree::constructLCDTUple( map<unsigned int,unsigned int> tuple, unsigned int gcd){
     map<unsigned int,unsigned int> sTuple= tuple;
    for(std::map<unsigned int,unsigned int>::iterator stit=sTuple.begin(); stit!=sTuple.end(); ++stit){
        sTuple[stit->first] = (unsigned int)(stit->second / gcd);
    }
     return sTuple;
}
unsigned int gtree::lcd(unsigned int a, unsigned int b){
    for(unsigned int i=2; i < (a > b? b/2: a/2 ); i++){
        if(a%i==0 && b%i==0){
            return i;
        }
    }
    return 1;
}

unsigned int gtree::gcdTuple( map<unsigned int,unsigned int> gcdTuple){

    unsigned int gcd = gcdTuple[gcdTuple.begin()->first];
    for(std::map<unsigned int,unsigned int>::iterator gsit=gcdTuple.begin(); gsit!=gcdTuple.end(); ++gsit){
        gcd = (unsigned int)__gcd((int)gcd, (int)gcdTuple.count(gsit->second));
        if(gcd == 1){
            return 1;
        }
    }
            
    return gcd;
}

vector<vector<gtree>> gtree::getFactors(vector<vector<gtree*>> * depthdict, vector<vector<gtree>> factors){
    for(int d = depthdict->size()-1; d > -1 ; d--){
        
        
        map<unsigned int, unsigned int> firstTuple = depthdict->at(d).at(0)->getKnuthTuple(d,false);
        unsigned int gcd = gtree::gcdTuple(firstTuple);
        map<unsigned int,unsigned int> primeMultiset=gtree::constructLCDTUple(firstTuple, gcd);
        for(int i = 1; i < depthdict->at(d).size(); i++){//we have to assure that we don't have the case, that the gcd of two tuples wont come after others  
            map<unsigned int,unsigned int> kt = depthdict->at(d).at(i)->getKnuthTuple(d,false);
            if(gtree::isDivisible(kt, primeMultiset)){
                unsigned int newgcd = gtree::getGCDFromPrimeTuple(primeMultiset, kt);
                gcd = __gcd(newgcd, gcd);
            }else{
                break;
            }
            
        }
    }
    return factors;
} 
/**
 * 
 * 
 * 
 */
unsigned int * gtree::getDepth(){
    return this->depth;
}
 map<unsigned int,unsigned int> gtree::getKnuthTuple(unsigned int depth, bool minimal){
    if(minimal && depth < this->depth[1]){
        return *new  map<unsigned int,unsigned int>;
    }
    unsigned int num = 0;
     
    map<unsigned int,unsigned int> tuple;
    for(gtree* child: this->childs){
        if(child->getDepth()[0] < depth ){
            tuple[child->getId()] = tuple[child->getId()] + 1;
            std::cout << child->getId()<< ":" << tuple[child->getId()]  <<  std::endl;
        }
    }
    return tuple;
}

int gtree::findInMultisetVector(vector< map<unsigned int,unsigned int>> vec, map<unsigned int,unsigned int> ms){
    for(int i = 0; i < vec.size();i++){
        if(vec.at(i) == ms){
            return i;
        }
    }
    return -1;
}
void gtree::createIndices(vector<vector<gtree*>> depthdict){
    unsigned int last_depths_index = 1;
    for(unsigned int d=1; d < depthdict.size(); d++){
        vector< map<unsigned int,unsigned int>> tuples;
        for(unsigned int i=0; i < depthdict[d].size(); i++){
             map<unsigned int,unsigned int> kt = depthdict[d][i]->getKnuthTuple(d,true);
            if(kt.empty()){
                continue;
            }
            int index = gtree::findInMultisetVector(tuples, kt);
            if(index > -1){
                depthdict[d][i]->setId(last_depths_index + index + 1);
            }else{
                tuples.push_back(kt);
                depthdict[d][i]->setId(last_depths_index + tuples.size());
            }
                        
        }
        last_depths_index += tuples.size();
        //sort tuples
    }

}
unsigned int gtree::getId(){
    return this->id;
}
void gtree::setId(unsigned int id){
    this->id = id;
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
    me_s.append("\t [").append(to_string(this->depth[0])).append(", ").append(to_string(this->depth[1])).append("]").append(" \t (").append(to_string(this->id)).append(")").append("\n");
    for(unsigned short i = 0; i < this->childs.size(); i++){
        me_s.append(this->childs.at(i)->get_string(intendation,(this->childs.size()-1 == i) ));
    }
    return me_s;
    
}
gtree::gtree() {
}

gtree::gtree(const gtree& orig) {
}
void gtree::constructChildren(graph* g, vector<unsigned long long*>* components,vector<vector<gtree*>> *depthdict ){
    this->depth= new unsigned int[2];
            this->depth[0]=0;
            this->depth[1]=0;
        if(components->size() > 1){
            this->id = 0;
            this->depth[0]=-1;
            for(unsigned long long* thiscomponent: *components){
                unsigned int *cdepth = new unsigned int[2];
                gtree* child = new gtree(g, thiscomponent, !this->state,cdepth, depthdict);
                
                this->depth[0]= (cdepth[1] + 1 < this->depth[0]? cdepth[1] + 1 : this->depth[0]);
                this->depth[1]= (cdepth[1] + 1 > this->depth[1]? cdepth[1] + 1 : this->depth[1]);
                
                this->childs.push_back(child);
            }
        }else{
            this->id = (this->state? 1:0);
        }
}
gtree::gtree(graph* g, vector<vector<gtree*>> depthdict){
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
    this->constructChildren(g,&components,&depthdict);
    this->writeInDepthDict(&depthdict);
    this->createIndices(depthdict);
}
gtree::gtree(graph* g, unsigned long long* component, bool state, unsigned int * pdepth,vector<vector<gtree*>> *depthdict){
    this->state = state;
    vector<unsigned long long*> components = g->getConnections(state, component);
    {
        this->constructChildren(g,&components,depthdict);
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