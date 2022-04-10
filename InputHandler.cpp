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
void InputHandler::init(char** args, int argnum){
    this->input = "";
    this->output = "";
    unsigned int i = 0;
    this->si = false;
    if(argnum==1)this->handleHelp();
    for(unsigned int i = 1; i < argnum; i++){
        if(strcmp(args[i],"--input") == 0 || strcmp(args[i], "-i") == 0){
            i++;
            this->input = *new string(args[i]);
        }else if (strcmp(args[i],"--output") == 0 || strcmp(args[i], "-o") == 0){
            this->output = *new string(args[i]);
            i++;
        }else if(strcmp(args[i],"--help") == 0 || strcmp(args[i], "-h") == 0){
            this->handleHelp();
        }else if(strcmp(args[i],"--print") == 0 || strcmp(args[i], "-p") == 0){
            this->si = true;
        }else{
            std::cout << "Fehlerhafte Eingabe: \"" << args[i] << "\"" << std::endl;
            this->handleHelp();
        }
    }
    
    if(this->input != ""){
         this->calculate();
    }
    
    
}

InputHandler::InputHandler(char** arguments, int argnum){
    this->init(arguments, argnum);
}
InputHandler::InputHandler(const InputHandler& orig) {
}

void InputHandler::calculate(){
    graph *g = new graph(this->input);
    
    
    
    
    vector<vector<cotree*>> depthdict;
    cotree * gt = new cotree(g, &depthdict);
    if(this->si){
        std::cout << "\n Input cograph:" << std::endl;
        std::cout << g->get_string()<< std::endl;
        std::cout << "\n\n Corresponding cotree: \n\n"<< gt->get_string() <<std::endl;
    }
    vector<vector<cotree*>> factors = gt->getFactors(depthdict);

    std::cout << "\n\n#######################################\n\n" << std::endl;
    for(unsigned int fli = 0; fli < factors.size(); fli++){
        std::cout << "\nFactorization Nr. " << fli+1 <<"\n-----------------\n"<< std::endl;
        for(int fi = factors[fli].size()-1; fi >=0;){
            std::cout << factors[fli][fi]->get_string() << std::endl;
            if(fi > 0){
                std::cout << "- - - - - - - - - - - - - - - - - - - -\n" << std::endl;
            }
            fi--;
        }
        std::cout <<         "\n" << std::endl;
    }
    if(this->output != ""){
    
    }
}

InputHandler::~InputHandler() {
}
void InputHandler::handleHelp(){
    std::cout << "\nUsage:" << std::endl;
    std::cout << "\tcgfactorization [args]" << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "\tcgfactorization --input \"graph3.graph\" -pi" << std::endl;
    std::cout << "\nArguments:" << std::endl;
    std::cout << "\n\t --help \t\t -h \t\t\t\t show this page" << std::endl;
    std::cout << "\n\t --printinput \t\t -p \t\t\t\t print the inputgraph and tree" << std::endl;
    std::cout << "\n\t --input \"filepath\"\t -i \"filepath\"\t\t\t input cograph as file (adjacency matrix)" << std::endl;
    std::cout << "\n\t --output \"dirpath\"\t -o \"dirpath\"\t\t\t output path for factors as \n\t\t\t\t\t\t\t\t adjacency matrices (f1.graph, f2.graph,...)\n\n" << std::endl;
}
void InputHandler::handleFileI(string file){
    this->input = file;
}

void InputHandler::handelFileO(string file){
    this->output = file;
}

