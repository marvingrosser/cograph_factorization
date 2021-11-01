/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gtree.h
 * Author: marvin
 *
 * Created on November 1, 2021, 2:12 PM
 */

#ifndef GTREE_H
#define GTREE_H
#include "vertice.h"

class gtree {
public:
    gtree();
    gtree(const gtree& orig);
    gtree* getChilds();
    bool getState();
    void setState(bool state);
    void setChilds(gtree *child1, gtree *child2);
    void setChild1(gtree* child);
    void setChild2(gtree*child);
    gtree* getChild1();
    gtree* getChild2();
    
    virtual ~gtree();
private:
    bool state; 
    gtree *child1;
    gtree *child2;
    
};

#endif /* GTREE_H */

