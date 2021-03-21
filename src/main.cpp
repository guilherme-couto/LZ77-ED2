#include <stdio.h>
#include <iostream>

#include "../include/Janela.h"

using namespace std;

int main()
{
    Janela *janela = new Janela();
    janela->codifica();

    cout << "\n";
    cout << "SAIDA -> ";
    for (int i = 0; i < janela->infoCodificada.size(); i++)
    {
        cout << janela->infoCodificada[i] << " ";
    }
    cout << endl;

    return 0;
}