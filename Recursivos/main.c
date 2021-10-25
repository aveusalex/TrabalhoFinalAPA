#include <stdio.h>
#include <string.h>

#define MAX 112

int N, duracaoMusicas[MAX];

// criando a tabela de memoização:
int memo[MAX][60][60][60];  // a tabela de memoizacao está setada para o maior tamanho de entradas possível

// função que acha o valor maior entre dois valores (máximo binário).
int max(int num1, int num2){
    if (num1 < num2){
        return num2;
    }
    else{
        return num1;
    }
}

// função com programção dinâmica
int dp(int i, int car1, int car2, int car3){
    int ch1 = 0, ch2 = 0, ch3 = 0, ch4;  // escolhas de cada subproblema
    if (i == N){
        return 0;
    }
    if (memo[i][car1][car2][car3] != -1){
        return memo[i][car1][car2][car3];  // memoização dos subproblemas já calculados.
    }
    if (duracaoMusicas[i] <= car1){
        ch1 = dp(i+1, car1 - duracaoMusicas[i], car2,car3) + duracaoMusicas[i];
    }
    if (duracaoMusicas[i] <= car2){
        ch2 = dp(i+1, car1, car2 - duracaoMusicas[i],car3) + duracaoMusicas[i];
    }
    if (duracaoMusicas[i] <= car3){
        ch3 = dp(i+1, car1, car2, car3 - duracaoMusicas[i]) + duracaoMusicas[i];
    }
    ch4 = dp(i+1, car1, car2, car3);
    return memo[i][car1][car2][car3] = max(ch1, max(ch2, max(ch3, ch4)));
}

int main() {
    int K, cartuchos[] = {0, 0, 0};
    scanf("%d %d", &N, &K);  // escaneando o N (numero de musicas) e o K (numero de cartuchos)
    for (int i = 0; i < N; i++){
        scanf("%d", &duracaoMusicas[i]);  // escaneando as duracoes das musicas
    }
    for (int i = 0; i < K; i++) {
        scanf("%d", &cartuchos[i]);  // escaneando a capacidade de cada cartucho
    }

    memset(memo, -1, sizeof(memo));  // funcao para preencher toda a matriz com -1

    printf("%d\n", dp(0, cartuchos[0], cartuchos[1], cartuchos[2]));
    return 0;
}

// N, K = 8, 3
// duracaoMusicas = [7, 3, 3, 2, 4, 4, 2, 3]
// capacidadeCartuchos = [9, 8, 9]

// N, K = 10, 1
// duracaoMusicas = [31, 36, 16, 13, 10, 13, 36, 47, 1, 21]
// capacidadeCartuchos = [20]

// N, K = 10, 2
// duracaoMusicas = [41, 8, 48, 49, 33, 2, 41, 26, 5, 39]
// capacidadeCartuchos = [22, 37]