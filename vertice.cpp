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

#include "vertice.h"

vertice::vertice(int num) {
    this->num =num;
}
vertice::vertice(){
    this->num = 0;}

void vertice::setNum(int num){
    this->num = num;
}

string vertice::to_string(){
    return std::to_string(this->num);
}
int vertice::getNum(){
    return this->num;
}


vertice::~vertice() {
}

