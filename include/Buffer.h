#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>

using namespace std;

class Buffer
{
public:
    Buffer();
    ~Buffer();

    char *vetor;

    void insereNoFinal(char c);
};

#endif // BUFFER_H