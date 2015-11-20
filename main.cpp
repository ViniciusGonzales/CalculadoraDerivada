#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stack>

enum TipoAtomo
{
    NUMERO, OPERADOR_SOMA, OPERADOR_MULTIPLICACAO, ABRE_PARENTESES, FECHA_PARENTESES, FUNCAO
};

class Atomo
{
private:
    float valor;
    std::string expressao;
    TipoAtomo tipo;

public:
    Atomo(float valor);

    Atomo(std::string expressao);

    TipoAtomo getTipo();

    float getValor();

    std::string getExpressao();
};

class Funcao
{
private:
    Funcao argumento();
    float coeficiente;
    std::string ExpressaoDerivada;

public:
    Funcao(std::string argumento);

    float getCoeficiente(){ return coeficiente;};

    std::string getDerivada(){ return ExpressaoDerivada;};

    Funcao getArgumento(){ return argumento;};
};

class No
{
public:
    Atomo elemento;
    No* proximo;

    No();
};


int main()
{
    bool fim = false;
    std::string linha;
    while (!fim)
    {
        Fila funcao;
        Fila derivada;
        getline(std::cin, linha);
        // Verifica se o usuario digitou "fim"
        if (linha != "fim")
        {
            // Para evitar "lixo" da iteracao
            // anterior
            funcao.esvaziar();
            derivada.esvaziar();

            interpretarExpressao(linha, funcao);
            std::cout << "Derivada: ";
            imprimirFila(derivada);
            //float resultado = calcularDerivada(derivada);
            //std::cout << "Resultado: " << resultado << std::endl;
        }
        else
        {
            fim = true;
        }
    }

    return 0;
}

// NUMERO, OPERADOR_SOMA, OPERADOR_MULTIPLICACAO, ABRE_PARENTESES, FECHA_PARENTESES, FUNCAO

Atomo::Atomo(float valor) : valor(valor)
{
    tipo = NUMERO;
}

Atomo::Atomo(std::string expressao) : expressao(expressao)
{
    if (ehOperadorSoma(expressao[0]))
    {
        tipo = OPERADOR_SOMA;
    }
    else if (ehOperadorMultiplicacao(expressao[0]))
    {
        tipo = OPERADOR_MULTIPLICACAO;
    }
    else if (expressao.size() == 1 && expressao[0] == '(')
    {
        tipo = ABRE_PARENTESES;
    }
    else if (expressao.size() == 1 && expressao[0] == ')')
    {
        tipo = FECHA_PARENTESES;
    }
    else
    {
        tipo = FUNCAO;
    }
}

TipoAtomo Atomo::getTipo()
{
    return tipo;
}

float Atomo::getValor()
{
    return valor;
}

std::string Atomo::getExpressao()
{
    return expressao;
}

No::No() : elemento(Atomo('#'))
{
    proximo = NULL;
}

// Implementacao das funcoes

bool compoeNumero(char expressao)
{
    return (expressao >= '0' && expressao <= '9') || expressao == '.';
}

bool ehOperadorSoma(char expressao)
{
    return expressao == '+' || expressao == '-';
}

bool ehOperadorMultiplicacao(char expressao)
{
    return expressao == '*' || expressao == '/';
}

void interpretarExpressao(const std::string& linha, Fila& funcao)
{
    // Um numero pode possuir varios caracteres,
    // assim usamos um acumulador de caracteres
    // para guardar todos os caracteres de um certo numero
    std::stringstream acumulador;
    // Variavel booleana que indica se a funcao
    // esta lendo um numero
    bool lendoNumero = false;

    bool jaAbriuParentesis = false;

    for (int i = 0; i < linha.size(); ++i)
    {
        // Indexa um caractere da cadeia de caracteres linha
        char caractere = linha[i];

        if (caractere == ' ')
            continue; // Ignora ' '

        if (lendoNumero && !compoeNumero(caractere))
        {
            lendoNumero = false;
            float valor = atof(acumulador.str().c_str());
            funcao.inserir(Atomo(valor));
            // Reseta o acumulador
            acumulador.str("");
        }

        if (compoeNumero(caractere))
        {
            lendoNumero = true;
            acumulador << caractere;
        }
        else if(jaAbriuParentesis == true && caractere != '(')
        {
            jaAbriuParentesis = false;
            funcao.inserir(Atomo(acumulador.str()));
        }
        else if(jaAbriuParentesis == false && caractere == '(')
        {
            jaAbriuParentesis = true;
            acumulador << caractere;
        }
        else
        {
            funcao.inserir(Atomo(caractere));
        }
    }
}

void imprimirFila(Fila& derivada)
{
    // Enquanto vai tirando elementos da fila
    // polonesa, vai guardando estes elementos nesta
    // fila auxiliar
    Fila filaAuxiliar;
    while (!derivada.vazia())
    {
        Atomo primeiro = derivada.primeiro();
        if (primeiro.getTipo() == NUMERO)
            std::cout << primeiro.getValor() << " ";
        else
            std::cout << primeiro.getExpressao() << " ";
        filaAuxiliar.inserir(primeiro);
        derivada.remover();
    }
    // Todos os elementos originais de fila polonesa
    // estao em auxiliar, entao basta copia-los de volta
    // para a fila polonesa
    while (!filaAuxiliar.vazia())
    {
        derivada.inserir(filaAuxiliar.primeiro());
        filaAuxiliar.remover();
    }
    std::cout << std::endl;
}

float calcularDerivada(Fila& funcao)
{
    Pilha pilhaAux;
    float primeiro;
    float segundo;
    float resultado;
}
