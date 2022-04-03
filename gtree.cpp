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
    std::cout << (*(primeMultiset.end())).first << std::endl;
    std::cout << primeMultiset[(*(primeMultiset.begin())).first] << std::endl;
    return (unsigned int) (multiset[(*primeMultiset.begin()).first]/primeMultiset[(*primeMultiset.begin()).first]);
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
//calculate factors of given cotree (lexicographic)
vector<vector<gtree*>> gtree::getFactors(){
    vector<gtree*> head = *new vector<gtree*>;
    head.push_back(this);
    vector<gtree*>  lastFactor = *new vector<gtree*>;
    vector<vector<gtree*>> factors = gtree::getFactors(head, this->depth[1],(unsigned int) 1, &lastFactor);
    for(unsigned int i = 0; i < factors.size(); i++){
        factors[i].insert(factors[i].begin(), lastFactor.begin(), lastFactor.end());
    }
    return factors;
}
unsigned int gtree::getChildNum(unsigned int depth){
    unsigned int num = 0;
    for(unsigned int i=0; i < this->childs.size(); i++){
        if(this->childs[i]->getDepth()[1] < depth){
            num++;
        }
    }
    return num;
}
vector<unsigned int> gtree::getPrimeFactorization(unsigned int x, unsigned int i,vector<unsigned int> factors){
    if(x<i){
        return factors;
    }else if(x % i == 0){
        factors.push_back(i);
        return gtree::getPrimeFactorization(x/i, i , factors);
    }else{
        return gtree::getPrimeFactorization(x,i+1,factors);
    }
}
set<vector<unsigned int>> gtree::permutateFactorMultiset(vector<unsigned int> factors){
    set<vector<unsigned int>> permutated;
    if(factors.size() == 1){
        permutated.insert(factors);
        return permutated;
    }
    for(unsigned int i = 0; i < factors.size();i++){
        vector<unsigned int> withoutThisFactor (factors);
        withoutThisFactor.erase(factors.begin() + i);
        
        set<vector<unsigned int>> recursivePermutation = gtree::permutateFactorMultiset(withoutThisFactor);
        for(std::set<vector<unsigned int>>::iterator it = recursivePermutation.begin(); it !=recursivePermutation.end(); ++it){
            vector<unsigned int> extractedP (*it);
            extractedP.push_back(factors[i]);
            permutated.insert(extractedP);
        }
               
    }
    return permutated;
}
set<vector<unsigned int>> gtree::getPrimeFactorizations(unsigned int gcd){
    vector<unsigned int> factorization = gtree::getPrimeFactorization(gcd, 2, *new vector<unsigned int>);
    
    //permutate the factorizations
    return gtree::permutateFactorMultiset(factorization);
    
}
gtree::gtree(bool state){
    this->state = state;
}
gtree::gtree(unsigned int k){
    this->depth = new unsigned int[2];
    if(k==1){
        this->depth[0]=0;
        this->depth[1]=0;
        this->state = true;
        this->id=1;
        return;
    }
    this->state = true;
    this->depth[0]=1;
        this->depth[1]=1;
    this->id=1;
    for(unsigned int i = 0; i < k; i++){
        gtree * child = new gtree();
        this->childs.push_back(child);
        child->depth = new unsigned int[2];
        child->depth[0] = 0;
        child->depth[1] = 0;
        child->state = false;
        child->id = 0;
    }
}
vector<vector<gtree*>> gtree::getFactors(vector<gtree*> heads, unsigned int depth, unsigned int divisor, vector<gtree*>* new_factor){
    vector<vector<gtree*>> factors;
    if(depth == 0){
        *new_factor = heads ;
        factors.push_back(*new vector<gtree*>);
        return factors;
    }
    
    std::cout <<"recursion with depth = " << to_string(depth)<<  std::endl;
    map<unsigned int, unsigned int> firstTuple = heads.at(0)->getKnuthTuple(depth,false);
    unsigned int gcd = gtree::gcdTuple(firstTuple);
    map<unsigned int,unsigned int> primeMultiset = gtree::constructLCDTUple(firstTuple, gcd);
    vector<unsigned int> gcds;
    gcds.push_back(gcd);
    for(unsigned int h = 1; h < heads.size(); h++){
        map<unsigned int,unsigned int> kt = heads.at(h)->getKnuthTuple(depth,false);
        if(gtree::isDivisible(kt, primeMultiset)){
            unsigned int newgcd = gtree::getGCDFromPrimeTuple(primeMultiset, kt);
            gcds.push_back(newgcd);
            gcd = __gcd(newgcd, gcd);
        }else{
            gcd = 0;
            break;
        }
    }
    if(gcd!=0){//wir müssen hier noch alle möglichkeiten zusqammenführen (also auch normal weiter laufen lassen :))
        //pollish prev factor
        for(unsigned int h=0; h < heads.size();h++){
            new_factor->push_back(new gtree((unsigned int)gcds[h]/gcd));
        }
        
       
        
        set<vector<unsigned int>> factorizations = gtree::getPrimeFactorizations(gcd);
        vector<vector<gtree*>> allTowers;
        for(std::set<vector<unsigned int>>::iterator it = factorizations.begin() ; it!= factorizations.end(); ++it){
            vector<gtree*> kTower = *new vector<gtree*>;
            for(unsigned int k: *it){
                gtree * kTree = new gtree(k);
                kTower.push_back(kTree);
            }
            allTowers.push_back(kTower);
        }
        if(allTowers.empty()){
            allTowers.push_back(*new vector<gtree*>);
        }
        
        vector<gtree*> newHeads;
        
        vector<gtree*> singlehead;
        singlehead.push_back(heads[0]);
            
        for(gtree* child: gtree::collectChilds(singlehead , depth - 1)){
            unsigned int id = child->getId();
            if(primeMultiset[id] > 0){
                newHeads.push_back(child);
                primeMultiset[id] = primeMultiset[id] - 1;
            }else{
                
                for(gtree* childOfambiguousDepthNode : child->getChilds()){
                    unsigned int id = childOfambiguousDepthNode->getId();
                    if(childOfambiguousDepthNode->depth[1] < depth - 1 && primeMultiset[id] > 0){
                        primeMultiset[id] = 0;
                        newHeads.push_back(child);
                        break;
                    }
                }
            }
        }
        
        vector<gtree*> followingFactor = *new vector<gtree*>; 
        vector<vector<gtree*>> factorscommingafterme = gtree::getFactors(newHeads, depth - 1, 1,&followingFactor );
        gtree *followingFactorComposition = new gtree(&followingFactor, 0, followingFactor.size());
        for(vector<gtree*> factorcommingafterme: factorscommingafterme){
            for(vector<gtree*> tower: allTowers){
                vector<gtree*> concatFactors (tower);
                concatFactors.push_back(followingFactorComposition);
                concatFactors.insert(concatFactors.end(), factorcommingafterme.begin(),factorcommingafterme.end());
                factors.push_back(concatFactors);
            }
        }
        return factors;
        
        
                
    }else{
        vector<vector<gtree*>> prev_factors = gtree::getFactors(gtree::collectChilds(heads, depth - 1), depth - 1, 1, new_factor);
        
        //here we have to build up the new factor from bottom up
        vector<gtree*> nf (*new_factor);
        unsigned int factorcounter = 0;
        
        for(gtree* head:heads){
            unsigned int childnum = head->getChildNum(depth);
            if(head->getDepth()[1]==depth){
                gtree* newFactorNode = new gtree(new_factor, factorcounter, factorcounter + childnum  );
                std::vector<gtree*>::iterator it = new_factor->begin() + factorcounter;
                new_factor->insert(it,newFactorNode);
            }else{
                factorcounter += childnum;
            }
        }
        nf = (*new_factor);
        return prev_factors;
    }
}
gtree::gtree(vector<gtree*> *children, unsigned int from, unsigned int to){
    for(unsigned int i = from; i < to; i++){
        this->childs.push_back(children->at(i));
        
    }
    for(unsigned int i = from; i < to; i++){
        children->erase(children->begin() + i);
    }
}
vector<gtree*> gtree::collectChilds(vector<gtree*> heads, unsigned int depth){
    vector<gtree*> childs;
    for(gtree* head : heads){
        if(head->getDepth()[0] <= depth){
            childs.push_back(head);
        }
        for( gtree* child: head->getChilds()){
            if(child->getDepth()[1] == depth){
                childs.push_back(child);
            }
        }
    }
    return childs;
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
    std::cout << "---"<< std::endl;
    map<unsigned int,unsigned int> tuple;
    for(gtree* child: this->childs){
        if(child->getDepth()[1] < depth ){
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