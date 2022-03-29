/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   int_multiset.h
 * Author: marvin
 *
 * Created on March 5, 2022, 1:08 PM
 */

#ifndef INT_MULTISET_H
#define INT_MULTISET_H
#include <cstdlib>
#include <set>
struct ituple{
    unsigned int index;
    unsigned int count;
};

class int_multiset {
public:
    int_multiset();
    std::set<unsigned int> getSet();
    int_multiset(unsigned int length);
    void add(unsigned int index);
    unsigned int getCount(unsigned int index);
    int compareI(int_multiset t1, int_multiset t2);
    unsigned int getLength();
private:
    ituple *  data; 
    unsigned int length;
};

#endif /* INT_MULTISET_H */

