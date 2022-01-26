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
#include "gtree.h"
#include <vector>
/*
 * 
 */
int main(int argc, char** argv) {
    graph *g = new graph("src/data/problem.graph"); 

    std::cout << g->get_string()<< std::endl;
    
    gtree * gt = new gtree(g);
    gt->computeFactorizations();
    std::cout << "\nTree: \n\n"<< gt->get_string() <<std::endl;

    
    return 0;
}

