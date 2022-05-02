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

#include "../headers/cotree.h"

unsigned int cotree::getGCDFromPrimeTuple(map<unsigned int,unsigned int> primeMultiset, map<unsigned int,unsigned int> multiset){
    //because multiset is divisible by primeMultiset we just need to divide the first multiplicities.
    return (unsigned int) (multiset[(*primeMultiset.begin()).first]/primeMultiset[(*primeMultiset.begin()).first]);
}
bool cotree::isDivisible(map<unsigned int,unsigned int> divident, map<unsigned int,unsigned int> divisor){
    
    if(divident.size() == divisor.size()){//if they dont have the same size, they have to differ with at least one element
        
        if(divident==divisor) return true; 
        unsigned int olddiv;
        //loop throu all indices of the divisor and divide the multiplicities. If all quotients are the same then the multiset is divisible by prime multiset
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
map<unsigned int,unsigned int> cotree::constructGCDTuple( map<unsigned int,unsigned int> tuple, unsigned int gcd){
    
    map<unsigned int,unsigned int> sTuple= tuple;
    //devide every multiplicity by gcd
    for(std::map<unsigned int,unsigned int>::iterator stit=sTuple.begin(); stit!=sTuple.end(); ++stit){
        sTuple[stit->first] = (unsigned int)(stit->second / gcd);
    }
     return sTuple;
}


unsigned int cotree::gcdTuple( map<unsigned int,unsigned int> gcdTuple){

    unsigned int gcd = gcdTuple[gcdTuple.begin()->first];
    //get gcd from all multiplicities of the multiset
    for(std::map<unsigned int,unsigned int>::iterator gsit=gcdTuple.begin(); gsit!=gcdTuple.end(); ++gsit){
        gcd = (unsigned int)__gcd((int)gcd, (int)(gsit->second));
        if(gcd == 1){
            return 1;
        }
    }
            
    return gcd;
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
    }else if(x % i == 0){ //if i devides x then we found a factor and continue with x/i
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
    this->virtualData[0].foundK = 0;
}
cotree::cotree(unsigned int k, unsigned int id,bool state){ //init a K-Cotree with k vertices (fully connected)
    if(k==1)k=0;
    this->depth = new unsigned int[2];
    this->state = state;
    this->depth[0]=1;
    this->depth[1]=1;
    this->virtualData[0].id =id;
    for(unsigned int i = 0; i < k; i++){
        cotree * child = new cotree();
        this->childs.push_back(child);
        child->depth = new unsigned int[2];
        child->depth[0] = 0;
        child->depth[1] = 0;
        child->state = !state;
        child->virtualData[0].id = 0;
    }
}
unsigned int cotree::getChildNum(){
    return (unsigned int)this->childs.size();
}

unsigned int * cotree::getDepth(){
    return this->depth;
}
 map<unsigned int,unsigned int> cotree::getKnuthTuple(unsigned int depth){

    unsigned int num = 0;
    
    map<unsigned int,unsigned int> tuple;
    
    for(cotree* child: this->childs){
        if(child->getDepth()[1] == depth-1 ){ //child lays directly below
            tuple[child->getId()] = tuple[child->getId()] + child->getMultiplicity();
            
        }
    }
    if(this->depth[0] < depth){//look at itself as well
        tuple[this->getId()] = tuple[this->getId()] + this->getMultiplicity();
    }
    return tuple;
}


cotree::cotree(cotree* copy, unsigned int depthtogo,map<unsigned int, unsigned int> primeTuple, unsigned int depth){
    this->state = copy->getState();
    this->virtualData[0].multiplicity = 1;
    if(depthtogo > 0){
        for(cotree* copy_child : copy->getChilds()){
            if(primeTuple[copy_child->getId()] > 0 &&copy_child->getDepth()[1] == depth-1){// && copy_child->getDepth()[1]==depthtogo-1
                this->childs.push_back(new cotree(copy_child, depthtogo-1));
                primeTuple[copy_child->getId()] --;
            }
        }
        if(primeTuple[copy->getId()] > 0){ //look at itself 
            for(unsigned int i = 0; i < primeTuple[copy->getId()] ; i++){
                this->childs.push_back(new cotree(!this->state));
            }
        }
    }else if (copy->getFoundK() > 1){
        for(unsigned int i = 0; i < copy->getFoundK(); i++){
            this->childs.push_back(new cotree(!copy->getState()));
        }
    }
}

void cotree::setFoundK(unsigned int k,unsigned int procId){
    this->virtualData[procId].foundK = k;
}

unsigned int cotree::getFoundK(unsigned int procId){
    return this->virtualData[procId].foundK;
}
cotree::cotree(cotree* copy, unsigned int depthtogo){
    this->state = copy->state;
    this->virtualData[0].multiplicity= 1;
    if(depthtogo > 0){
        for(cotree* copy_child : copy->getChilds()){

            this->childs.push_back(new cotree(copy_child, depthtogo-1));
            
        }
    }else if (copy->getFoundK() > 1){
        for(unsigned int i = 0; i < copy->getFoundK(); i++){
            this->childs.push_back(new cotree(!copy->getState()));
        }
    }
}
int cotree::findInMultisetVector(vector< map<unsigned int,unsigned int>> vec, map<unsigned int,unsigned int> ms){
    for(int i = 0; i < vec.size();i++){
        if(vec.at(i) == ms){
            return i;
        }
    }
    return -1;
}
vector<vector<cotree*>> cotree::getFactors(vector<vector<cotree*>> depthdict, unsigned int oldDepth, unsigned int callNumber){ //merge this with the factor-Algorithm (BottomUp)
    vector<vector<cotree*>> factors;
    factors.push_back(*new vector<cotree*> );
    unsigned int lastdepthfound = 0;
    
    for(unsigned int d=oldDepth; d < depthdict.size(); d++){
        
        vector< map<unsigned int,unsigned int>> tuples; //index tuples of children (of nodes with depth d)
        vector<map<unsigned int, unsigned int>> primeTuples;  //primetuples generating the set tuples (devides each component of other tuple and is itself not divisible) 
        vector<unsigned int*> gcds; //for each tuple its components gcd and the array-index of prime Tuple dividing it
        
        for(unsigned int i=0; i < depthdict[d].size(); i++){//always split brutally if it is indeed not its own maximal depth
             
             map<unsigned int,unsigned int> kt = depthdict[d][i]->getKnuthTuple(d); //get indexTuple
             unsigned int pTnum = 0; //primeTupleNumber
             bool foundPrime = false; 

             for(map<unsigned int, unsigned int> primeTuple : primeTuples){ //did we came across other Tuples that have the same prime Tuple? If so fill informations
                 if(cotree::isDivisible(kt, primeTuple)){
                     gcds.push_back(new unsigned int[2] {cotree::getGCDFromPrimeTuple(primeTuple, kt) , pTnum});
                     foundPrime = true;
                     break;
                 }
                 pTnum++;
             }
             
             if(!foundPrime){//if we didnt came across such a primeTuple note this Tuples PrimeTuple in our prime-list.
                 unsigned int gcd = cotree::gcdTuple(kt);
                 primeTuples.push_back(cotree::constructGCDTuple( kt , gcd ));
                 gcds.push_back(new unsigned int[2] {gcd , pTnum});
             }
                                     
        }
        //sort tuples
        vector<map<unsigned int, unsigned int>> remainingTuples;
        if(primeTuples.size()==1){//wenn das passiert müssen wir bei nicht splitbaren tupeln //wenn gefunden es muss auch der else part ausgeführt werden, jedoch in anderer "Dimension" (DImensionen fernhalten)
            //construct K-Tower here and add them to our factors. As well as the found primefactor
            unsigned int gcd = 0;
            
            for(unsigned int i = 0; i < gcds.size(); i++){ //extracting the greatest divisor with which we are able to split all tuples
                gcd = __gcd(gcd, gcds[i][0]);
                
            }
            /**
             * Now we have to distinguish between 
             * nodes that are splittable (e.g. their parent has got the same state) --> split them virtually
             * nodes that are not splittable (e.g. their parent hast not got the same state) --> extrude a set of of splits from them downwards, namely foundK
             */
            for(unsigned int i =0 ; i < gcds.size(); i++){
                if(depthdict[d][i]->getDepth()[1] > d ){ //parent node has same state
                    depthdict[d][i]->setId(0);
                    //depthdict[d][i]->setId(gcds.at(i)[1]); //set new ID
                    depthdict[d][i]->setMultiplicity(gcds.at(i)[0]/gcd); //set Multiplicity which remains after extracting the kTower
                    depthdict[d][i]->setFoundK(0); //nothing to extrude downwards
                }else{ //parent node has not got the same state
                    /**
                     * order the not splittable tuples and look for similarities, thus giving them an equivalent id if their tuple is the same
                     * considering id's only for (1 <= id <= n) because id = 0 is reserved for the splitted tuples
                     */
                    map<unsigned int,unsigned int> kt = depthdict[d][i]->getKnuthTuple(d);
                    int id = cotree::findInMultisetVector(remainingTuples, kt); 
                    if(id > -1){ //tuple has  been seen before
                        depthdict[d][i]->setId(id + 1);
                    
                    }else{  //tuple has not been seen before
                        depthdict[d][i]->setId(remainingTuples.size() + 1); //set new id
                        remainingTuples.push_back(kt); 
                    }
                        depthdict[d][i]->setFoundK(gcds.at(i)[0]/gcd); //extrude downwards
                        depthdict[d][i]->setMultiplicity(1);           //don't split
                    
                }
            } 
            
            set<vector<unsigned int>> factorizations = cotree::getPrimeFactorizations(gcd); //get factorizations of gcd (order NOT neglegted)
            
            vector<vector<cotree*>> allTowers;
        
            for(std::set<vector<unsigned int>>::iterator it = factorizations.begin() ; it!= factorizations.end(); ++it){ //construct kTower from gcd's factorization
                vector<cotree*> kTower = *new vector<cotree*>;
                bool rootstate = depthdict[d][0]->getState(); //set rootstate
                for(unsigned int k: *it){
                    cotree * kTree = new cotree(k,k, rootstate);
                    kTower.push_back(kTree);
                    rootstate = !rootstate;
                }
                allTowers.push_back(kTower);
            }
                    
            unsigned int factorcount = factors.size();
            
            unsigned int towercount = allTowers.size();
            bool nofactor = true;
            
            for(unsigned int i = 0; i < factorcount; i++ ){
                
                factors[i].push_back(new cotree(depthdict[d][0], d-lastdepthfound, primeTuples[0],d)); //construct tree of the primeTuple
                
                if(factors[i][factors[i].size()-1]->getChildNum() < 2 ){//check if the factor would be trivial (single vertice) and delete it then
                    factors[i].pop_back(); 
                }else{
                    nofactor = false;
                }
                
                if(towercount > 1)factors.insert(factors.end(), towercount-1, factors[i]); //copy every factor as many times as there exists towers
                
            }
                    
            for(unsigned int ti = 0; ti < allTowers.size(); ti++){//putting the Ktowers to the new concatenated factors 
                for(unsigned int fi = 0; fi < factorcount; fi++){
                    factors[fi*towercount+ti].insert(factors[fi*towercount + ti].end(), allTowers[ti].begin(), allTowers[ti].end());
                }
            }
                    
            lastdepthfound = d; 
        }else{
            for(unsigned int i = 0; i < gcds.size(); i++){ //splitting of the tuples to make sure that all are prime
                if(depthdict[d][i]->getDepth()[1] > d){
                    depthdict[d][i]->setId(gcds.at(i)[1]);
                    depthdict[d][i]->setMultiplicity(gcds.at(i)[0]);
                    depthdict[d][i]->setFoundK(0);
                }else{
                    map<unsigned int,unsigned int> kt = depthdict[d][i]->getKnuthTuple(d);
                    int id = cotree::findInMultisetVector(remainingTuples, kt);
                    if(id > -1){
                        depthdict[d][i]->setId(id + primeTuples.size());
                    
                    }else{
                        depthdict[d][i]->setId(remainingTuples.size() + primeTuples.size());
                        remainingTuples.push_back(kt);
                    }
                        depthdict[d][i]->setMultiplicity(1); 
                        depthdict[d][i]->setFoundK(gcds.at(i)[0]);//think we might can delete this part because found k is just interesting if indeed a factor found
                }
                
            }
        }
    }
    
    return factors;
}
unsigned int cotree::getMultiplicity(unsigned int procId){
    return this->virtualData[procId].multiplicity;
}
void cotree::setMultiplicity(unsigned int m,unsigned int procId){
    this->virtualData[procId].multiplicity = m;
}
unsigned int cotree::getId(unsigned int procId){
    return this->virtualData[procId].id;
}
void cotree::setId(unsigned int id, unsigned int procId){
    this->virtualData[procId].id = id;
}

string cotree::get_string(){
    return string("  ").append(this->get_string("",true).substr(6, string::npos));
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
    //me_s.append("\t [").append(to_string(this->depth[0])).append(", ").append(to_string(this->depth[1])).append("]").append(" \t (").append(to_string(this->id)).append(")");
    me_s.append("\n");
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
            this->virtualData[0].multiplicity = 1;
            this->virtualData[0].foundK = 0;
        if(components->size() > 1){//more than one vertice
            this->virtualData[0].id = 0;
            this->depth[0]=-1;
            for(unsigned long long* thiscomponent: *components){
                unsigned int *cdepth = new unsigned int[2];
                cotree* child = new cotree(g, thiscomponent, !this->state,cdepth, depthdict);
                
                this->depth[0]= (cdepth[1] + 1 < this->depth[0]? cdepth[1] + 1 : this->depth[0]);
                this->depth[1]= (cdepth[1] + 1 > this->depth[1]? cdepth[1] + 1 : this->depth[1]);
                
                this->childs.push_back(child);
            }
            //this->depth[1]++;
        }else{
            this->virtualData[0].id= (this->state? 1:0);
        }
}
cotree::cotree(graph* g, vector<vector<cotree*>> *depthdict){
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
    this->constructChildren(g,&components,depthdict);
    this->writeInDepthDict(depthdict);
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