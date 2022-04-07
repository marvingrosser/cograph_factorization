/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputHandler.cpp
 * Author: marvin
 * 
 * Created on April 5, 2022, 11:24 AM
 */

#include "InputHandler.h"

InputHandler::InputHandler(string arguments) {
    this->input = "";
    this->output = "";
    unsigned int i = 0;
    
    while(i < arguments.size()){
        int minus_index = arguments.find('-', i);
        if(arguments.at(minus_index + 1)=='-'){
            
            int next_spaceIndex = arguments.find(' ', minus_index + 2);
            int next_minusIndex = arguments.find('-', next_spaceIndex);
            
            string argName = arguments.substr(minus_index + 2, next_spaceIndex - minus_index -  2  );
            
            
            
            if(argName == "help"){
                this->handleHelp();
                i = minus_index + 2;
            }else{
                int first_QTM = arguments.find('"', next_spaceIndex);
                int second_QTM = arguments.find('"', first_QTM + 1);
                if(first_QTM < next_minusIndex && second_QTM < next_minusIndex){
                    std::cout << "Please use \" \" for filepaths" << std::endl;
                    
                    break;
                }
                
                string arg = arguments.substr(first_QTM + 1,second_QTM - first_QTM - 2);
                
                if (argName == "input"){
                    this->handleFileI(arg);
                    i = second_QTM + 1;
                }else if(argName == "output"){
                    this->handelFileO(arg);
                    i = second_QTM + 1;
                }else{
                    std::cout << "The command was written poorly. Please try again" << std::endl;
                    this->handleHelp();
                    
                    break;
            }
            } 
            
        }else{
            i = minus_index + 2;
        }
    }
    
    if(this->input==""){
        return;
    }else{
        this->calculate();
    }
    
    
}
InputHandler::InputHandler(char* arguments){
    
}
InputHandler::InputHandler(const InputHandler& orig) {
}

void InputHandler::calculate(){
    graph *g = new graph(this->input);
}

InputHandler::~InputHandler() {
}
void InputHandler::handleHelp(){
    std::cout << "Help:" << std::endl;
}
void InputHandler::handleFileI(string file){
    this->input = file;
}

void InputHandler::handelFileO(string file){
    this->output = file;
}

