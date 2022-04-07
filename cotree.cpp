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

#include "cotree.h"

unsigned int cotree::getGCDFromPrimeTuple(map<unsigned int,unsigned int> primeMultiset, map<unsigned int,unsigned int> multiset){
    //std::cout << (*(primeMultiset.end())).first << std::endl;
    //std::cout << primeMultiset[(*(primeMultiset.begin())).first] << std::endl;
    return (unsigned int) (multiset[(*primeMultiset.begin()).first]/primeMultiset[(*primeMultiset.begin()).first]);
}
bool cotree::isDivisible(map<unsigned int,unsigned int> divident, map<unsigned int,unsigned int> divisor){
    if(divident.size() == divisor.size()){
        if(divident==divisor) return true;
        unsigned int olddiv;
        for(std::map<unsigned int, unsigned int>::iterator divisorIt=divisor.begin(); divisorIt!= divisor.end(); ++divisorIt){
            unsigned int divisorcount = divisor[(*divisorIt).first];
            unsigned int dividentcount = divident[(*divisorIt).first];
            unsigned int div = (unsigned int)dividentcount/divisorcount;
            if((float) div != (float)((float)dividentcount)/((float) divisorcount) || (olddiv != div && divisorIt!=divisor.begin()) || div == 0){
                return false;
            }
            olddiv =div;
            
        }
        return true;
    }
    return false;
}
map<unsigned int,unsigned int> cotree::constructLCDTUple( map<unsigned int,unsigned int> tuple, unsigned int gcd){
     map<unsigned int,unsigned int> sTuple= tuple;
    for(std::map<unsigned int,unsigned int>::iterator stit=sTuple.begin(); stit!=sTuple.end(); ++stit){
        sTuple[stit->first] = (unsigned int)(stit->second / gcd);
    }
     return sTuple;
}
unsigned int cotree::lcd(unsigned int a, unsigned int b){
    for(unsigned int i=2; i < (a > b? b/2: a/2 ); i++){
        if(a%i==0 && b%i==0){
            return i;
        }
    }
    return 1;
}

unsigned int cotree::gcdTuple( map<unsigned int,unsigned int> gcdTuple){

    unsigned int gcd = gcdTuple[gcdTuple.begin()->first];
    for(std::map<unsigned int,unsigned int>::iterator gsit=gcdTuple.begin(); gsit!=gcdTuple.end(); ++gsit){
        gcd = (unsigned int)__gcd((int)gcd, (int)(gsit->second));
        if(gcd == 1){
            return 1;
        }
    }
            
    return gcd;
}
//calculate factors of given cotree (lexicographic)
vector<vector<cotree*>> cotree::getFactors(){
    vector<cotree*> head = *new vector<cotree*>;
    head.push_back(this);
    vector<vector<cotree*>>  lastFactor = *new vector<vector<cotree*>>;
    lastFactor.push_back(* new vector<cotree*>);
    vector<vector<cotree*>> factors = cotree::getFactors(head, this->depth[1],(unsigned int) 0, &lastFactor);
    //build with last factor together!
    return factors;
}
unsigned int cotree::getChildNum(unsigned int depth){
    unsigned int num = 0;
    for(unsigned int i=0; i < this->childs.size(); i++){
        if(this->childs[i]->getDepth()[1] < depth){
            num++;
        }
    }
    return num;
}
vector<unsigned int> cotree::getPrimeFactorization(unsigned int x, unsigned int i,vector<unsigned int> factors){
    if(x<i){
        return factors;
    }else if(x % i == 0){
        factors.push_back(i);
        return cotree::getPrimeFactorization(x/i, i , factors);
    }else{
        return cotree::getPrimeFactorization(x,i+1,factors);
    }
}
set<vector<unsigned int>> cotree::permutateFactorMultiset(vector<unsigned int> factors){ //permutates the factorization of some Integer, by varying the placement.
    set<vector<unsigned int>> permutated;
    if(factors.size() == 1){
        permutated.insert(factors);
        return permutated;
    }//number already prime
    
    for(unsigned int i = 0; i < factors.size();i++){
        vector<unsigned int> withoutThisFactor (factors);
        withoutThisFactor.erase(withoutThisFactor.begin() + i);
        
        
        set<vector<unsigned int>> recursivePermutation = cotree::permutateFactorMultiset(withoutThisFactor);
        for(std::set<vector<unsigned int>>::iterator it = recursivePermutation.begin(); it !=recursivePermutation.end(); ++it){ //bring the permutated factorizations together
            vector<unsigned int> extractedP (*it);
            extractedP.push_back(factors[i]);
            permutated.insert(extractedP);
        }
               
    }
    return permutated;
}
set<vector<unsigned int>> cotree::getPrimeFactorizations(unsigned int gcd){ //get Factorizations (order NOT neglegtable) of some Number
    vector<unsigned int> factorization = cotree::getPrimeFactorization(gcd, 2, *new vector<unsigned int>);
    
    //permutate the factorizations
    return cotree::permutateFactorMultiset(factorization);
    
}
cotree::cotree(bool state){
    this->state = state;
    this->depth = new unsigned int[2];
    this->depth[0] = 0;
    this->depth[1] = 0;
}
cotree::cotree(unsigned int k, unsigned int id,bool state){ //init a K-Cotree with k vertices (fully connected)
    if(k==1)k=0;
    this->depth = new unsigned int[2];
    this->state = state;
    this->depth[0]=1;
    this->depth[1]=1;
    this->id=id;
    for(unsigned int i = 0; i < k; i++){
        cotree * child = new cotree();
        this->childs.push_back(child);
        child->depth = new unsigned int[2];
        child->depth[0] = 0;
        child->depth[1] = 0;
        child->state = !state;
        child->id = 0;
    }
}
unsigned int cotree::getChildNum(){
    return (unsigned int)this->childs.size();
}
vector<vector<cotree*>> cotree::getFactors(vector<cotree*> heads, unsigned int depth, unsigned int i, vector<vector<cotree*>>* new_factor){
    vector<vector<cotree*>> factors;
    vector<vector<cotree*>> f (*new_factor); 
    if(depth == 0){
        new_factor->at(i) = heads ;
        
        
        factors.push_back(*new vector<cotree*>);
        return factors;
    }
    
    //std::cout <<"recursion with depth = " << to_string(depth)<<  std::endl;
    map<unsigned int, unsigned int> firstTuple = heads.at(0)->getKnuthTuple(depth,false);
    unsigned int gcd = cotree::gcdTuple(firstTuple);
    map<unsigned int,unsigned int> primeMultiset = cotree::constructLCDTUple(firstTuple, gcd);
    vector<unsigned int> gcds;
    gcds.push_back(gcd);
    for(unsigned int h = 1; h < heads.size(); h++){
        map<unsigned int,unsigned int> kt = heads.at(h)->getKnuthTuple(depth,false);
        if(cotree::isDivisible(kt, primeMultiset)){
            unsigned int newgcd = cotree::getGCDFromPrimeTuple(primeMultiset, kt);
            gcds.push_back(newgcd);
            gcd = __gcd(newgcd, gcd);
        }else{
            gcd = 0;
            break;
        }
    }
    if(gcd!=0){//wir müssen hier noch alle möglichkeiten zusqammenführen (also auch normal weiter laufen lassen )
        //pollish prev factor
        
        
       
        
        set<vector<unsigned int>> factorizations = cotree::getPrimeFactorizations(gcd);
        vector<vector<cotree*>> allTowers;
        
        for(std::set<vector<unsigned int>>::iterator it = factorizations.begin() ; it!= factorizations.end(); ++it){
            vector<cotree*> kTower = *new vector<cotree*>;
            bool rootstate = heads[0]->getState();
            for(unsigned int k: *it){
                cotree * kTree = new cotree(k,k, rootstate);
                kTower.push_back(kTree);
                rootstate = !rootstate;
            }
            allTowers.push_back(kTower);
        }
        if(allTowers.empty()){
            allTowers.push_back(*new vector<cotree*>);
        }
        
        vector<cotree*> newHeads;
        
        vector<cotree*> singlehead;
        singlehead.push_back(heads[0]);
        cotree divhead = new cotree(heads[0]); 
        divhead.deleteAboveDepthAndDivideChilds(depth-1, gcds[0]);
        bool headgotpushed = false;
        for(cotree* child: cotree::collectChilds(singlehead , depth - 1)){
            unsigned int id = child->getId();
            if(primeMultiset[id] > 0){
                newHeads.push_back(child);
                primeMultiset[id] = primeMultiset[id] - 1;
            }else{
                if(singlehead[0] == child && !headgotpushed){
                    headgotpushed = true;
                    newHeads.push_back(&divhead);
                }
            }
        }
        
        vector<vector<cotree*>> followingFactors = *new vector<vector<cotree*>>; 
        followingFactors.push_back(*new vector<cotree*>);
        vector<vector<cotree*>> factorscommingafterme = cotree::getFactors(newHeads, depth - 1, 0,&followingFactors );
       
        
        unsigned int * ffdepth = new unsigned int[2];
        ffdepth[0] = -1;
        ffdepth[1] = 0;
        vector<cotree*> followingFactorCompositions = *new vector<cotree*>;
        for(unsigned int i = 0; i < followingFactors.size();i++){
            followingFactorCompositions.push_back((followingFactors[i].size() == 1 && followingFactors[i][0]->getChildNum()==0?
            NULL:
            new cotree(&followingFactors[i], 0, followingFactors[i].size(),ffdepth, heads[0]->getId(), true)));
            if(followingFactorCompositions[i] != NULL)followingFactorCompositions[i]->minimalizeFirstLayer(); //why does this like nothing????
        }
        new_factor->push_back(*new vector<cotree*>);
        

        vector<vector<cotree*>> didntSplit = cotree::getFactors(cotree::collectChilds(heads, depth - 1), depth - 1, i + 1, new_factor); //new factor wird aus 2 blickwinkeln gefüllt
        vector<vector<cotree*>> nf (*new_factor);
        if(didntSplit[0].empty()){
            new_factor->erase(new_factor->begin() + i + 1);
        }else{
            std::cout << "np" << std::endl;
            for(vector<cotree*> fac: didntSplit ){
                factors.push_back(fac);
            }
        }
        cotree::buildBoUpCotree(heads, new_factor, depth,i + 1);
        
        
        for(vector<cotree*> factorcommingafterme: factorscommingafterme){
            for(vector<cotree*> tower: allTowers){
                for(unsigned int i=0; i < followingFactorCompositions.size();i++){
                    vector<cotree*> concatFactors (tower);
                    if(followingFactorCompositions[i] != NULL){
                        concatFactors.push_back(followingFactorCompositions[i]);
                    }
                    concatFactors.insert(concatFactors.end(), factorcommingafterme.begin(),factorcommingafterme.end());
                    factors.push_back(concatFactors);
                }
            }
        }
        
        
        //wenn didntSplit leer ist müssen wir den spaß garnicht anschauen, da dann ja kein neuer Faktor gefunden wurde.
        
        
        //factors.insert(factors.end(), didnSplit.begin(), didnSplit.end());
        
        for(unsigned int h=0; h < heads.size();h++){
            
                new_factor->at(i).push_back(new cotree((unsigned int)gcds[h]/gcd, 
                                        heads[h]->getId(), 
                                        heads[h]->getState() ));
            
            
            
        }
        
        nf = (*new_factor);
        return factors;
        
        
                
    }else{

        vector<vector<cotree*>> prev_factors = cotree::getFactors(cotree::collectChilds(heads, depth - 1), depth - 1, i, new_factor);
        vector<vector<cotree*>> nf (*new_factor);
        //here we have to build up the new factor from bottom up
        
        
        cotree::buildBoUpCotree(heads, new_factor, depth,i);
        
        nf = (*new_factor);
        return prev_factors;
    }
}
void cotree::buildBoUpCotree(vector<cotree*> heads, vector<vector<cotree*>>* new_factors, unsigned int depth, unsigned int j){
    vector<vector<cotree*>> nf (*new_factors);
    for(unsigned int i=j; i< new_factors->size();i++){
        //if(new_factors->at(i).empty())return;
            
        unsigned int factorcounter = 0;
        
        for(cotree* head:heads){
            unsigned int childnum = head->getChildNum(depth); ;
            if(head->getId() == new_factors->at(i).at(factorcounter)->getId()){
                factorcounter++;
                continue;
            }            
            if(head->getDepth()[1]==depth){
                cotree* newFactorNode = new cotree(&new_factors->at(i), factorcounter, factorcounter + childnum, head->getDepth(),head->getId(),head->getState() );
                newFactorNode->minimalizeFirstLayer();
                std::vector<cotree*>::iterator it = new_factors->at(i).begin() + factorcounter;
                new_factors->at(i).insert(it,newFactorNode);
                factorcounter++;
            }else{
                factorcounter += childnum;
            }
        }
    }
}
void cotree::minimalizeFirstLayer(){
    for(unsigned int i=0; i < this->childs.size(); i++){
        if(this->getState() == this->childs[i]->getState()){
            vector<cotree*> childsOfChild = this->childs[i]->getChilds();
            this->childs.insert(this->childs.end(),childsOfChild.begin(), childsOfChild.end() );
            this->childs.erase(this->childs.begin() + i);
            i--;
        }
    }

}
void cotree::deleteAboveDepthAndDivideChilds(unsigned int depth, unsigned int divisor){
    for( unsigned int i = 0; i < this->childs.size(); i++){
        if(this->childs[i]->getDepth()[1] > depth){
            this->childs.erase(this->childs.begin() + i);
            i--;
        }
    }
    map<unsigned int, unsigned int> myKT = this->getKnuthTuple(depth, false);
    map<unsigned int, unsigned int> myKTprime = cotree::constructLCDTUple(myKT,divisor);
    for(unsigned int i = 0; i < this->childs.size(); i++){
        if(myKTprime[this->childs[i]->getId()] > 0){
            myKTprime[this->childs[i]->getId()]--;
        }else{
            this->childs.erase(this->childs.begin() + i);
            i--;
        }
    }
    
   
}
cotree::cotree(cotree * other){
    this->state = other->state;
    this->childs = other->getChilds();
    this->id = other->id;
    this->depth= new unsigned int [2];
    this->depth[0] = other->depth[0];
    this->depth[1] = other->depth[1];
}
cotree::cotree(vector<cotree*> *children, unsigned int from, unsigned int to, unsigned int *hdepth, unsigned int hid, bool state){
    this->depth = new unsigned int[2];
    
    this->depth[0] = hdepth[0];
    this->depth[1] = hdepth[1];
    
    this->state = state;
    for(unsigned int i = from; i < to; i++){
        this->childs.push_back(children->at(i));
        unsigned int *cdepth = children->at(i)->getDepth(); 
        this->depth[0]= (cdepth[1] + 1 < this->depth[0]? cdepth[1] + 1 : this->depth[0]);
        this->depth[1]= (cdepth[1] + 1 > this->depth[1]? cdepth[1] + 1 : this->depth[1]);
    }
    this->id = hid;
    children->erase(children->begin() + from, children->begin() + to );
    
}
vector<cotree*> cotree::collectChilds(vector<cotree*> heads, unsigned int depth){
    vector<cotree*> childs;
    for(cotree* head : heads){
        if(head->getDepth()[0] <= depth){
            childs.push_back(head);
        }
        for( cotree* child: head->getChilds()){
            if(child->getDepth()[1] == depth){
                childs.push_back(child);
            }
        }
    }
    return childs;
}
vector<vector<cotree>> cotree::getFactors(vector<vector<cotree*>> * depthdict, vector<vector<cotree>> factors){
    for(int d = depthdict->size()-1; d > -1 ; d--){
        
        
        map<unsigned int, unsigned int> firstTuple = depthdict->at(d).at(0)->getKnuthTuple(d,false);
        unsigned int gcd = cotree::gcdTuple(firstTuple);
        map<unsigned int,unsigned int> primeMultiset=cotree::constructLCDTUple(firstTuple, gcd);
        for(int i = 1; i < depthdict->at(d).size(); i++){//we have to assure that we don't have the case, that the gcd of two tuples wont come after others  
            map<unsigned int,unsigned int> kt = depthdict->at(d).at(i)->getKnuthTuple(d,false);
            if(cotree::isDivisible(kt, primeMultiset)){
                unsigned int newgcd = cotree::getGCDFromPrimeTuple(primeMultiset, kt);
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
unsigned int * cotree::getDepth(){
    return this->depth;
}
 map<unsigned int,unsigned int> cotree::getKnuthTuple(unsigned int depth, bool minimal){
    if(minimal && depth < this->depth[1]){
        return *new  map<unsigned int,unsigned int>;
    }
    unsigned int num = 0;
    //std::cout << "---"<< std::endl;
    map<unsigned int,unsigned int> tuple;
    for(cotree* child: this->childs){
        if(child->getDepth()[1] < depth ){
            tuple[child->getId()] = tuple[child->getId()] + 1;
            //std::cout << child->getId()<< ":" << tuple[child->getId()]  <<  std::endl;
        }
    }
    return tuple;
}

int cotree::findInMultisetVector(vector< map<unsigned int,unsigned int>> vec, map<unsigned int,unsigned int> ms){
    for(int i = 0; i < vec.size();i++){
        if(vec.at(i) == ms){
            return i;
        }
    }
    return -1;
}
void cotree::createIndices(vector<vector<cotree*>> depthdict){
    unsigned int last_depths_index = 1;
    for(unsigned int d=1; d < depthdict.size(); d++){
        vector< map<unsigned int,unsigned int>> tuples;
        for(unsigned int i=0; i < depthdict[d].size(); i++){
             map<unsigned int,unsigned int> kt = depthdict[d][i]->getKnuthTuple(d,true);
            if(kt.empty()){
                continue;
            }
            int index = cotree::findInMultisetVector(tuples, kt);
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
unsigned int cotree::getId(){
    return this->id;
}
void cotree::setId(unsigned int id){
    this->id = id;
}

string cotree::get_string(){
    return this->get_string("",true);
}
string cotree::get_string(string intendation, bool isLast){
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
cotree::cotree() {
    this->depth = new unsigned int[2];
}

cotree::cotree(const cotree& orig) {
}
void cotree::constructChildren(graph* g, vector<unsigned long long*>* components,vector<vector<cotree*>> *depthdict ){
    this->depth= new unsigned int[2];
            this->depth[0]=0;
            this->depth[1]=0;
        if(components->size() > 1){
            this->id = 0;
            this->depth[0]=-1;
            for(unsigned long long* thiscomponent: *components){
                unsigned int *cdepth = new unsigned int[2];
                cotree* child = new cotree(g, thiscomponent, !this->state,cdepth, depthdict);
                
                this->depth[0]= (cdepth[1] + 1 < this->depth[0]? cdepth[1] + 1 : this->depth[0]);
                this->depth[1]= (cdepth[1] + 1 > this->depth[1]? cdepth[1] + 1 : this->depth[1]);
                
                this->childs.push_back(child);
            }
        }else{
            this->id = (this->state? 1:0);
        }
}
cotree::cotree(graph* g, vector<vector<cotree*>> depthdict){
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
cotree::cotree(graph* g, unsigned long long* component, bool state, unsigned int * pdepth,vector<vector<cotree*>> *depthdict){
    this->state = state;
    vector<unsigned long long*> components = g->getConnections(state, component);
    {
        this->constructChildren(g,&components,depthdict);
    }
        pdepth[0] = this->depth[0];
        pdepth[1] = this->depth[1];
        this->writeInDepthDict(depthdict);
}
void cotree::writeInDepthDict(vector<vector<cotree*> >* depthdict){
    for(unsigned int i = this->depth[0]; i <= this->depth[1];i++){
        if(depthdict->size() < i+1 ){
            depthdict->push_back(* new vector<cotree*>);
        }
        depthdict->at(i).push_back(this);
    }
}
cotree::~cotree() {
}


vector<cotree*> cotree::getChilds(){
    return childs;
}

bool cotree::getState(){
    return this->state;
}
void cotree::setState(bool state){
    this->state = state;
}
void cotree::addChild(cotree* child){
    this->childs.push_back(child);
}

cotree* cotree::getChild(unsigned short i){
    return this->childs.at(i);
}