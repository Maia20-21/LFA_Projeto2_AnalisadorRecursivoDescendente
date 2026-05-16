/*
 * GRUPO:
 * Bruna Amorim Maia - 10431883
 * Caio Guilherme dos Santos Silva - 10420097
 * Fabyani Tiva Yan - 10431835 
 */

#include <stdio.h>
#include <stdlib.h>

char lookahead;

// FUNÇOES GERAIS
int E(char palavra[], int *pos);
int K(char palavra[], int *pos);
int T(char palavra[], int *pos);
int Z(char palavra[], int *pos);
int F(char palavra[], int *pos);
int N(char palavra[], int *pos);
void tratarErro(char palavra[], int pos);

int match(char t, char palavra[], int *pos) {
    if (lookahead == t) {
        lookahead = palavra[++(*pos)];
        return 1;
    }
    return 0;
}

// FUNÇOES DOS NÃO TERMINAIS
int E(char palavra[], int *pos) {
    if (T(palavra, pos) &&
        K(palavra, pos))
        return 1;
    else
        return 0;
}

int K(char palavra[], int *pos) {
    if (lookahead == '+') {
        if (match ('+', palavra, pos) && 
        E(palavra, pos) &&
        K(palavra, pos))
        return 1;
    else
        return 0;
    } else if (lookahead == '-') {
        if (match('-', palavra, pos) &&
            E(palavra, pos) &&
            K(palavra, pos))
            return 1;
        else
            return 0;

    } else {
        return 1;
    }
}

// CONTINUE AS FUNÇOES DAS OUTRAS LETRAS AQUI!!!!






int main() {
    char expressao[1000];
    int pos = 0;
    FILE *arquivo;

    arquivo = fopen("entrada.txt", "r");

    if (arquivo == NULL) {
        printf("\nERRO: Arquivo 'entrada.txt' nao encontrado!\n");
        printf("Crie o arquivo com a expressao a ser analisada.\n\n");
        system("PAUSE");
        return 1;
    }

    if (fgets(expressao, 999, arquivo) == NULL) {
        printf("\nERRO: Arquivo 'entrada.txt' esta vazio!\n\n");
        fclose(arquivo);
        system("PAUSE");
        return 1;
    }

    fclose(arquivo);

    int i = 0;
    while (expressao[i] != '\0' && expressao[i] != '\n') {
        i++;
    }
    expressao[i]   = '$';
    expressao[i+1] = '\0';

    printf("\nExpressao lida: %s\n", expressao);
    printf("Analisando...\n\n");

    pos = 0;
    lookahead = expressao[pos];

    if (E(expressao, &pos) && lookahead == '$') {
        printf("Resultado: Expressao VALIDA! :-)\n\n");
    } else {
        tratarErro(expressao, pos);
    }

    system("PAUSE");
    return 0;
}