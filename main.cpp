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
#include "cograph.h"
#include "cotree.h"
#include <vector>
/*
 * 
 */
int main(int argc, char** argv) {
    //graph *g = new graph("src/data/k12.graph"); 
    graph *g = new graph("src/data/graph2.graph"); 
    std::cout << g->get_string()<< std::endl;
    vector<vector<cotree*>> depthdict;
    cotree * gt = new cotree(g, &depthdict);
    std::cout << "\nTree: \n\n"<< gt->get_string() <<std::endl;
    vector<vector<cotree*>> factors = gt->getFactors(depthdict);

    std::cout << "###############################" << std::endl;
    for(vector<cotree*> fline : factors){
        for(cotree* fac: fline){
            std::cout << fac->get_string() << std::endl;
            std::cout << "---------------------------------------" << std::endl;
        }
        std::cout << "#######################################" << std::endl;
    }
    
    
    return 0;
}

