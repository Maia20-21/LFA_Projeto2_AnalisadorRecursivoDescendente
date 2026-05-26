/*
 * GRUPO:
 * Bruna Amorim Maia - 10431883
 * Caio Guilherme dos Santos Silva - 10420097
 * Fabyani Tiva Yan - 10431835 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char lookahead;

int pos_erro_max = -1;

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
        if (*pos > pos_erro_max)
            pos_erro_max = *pos;
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

int T(char palavra[], int *pos) {
    if (F(palavra, pos) &&
        Z(palavra, pos))
        return 1;
    else
        return 0;
}
//divisao e multiplicacao
int Z(char palavra[], int *pos) {
    if (lookahead == '*') {
        if (match('*', palavra, pos) &&
            T(palavra, pos) &&
            Z(palavra, pos))
            return 1;
        else
            return 0;

    } else if (lookahead == '/') {
        if (match('/', palavra, pos) &&
            T(palavra, pos) &&
            Z(palavra, pos))
            return 1;
        else
            return 0;

    } else {
        return 1;
    }
}
//fator simples
int F(char palavra[], int *pos) {
    if (lookahead == '(') {
        if (match('(', palavra, pos) &&
            E(palavra, pos) &&
            match(')', palavra, pos))
            return 1;
        else
            return 0;

    } else if (lookahead >= '0' && lookahead <= '9') {
        if (N(palavra, pos))
            return 1;
        else
            return 0;

    } else {
        return 0;
    }
}
//numeros
int N(char palavra[], int *pos) {
    if (lookahead >= '0' && lookahead <= '9') {
        match(lookahead, palavra, pos);

        if (lookahead >= '0' && lookahead <= '9') {
            N(palavra, pos);
        }

        return 1;
    }

    return 0;
}

void tratarErro(char palavra[], int pos) {
    int pos_real = (pos_erro_max >= 0) ? pos_erro_max : pos;

    int len = (int)strlen(palavra);
    if (pos_real >= len) pos_real = len - 1;

    char encontrado = palavra[pos_real];

    const char *esperado = NULL;

    if (encontrado == '$') {
        esperado = "numero, '(' ou operador (+, -, *, /)";
        printf("\n");
        printf("ERRO: Expressão Incompleta\n");
        printf("A expressão termina abruptamente na posição %d.\n", pos_real);
        printf("Esperado: %s\n", esperado);
    }
    else if (encontrado != '+' && encontrado != '-' &&
            encontrado != '*' && encontrado != '/' &&
            encontrado != '(' && encontrado != ')' &&
            !(encontrado >= 0 && encontrado <= 9)) {
        esperado = "numero, operador (+,-,*,/) ou parentese";
        printf("\n");
        printf("ERRO na posição %d: caractere invalido.\n", pos_real);
        printf("Encontrado: '%c'\n", encontrado);
        printf("Esperado: %s\n", esperado);
    }

    else if (encontrado == '*' || encontrado == '/' ||
            encontrado == '+' || encontrado == '-') {
        if (pos_real > 0) {
            char anterior = palavra[pos_real - 1];
            if (anterior == '+' || anterior == '-' ||
                anterior == '*' || anterior == '/') {
                printf("\n");
                printf("ERRO na posição %d: operador duplicado ou invalido.\n", pos_real);
                printf("Encontrado: '%c' logo após '%c'\n", encontrado, anterior);
                printf("Esperado: numero ou '(' após o operador '%c'\n", anterior);
            } else {
                printf("\n");
                printf("ERRO na posição %d: operador inesperado.\n", pos_real);
                printf("Encontrado: '%c'\n", encontrado);
                printf("Esperado: numero, ')' ou fim da expressão.\n");
            }
        } else {
            printf("\n");
            printf("ERRO na posição %d: expressão não pode começar com operador.\n", pos_real);
            printf("Encontrado: '%c'\n", encontrado);
            printf("Esperado: numero ou '('\n");
        }
    }

    else if (encontrado == ')') {
        printf("\n");
        printf("ERRO na posição %d: ')' inesperado.\n", pos_real);
        printf("Encontrado: ')'\n");
        printf("Esperado: numero, operador ou '('\n");
        printf("Verifique se todos os parenteses estão balanceados.\n");
    }
        
    else if (encontrado == '(') {
        printf("\n");
        printf("ERRO na posição %d: '(' sem fechamento correspondente.\n", pos_real);
        printf("Encontrado: '('\n");
        printf("Esperado: expressão válida seguida de ')'\n");
        printf("Verifique se todos os parenteses estão balanceados.\n");
    }

    else {
        esperado = "operador (+,-,*,/), ')' ou fim da expressão '$'";
        printf("\n");
        printf("ERRO na posição %d: caractere inesperado\n", pos_real);
        printf("Encontrado: '%c'\n", encontrado);
        printf("Esperado: %s\n", esperado);
    }

    int exibir_len = len - 1;
    printf("\n");
    printf("Expressão: ");
    for (int i = 0; i < exibir_len; i++)
        printf("%c", palavra[i];
    printf("\n");

    printf("            ");
    for(int i = 0; i < pos_real && i < exibir_len; i++)
        printf(" ");
    printf("^\n");

    printf("\nResultado: Expressão Inválida.\n\n");

}
//COLOQUE AQUI A FUNCAO DE TRATAMENTO DE ERRO 

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
    pos_erro_max = 0;
    lookahead = expressao[pos];

    if (E(expressao, &pos) && lookahead == '$') {
        printf("Resultado: Expressao VALIDA! :-)\n\n");
    } else {
        tratarErro(expressao, pos);
    }

    system("PAUSE");
    return 0;
}
