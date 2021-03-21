#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include "../include/Dicionario.h"
#include "../include/Buffer.h"
#include "../include/Janela.h"

#define TAM_BUFFER 4
#define TAM_DICIO 6

using namespace std;

Janela::Janela()
{
    buffer = new Buffer();
    dicio = new Dicionario();
    infoCodificada.clear();
}

Janela::~Janela()
{
    delete buffer;
    delete dicio;
}

void Janela::codifica()
{
    //abre o arquivo
    cout << "Insira o nome do arquivo a ser codificado: ";
    string nomeArqv;
    cin >> nomeArqv;
    arquivo.open(nomeArqv);

    //enche o buffer
    int i = 0;
    cout << "\nEnchendo o buffer: ";
    while (!arquivo.eof() && i < TAM_BUFFER)
    {
        buffer->vetor[i] = arquivo.get();
        cout << buffer->vetor[i] << " | ";
        i++;
    }
    cout << "\n"
         << endl;

    //começa o processo de codificação
    while (!arquivo.eof())
    {
        int p = 0, l = 0; //campos do formato codificado
        char c;
        int indexOcorrencia;

        vector<char> vetAux(dicio->vetor, dicio->vetor + TAM_DICIO); //vetor auxiliar que pega só os elementos do dicionario
        vector<char>::iterator it;                                   //iterador para passar pelo vector

        int numCaracteres = TAM_BUFFER;

        while (numCaracteres > 0)
        {
            it = find_end(vetAux.begin(), vetAux.end(), buffer->vetor, buffer->vetor + numCaracteres); //aponta para a posição onde encontra a ultima sequencia no vetAux que seja igual ao vetor do buffer

            if (it != vetAux.end()) //caso exista uma ocorrencia
            {
                indexOcorrencia = it - vetAux.begin();
                p = TAM_DICIO - indexOcorrencia;
                l = numCaracteres;

                if (l + indexOcorrencia >= TAM_DICIO) //quando está no final do dicionario, será p < l
                {
                    int aux = indexOcorrencia;
                    while (dicio->vetor[aux] == buffer->vetor[l] && l < TAM_BUFFER) //pega as repetições do dicionario enquanto for combatível com a sequência do buffer
                    {
                        l++;
                        if ((aux++) == TAM_DICIO)
                            aux = indexOcorrencia;
                    }
                }
                break;
            }
            numCaracteres--;
        }

        if (l == 0) //se não encontrar nenhuma ocorrencia de nenhum elemento do buffer no dicio, o c será o primeiro elemento do buffer
            c = buffer->vetor[0];
        else if (l == TAM_BUFFER) //caso todos os elementos do buffer estejam no dicio, c será o primeiro caractere fora do buffer
            c = arquivo.peek();   //peek, pois o get atrapalharia o deslocamento da janela dps
        else                      //caso contrário, com p > l, c será o elemento seguinte à subsequencia do buffer que voi encontrada no dicio
            c = buffer->vetor[l]; // vetor na posição l, o caracter que nao foi inserido

        imprimeJanela();

        cout << "  ->  (" << p << ", " << l << ", " << c << ")" << endl;
        infoCodificada.push_back("(" + to_string(p) + ", " + to_string(l) + ", " + c + ")"); //prepara a saída no formato certo
        deslocaJanela(l + 1);
        cout << endl;
    }
    restoDoBuffer();
}

void Janela::deslocaJanela(int qntd)
{
    int cont = 0;
    while (!arquivo.eof() && cont < qntd)
    {
        dicio->insereNoFinal(buffer->vetor[0]);
        buffer->insereNoFinal(arquivo.get());
        cont++;
    }
}

void Janela::restoDoBuffer()
{
    while (buffer->vetor[0] != '\0')
    {
        int p = 0, l = 0; //campos do formato codificado
        char c;
        int indexOcorrencia;

        vector<char> vetAux(dicio->vetor, dicio->vetor + TAM_DICIO); //vetor auxiliar que pega só os elementos do dicionario
        vector<char>::iterator it;                                   //iterador para passar pelo vector

        int numCaracteres = TAM_BUFFER;

        while (numCaracteres > 0)
        {
            it = find_end(vetAux.begin(), vetAux.end(), buffer->vetor, buffer->vetor + numCaracteres); //aponta para a posição onde encontra a ultima sequencia no vetAux que seja igual ao vetor do buffer

            if (it != vetAux.end()) //caso exista uma ocorrencia
            {
                indexOcorrencia = it - vetAux.begin();
                p = TAM_DICIO - indexOcorrencia;
                l = numCaracteres;

                if (l + indexOcorrencia >= TAM_DICIO) //quando está no final do dicionario, será p < l
                {
                    int aux = indexOcorrencia;
                    while (dicio->vetor[aux] == buffer->vetor[l] && l < TAM_BUFFER) //pega as repetições do dicionario enquanto for combatível com a sequência do buffer
                    {
                        l++;
                        if ((aux++) == TAM_DICIO)
                            aux = indexOcorrencia;
                    }
                }
                break;
            }
            numCaracteres--;
        }

        if (l == 0) //se não encontrar nenhuma ocorrencia de nenhum elemento do buffer no dicio, o c será o primeiro elemento do buffer
            c = buffer->vetor[0];
        else if (l == TAM_BUFFER) //caso todos os elementos do buffer estejam no dicio, c será o primeiro caractere fora do buffer
            c = arquivo.peek();   //peek, pois o get atrapalharia o deslocamento da janela dps
        else                      //caso contrário, com p > l, c será o elemento seguinte à subsequencia do buffer que voi encontrada no dicio
            c = buffer->vetor[l]; // vetor na posição l, o caracter que nao foi inserido

        imprimeJanela();

        cout << "  ->  (" << p << ", " << l << ", " << c << ")" << endl;
        if (c == '\0' || c == ' ')
            infoCodificada.push_back("(" + to_string(p) + ", " + to_string(l) + ", Null)");
        else
            infoCodificada.push_back("(" + to_string(p) + ", " + to_string(l) + ", " + c + ")"); //prepara a saída no formato certo

        int cont = 0;
        while (cont < l + 1)
        {
            dicio->insereNoFinal(buffer->vetor[0]);
            buffer->insereNoFinal('\0');
            cont++;
        }
        cout << endl;
    }
}

void Janela::imprimeJanela()
{
    cout << "Dicio|-|Buffer = ";
    for (int i = 0; i < TAM_DICIO; i++)
    {
        cout << dicio->vetor[i] << " | ";
    }
    cout << "-";
    for (int i = 0; i < TAM_BUFFER; i++)
    {
        cout << " | " << buffer->vetor[i];
    }
}