//
//  Forest_Steiner.hpp
//  Steiner_Tree
//
//  Created by sergio junior on 12/11/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef Read_Instance_hpp
#define Read_Instance_hpp
#include<iostream>
#include <list>
#include <limits.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <list>
#include <algorithm> // função find
#include <stack> // pilha para usar na DFS
#include <dirent.h>
#include <sstream>
#include <sstream>
#include <ostream>
#include "Forest_Steiner.hpp"


int n_terminals(const char *path){
    std::ifstream file(path);
    
    int nterminals=0;
    int lines=0;
    if (file.is_open()){
        std::string line;
        while (getline(file, line)){
            if(lines>1){
                vector<string> sep = split(line, ' ');
                if(strncmp(sep[0].c_str(),"S",1)==0){
                    nterminals++;
                }
            }
            lines++;
        }
        file.close();
        
    }else{
        printf("Solution file with error!\n");
    }
    
    
    return nterminals;
}

int n_edges(const char *path){
    std::ifstream file(path);
    int edges=0;
    if (file.is_open()){
        std::string line;
        while (getline(file, line)){
            vector<string> sep = split(line, ' ');
            if(strncmp(sep[0].c_str(),"E",1)==0){
                edges++;
            }
        }
        file.close();
        
    }else{
        printf("Solution file with error!\n");
    }
    
    
    return edges;
}

void split_file_Instance(const char *path,const char *path2, int V,int terminals){
    for(int i=0;i<terminals;i++){
        std::ifstream file(path);
        ofstream myfile;
        std::string buf(string(path2)+"T_"+ to_string(i)+".txt");
        myfile.open (buf, std::ios_base::app);
        int lines=0;
        if (file.is_open()){
            std::string line;
            while (getline(file, line)){
                if (lines==0){
                    vector<string> sep = split(line, ' ');
                    myfile << "Nodes "+sep[1]+"\n";
                }else{
                    if(lines==1){
                        string str= to_string(V-1);
                        myfile << "Edges "+str+"\n";
                    }else{
                        if(lines<V+1){
                            vector<string> sep = split(line, ' ');
                            myfile << "E "+to_string(std::atoi(sep[1].c_str())+1)+" "+to_string(std::atoi(sep[2].c_str())+1)+" "+to_string(std::atoi(sep[3].c_str()))+"\n";
                        }else{
                            vector<string> sep = split(line, ' ');
                            if(strncmp(sep[0].c_str(),"S",1)==0){
                                if(i==0){
                                    myfile << "\n";
                                    myfile << "Terminals "+ to_string(sep.size()-1) +"\n";
                                    int cont=1;
                                    while(cont<sep.size()){
                                        myfile << "T "+to_string(std::atoi(sep[cont].c_str())+1)+"\n";
                                        cont++;
                                    }
                                    break;
                                }else{
                                    if(lines==V+1+i){
                                        myfile << "\n";
                                        myfile << "Terminals "+ to_string(sep.size()-1) +"\n";
                                        int cont=1;
                                        while(cont<sep.size()){
                                            myfile << "T "+to_string(std::atoi(sep[cont].c_str())+1)+"\n";
                                            cont++;
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                lines++;
            }
            myfile.close();
            file.close();
        }else{
            printf("Solution file with error!\n");
        }
    }
}


  
#endif /* Forest_Steiner_hpp */
