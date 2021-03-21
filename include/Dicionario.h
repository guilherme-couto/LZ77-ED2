#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <stdio.h>

using namespace std;

class Dicionario
{
public:
    Dicionario();
    ~Dicionario();

    char *vetor;

    void insereNoFinal(char c);
};

#endif // DICIONARIO_H