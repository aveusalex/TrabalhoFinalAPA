#include <stdio.h>
#include <string.h>
#define MAX 100

// Função máximo auxiliar. Determina o maior valor em um par de inteiros.
int maximo(int num1, int num2){
    if (num1 < num2){
        return num2;
    }
    else{
        return num1;
    }
}

int main() {
    int K = 0, N = 0, duracaoMusicas[MAX];  // declarando variável quantidade de cartuchos e músicas e lista de durações.
    int tabela_PD[MAX][50];  // Cria uma tabela genérica de tamanho máximo baseado no valor máximo das entradas.
    int sizeCartuchos[] = {0, 0, 0};  // inicializando a lista referente à capacidade dos cartuchos.
    int j = 0;  // declarando os índices da tabela, i: linha, j: tabela.
    int resultado = 0;

    scanf("%d %d", &N, &K);  // escaneando o N (numero de musicas) e o K (numero de cartuchos)
    for (int c1 = 1; c1 <= N; c1++){
        scanf("%d", &duracaoMusicas[c1]);  // escaneando as duracoes das musicas
    }
    for (int c2 = 0; c2 < K; c2++) {
        scanf("%d", &sizeCartuchos[c2]);  // escaneando a capacidade de cada cartucho
    }

    memset(tabela_PD, 0, sizeof(tabela_PD));  // preenchendo com zeros a tabela.

    // início da programação dinâmica.
    while (j != maximo(sizeCartuchos[0], maximo(sizeCartuchos[1], sizeCartuchos[2])) + 1){
        for (int i = 1; i <= N; i++) {
            // Se a música de duração "duracaoMusicas[i]" couber no cartucho de tamanho "j"...
            if (duracaoMusicas[i] <= j) {
                // Se a soma da duração da música atual com a música do cartucho "j - duração atual" for maior que
                // o elemento da linha superior do mesmo cartucho...
                if (tabela_PD[i - 1][j - duracaoMusicas[i]] + duracaoMusicas[i] > tabela_PD[i - 1][j]) {
                    // Então o elemento "tabela_PD[i][j]" recebe a soma mencionada.
                    tabela_PD[i][j] = tabela_PD[i - 1][j - duracaoMusicas[i]] + duracaoMusicas[i];

                // senão, o elemento "tabela_PD[i][j]" recebe o valor anterior do mesmo cartucho.
                } else tabela_PD[i][j] = tabela_PD[i - 1][j];

            // senão, o elemento "tabela_PD[i][j]" recebe o valor anterior do mesmo cartucho.
            } else tabela_PD[i][j] = tabela_PD[i - 1][j];
        }
        j += 1;
    }

    // auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar
    printf("\n\n\n");
    for (int c = 0; c < maximo(sizeCartuchos[0], maximo(sizeCartuchos[1], sizeCartuchos[2])) + 1; c++){
        for (int c2 = 0; c2 < N; c2++){
            printf("%d  ", tabela_PD[c2][c]);
        }
        printf("\n");
    }
    // auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar

    // Iterar pelo tamanho dos cartuchos e recuperar a informacão correspondente na tabela (elemento N(maior valor da
    // linha) e sizeCartuchos(maior valor da coluna para cada cartucho).
    for (int c3 = 0; c3 < K; c3++){
        resultado += tabela_PD[N][sizeCartuchos[c3]];
    }

    printf("%d\n", resultado);
    return 0;
}
