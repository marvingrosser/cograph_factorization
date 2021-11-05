/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vertice.h
 * Author: marvin
 *
 * Created on October 27, 2021, 11:56 AM
 */

#ifndef VERTICE_H
#define VERTICE_H
#include <string>
#include <vector>
using namespace std;
using std::vector;
using std::string;
class vertice {
public:
    vertice();
    vertice(int num);
    virtual ~vertice();
    string to_string();
    string out_to_string();
    int getNum();
    void setNum(int num);
    void addConnection(vertice *vert);
    void visit();
    bool isVisited();
    void unvisit();
    vector<vertice*>* getConnections();
private:
    int num;
    vector<vertice*> out;
    bool visited;

};

#endif /* VERTICE_H */

