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
#include "cotree.h"
#include <vector>
/*
 * 
 */
int main(int argc, char** argv) {
    graph *g = new graph("src/data/problem.graph"); 
    //graph *g = new graph("src/data/graph2.graph"); 
    std::cout << g->get_string()<< std::endl;
    vector<vector<cotree*>> depthdict;
    cotree * gt = new cotree(g, depthdict);
    std::cout << "\nTree: \n\n"<< gt->get_string() <<std::endl;
    vector<vector<cotree*>> f = gt->getFactors();

    std::cout << "###############################" << std::endl;
    for(vector<cotree*> factorline : f){
        for(cotree* factor : factorline){
            std::cout << factor->get_string() << std::endl << "– – – – – – – – – – – – – – - -" << std::endl;
        }
        std::cout << "###############################" << std::endl;
    }
    
    
    return 0;
}

