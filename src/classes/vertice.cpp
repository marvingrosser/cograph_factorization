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

#include "../headers/vertice.h"
graph* vertice::getGraph(){
    return this->g;
}



vertice::vertice(int num) {
    this->num =num;
    this->out= NULL;


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
    if(this->out==NULL ){
    	return "";
    }
       for(int i=0 ; i < this->g->getSize();i++ ){
        if((this->out[(int)(((int)i)/((int)DATA_SIZE)) ] >> ((int)DATA_SIZE - 1 - (int)(((int)i) % ((int)DATA_SIZE)))) % 2 ){
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
	if(this->out != NULL){
		free( this->out );
	}

}
void vertice::setGraph(graph* g){
    this->g = g;
}

void vertice::initOut(unsigned short number){
    this->out = (unsigned long long *)calloc(number/DATA_SIZE +1 ,DATA_SIZE/8);
    this->out[0] = (unsigned long long)0;
    
}
void vertice::setOneInOut(unsigned short index){
    this->out[(int) (((int)index)/((int)DATA_SIZE))] |= ((unsigned long long) 1  << ((int)DATA_SIZE - 1 - (int)(((int)index) % ((int)DATA_SIZE))))  ;
    
    //std::cout << "versch: " <<(((int)DATA_SIZE - 1 - (int)(((int)index) % ((int)DATA_SIZE))))<< std::endl;
    
}

unsigned long long* vertice::getConnections(){
    return this->out;
}
