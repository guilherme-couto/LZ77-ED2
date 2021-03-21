#ifndef JANELA_H
#define JANELA_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/Dicionario.h"
#include "../include/Buffer.h"

using namespace std;

class Janela
{
public:
    Janela();
    ~Janela();

    ifstream arquivo;
    Buffer *buffer;
    Dicionario *dicio;
    vector<string> infoCodificada;

    void codifica();
    void deslocaJanela(int qntsEspacos);
    void restoDoBuffer();
    void imprimeJanela();
};

#endif //JANELA_H