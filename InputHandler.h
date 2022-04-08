/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputHandler.h
 * Author: marvin
 *
 * Created on April 5, 2022, 11:24 AM
 */

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "cotree.h"
#include "cograph.h"
#include <string.h>
#include <vector>
/**
 * Input Handler for Arguments: (Path to GraphFile, help, save to File, Print Output)
 */
class InputHandler {
public:

    InputHandler(char** arguments, int argnum);
    InputHandler(const InputHandler& orig);
    virtual ~InputHandler();
private:
    void init(char** args, int argnum);
    void handleHelp();
    void handleFileI(string file);
    void handelFileO(string file);
    void calculate();
    string input;
    string output;
    bool si;

};

#endif /* INPUTHANDLER_H */

