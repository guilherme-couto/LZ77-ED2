#include <stdio.h>

#include "../include/Buffer.h"

#define TAM_BUFFER 4

using namespace std;

Buffer::Buffer()
{
    vetor = new char[TAM_BUFFER];
}

Buffer::~Buffer()
{
    delete[] vetor;
}

void Buffer::insereNoFinal(char c)
{
    for(int i = 1; i < TAM_BUFFER; i++)
        vetor[i - 1] = vetor[i]; //abrindo espaço na esquerda
    vetor[TAM_BUFFER - 1] = c; //coloca o c no final   
}

