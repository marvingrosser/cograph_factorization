/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   int_multiset.cpp
 * Author: marvin
 * 
 * Created on March 5, 2022, 1:08 PM
 */

#include "int_multiset.h"

int_multiset::int_multiset(unsigned int length) {
    this->data = (ituple*) malloc(length* sizeof(ituple));
    this->length = length;
    for(unsigned int i = 0; i < length; i++){
        this->data[i].index = i;
        this->data[i].count = 0;
    }
}
unsigned int int_multiset::getLength(){
    return this->length;
}
void int_multiset::add(unsigned int index){
    this->data[index].count++;
}
unsigned int int_multiset::getCount(unsigned int index){
    return this->data[index].count;
}
int int_multiset::compareI(int_multiset t1, int_multiset t2){
    for(unsigned int i=0; i < t1.length; i++){
        if((t1.getCount(i) !=0 && t2.getCount(i) != 0) ||  t2.getCount(i) == t1.getCount(i) ){
            continue;
        }else{
            return  (t1.getCount(i)>t2.getCount(i)?1:-1);
        }
    }
    return 0;
}