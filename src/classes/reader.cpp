/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reader.cpp
 * Author: marvin
 * 
 * Created on October 25, 2021, 2:33 PM
 */

#include "../headers/reader.h"


reader::reader(string path) {
    this->path = path;
}

string reader::readFileToString(string path){
    string doc = "";
    string line;
    ifstream file (path);

  
    if (file.is_open()){
        while ( getline (file,line) ){
            doc.append(line);
            doc.push_back('\n');
        }
        doc.push_back('\0');
        
        file.close();
    }else{
        std::cout << "Unable to open file: " << path << std::endl;
    }
    return doc;
}
GraphBinary reader::getData(){
    
    return this->readBinaryFromFile();
}
reader::reader(const reader& orig) {
}

reader::~reader() {
}

GraphBinary reader::readBinaryFromFile(){
    string fileEnding = path.substr(path.rfind('.')+1);
    GraphBinary graphData;
    if(fileEnding == "graph"){
        graphData = this->readBinaryFromGraphFile();
    }
    return graphData;
}

GraphBinary reader::readBinaryFromGraphFile(){
    GraphBinary graphData;
    
    string file = this->readFileToString(this->path);
    
    
    
    graphData.number = std::stoi(file.substr(0,file.find('\n')));
    
    graphData.edges = new unsigned long long[(int)(graphData.number*graphData.number/DATA_SIZE)];
    
    file = file.substr(file.find('\n'));
    
    while(file.find('\n') != string::npos){
        unsigned short index =  file.find('\n');
        file.erase(file.begin() + index);
        //file.erase(index+1);
    }
    
    for(int i = 0; i < file.size()-1; i++){
        //char at = file.at(i);
        //std::cout << file.at(i) << std::endl ;
        //std::cout << ((int)file.at(i) - (int)'0')*0x80 << std::endl ;
        graphData.edges[i/DATA_SIZE] = graphData.edges[i/DATA_SIZE] << 1;
        graphData.edges[i/DATA_SIZE] = graphData.edges[i/DATA_SIZE]  | (((int)file.at(i)) - (int)'0');
    }

    
    
    return graphData;
}