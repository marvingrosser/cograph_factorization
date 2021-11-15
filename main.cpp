/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: marvin
 *
 * Created on October 25, 2021, 2:32 PM
 */

#include <cstdlib>

using namespace std;
#include "graph.h"
#include <vector>
/*
 * 
 */
int main(int argc, char** argv) {
    graph *g = new graph("src/data/graph1.graph"); //wtf wenn das kein pointer ist passiert was mit dem speicher was ich nicht mag
    vector<vector<vertice*>> cons = g->getConnected();
    std::cout << g->get_string()<< std::endl;
    for(int i=0; i < cons.size(); i++){
        std::cout << "Connected:\t" << (*new graph(cons.at(i))).get_string() << std::endl;
    }
    
    return 0;
}

