# Projeto 2 — Analisador Sintático Recursivo Descendente
## Linguagens Formais e Autômatos — 2026-1

Implementação em linguagem C (padrão ANSI) de um analisador sintático recursivo descendente para expressões numéricas com os operadores `+`, `-`, `*` e `/`, respeitando a precedência usual entre eles e suportando expressões entre parênteses.

### Informações do Grupo

| Integrante | RA |
| :--- | :--- |
| Caio Guilherme dos Santos Silva | 10420097 |
| Bruna Amorim Maia | 10431883 |
| Fabyani Tiva Yan | 10431835 |

---

### Estrutura do Projeto

```
/proj2-analisador/
│
├── README.md
├── analisador.c
└── entrada.txt
```

- **`analisador.c`**: Código-fonte completo do analisador.
- **`entrada.txt`**: Arquivo com a expressão numérica a ser analisada. Deve estar na mesma pasta do executável.

---

### Gramática Implementada

| Regra | Produção |
| :--- | :--- |
| E | → T K |
| K | → + E K \| - E K \| ε |
| T | → F Z |
| Z | → \* T Z \| / T Z \| ε |
| F | → ( E ) \| N |
| N | → 0\|1\|2\|...\|9 \| 0N\|1N\|...\|9N |

> `ε` representa a palavra vazia — o símbolo pode não gerar nada, sem erro.

---

### Detalhes da Implementação

| Componente | Descrição |
| :--- | :--- |
| **`match()`** | Verifica se o `lookahead` atual é o caractere esperado e avança para o próximo. |
| **`E()` e `K()`** | Reconhecem somas e subtrações respeitando a associatividade. |
| **`T()` e `Z()`** | Reconhecem multiplicações e divisões com precedência sobre `+` e `-`. |
| **`F()`** | Reconhece um fator: número isolado ou expressão entre parênteses. |
| **`N()`** | Reconhece sequências de dígitos (números com múltiplos algarismos). |
| **`trataErro()`** | Exibe mensagem informativa indicando a posição e o tipo do erro encontrado. |
| **`lookahead`** | Variável global que guarda o caractere sendo analisado no momento. |

---

### Compilação

No DEV-C++ para Windows, abra o arquivo `analisador.c` e pressione **F9**.

Ou via terminal (gcc):

```bash
gcc analisador.c -o analisador
```

---

### Execução

Crie o arquivo `entrada.txt` na mesma pasta do executável com a expressão a ser analisada:

```
3+2*5
```

Então execute:

```bash
./analisador
```

---

### Exemplos de Entrada e Saída

**Expressão válida:**
```
Expressao lida: 3+2*5$
Analisando...

Resultado: Expressao VALIDA! :-)
```

**Expressão inválida:**
```
Expressao lida: 3+*5$
Analisando...

ERRO na posicao 2: caractere inesperado '*'
```

---

### Exemplos de Expressões

| Expressão | Resultado |
| :--- | :--- |
| `3+2` | Válida |
| `10*5-4` | Válida |
| `(3+2)*4` | Válida |
| `100/4+3*(2-1)` | Válida |
| `3+` | Inválida — falta operando |
| `(3+4` | Inválida — parêntese não fechado |
| `5**2` | Inválida — operador duplicado |

---

