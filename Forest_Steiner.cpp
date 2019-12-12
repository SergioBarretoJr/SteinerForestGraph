//
//  Forest_Steiner.cpp
//  Steiner_Tree
//
//  Created by sergio junior on 12/11/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#include "Forest_Steiner.hpp"
#include "Read_Instance.hpp"
#include<iostream>
#include <list>
#include <limits.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <dirent.h>
#include <experimental/filesystem>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include<unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=5){
        printf("Argumentos Faltando\n Por favor inserir:\n - caminho da instância;\n - nome da instância\n - número de iterações\n - seed .");
        printf("\nEx.: ./main /home/Luftschlange-ms-steiner-puw-324769b/bin jmp-n-50-a-160-p-025-k-5-s-4731.dat 100 1\n");
    }else{
        std::string str_path=argv[1]; //Caminho onde as instâncias estão
        std::string inst=argv[2]; //Nome da instância
        std::string turns=argv[3]; //Numero de iterações
        std::string seed=argv[4]; //semente
        std::string intancia(str_path+"/"+inst); //caminho do arquivo instância
    
        std::string str_path_split=str_path+"/Instance_"; //formato do nome do arquivo após split
        
        int nterminais=n_terminals(intancia.c_str()); //extraindo número de conjunto de terminais
        int nEdges=n_edges(intancia.c_str()); //extraindo número de edges
        printf("ntermianis %d - edges %d\n",nterminais,nEdges);
        
        split_file_Instance(intancia.c_str(),str_path_split.c_str(),nEdges,nterminais); //split do arquivo da floresta de steiner
        
        ///////////////////// Executando Algoritmo da Árvore de Steiner ///////////////////////////
        chdir(str_path.c_str()); //mudança de diretório
        std::string  str;
        std::string  str2;
        std::string  strPy;
        
        auto start = std::chrono::system_clock::now();
        for (int i=0;i<nterminais;i++){
            str = "./steiner ";
            str2 = str+" " +str_path+"/Instance_T_"+to_string(i)+".txt -msit "+turns+" -seed "+seed;
            system(str2.c_str());
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        Grafo g1(nEdges+1);
        vector<string> s;
        std::string buf(str_path+"/");
        
        s=list_dir(str_path.c_str()); //montando vetor com nome dos arquivos da pasta onde é salvo a solução
        
        /////////////////////////////////////  Unindo árvores em um único grafo /////////////////////////////////////////
        for (int i=0;i<s.size();i++){
            vector<string> sep = split(s.at(i), '.');
            if(strncmp(sep.back().c_str(),"sol",1)==0 && int(sep.size())>2){
                
                std::string path1=s.at(i);
                printf("%s\n",path1.c_str());
                read_file(buf.c_str(),path1.c_str(),&g1);
            }
        }
        
        stack<int> listg1;
        int Component_connected=0;
        
        printf("Structure Before Prim\n");
        print_struct(str_path.c_str(),&g1); // print da estrutura unida
        
        Grafo gFinal(nEdges);
        
        g1.ConnecComp(listg1,&Component_connected,&gFinal); // retirando cilos das componentes conexas
        
        printf("Final Solution Find!\n");
        print_struct(str_path.c_str(),&gFinal); // print da estrutura final
        
        /////////////////////////////////////  Medindo tempo total do algoritmo /////////////////////////////////////////
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "finished computation at " << std::ctime(&end_time)
                  << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    return 0;
}
