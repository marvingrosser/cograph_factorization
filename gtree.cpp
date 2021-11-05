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

gtree::gtree() {
}

gtree::gtree(const gtree& orig) {
}

gtree::~gtree() {
}

gtree* gtree::getChilds(){
    gtree* childs = new gtree[2]{*this->child1, *this->child2};
    return childs;
}
gtree* gtree::getChild1(){
    return this->child1;
}
gtree* gtree::getChild2(){
    return this->child2;
}
bool gtree::getState(){
    return this->state;
}
void gtree::setState(bool state){
    this->state = state;
}

void gtree::setChilds(gtree* child1, gtree* child2){
    this->child1 = child1;
    this->child2 = child2;
 }
void gtree::setChild1(gtree* child){
    this->child1 = child;
}
void gtree::setChild2(gtree* child){
    this->child2 = child;
}
