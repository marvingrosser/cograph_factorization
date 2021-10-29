/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   edge.h
 * Author: marvin
 *
 * Created on October 27, 2021, 11:56 AM
 */

#ifndef EDGE_H
#define EDGE_H

#include <string>

using namespace std;

using std::string;

class vertice;

class edge {
public:
    edge(vertice *from, vertice *to);
    edge();
    void set(vertice* from, vertice* to);
    string to_string();
    edge(const edge& orig);
    virtual ~edge();
private:
    vertice* from;
    vertice* to;
};

#endif /* EDGE_H */

