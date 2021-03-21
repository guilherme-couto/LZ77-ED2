#include <stdio.h>

#include "../include/Dicionario.h"

#define TAM_DICIO 6

using namespace std;

Dicionario::Dicionario()
{
    vetor = new char[TAM_DICIO];
}

Dicionario::~Dicionario()
{
    delete [] vetor;
}

void Dicionario::insereNoFinal(char c)
{
    for (int i = 1; i < TAM_DICIO; i++) 
        vetor[i - 1] = vetor[i]; //abre espaço na esquerda
    vetor[TAM_DICIO - 1] = c;
}
