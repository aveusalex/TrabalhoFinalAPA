#include <stdio.h>
#include <string.h>
#define MAX 105

// Função máximo auxiliar. Determina o maior valor em um par de inteiros.
int maximo(int num1, int num2){
    if (num1 < num2){
        return num2;
    }
    else{
        return num1;
    }
}

// função para remover as músicas que já foram inseridas no cartucho que acabou de rodar.
int removeMusicas(int *musComponentes[], int duracaoMusicas[], int N, int qtdColocadas){
    for (int cont1 =0;  cont1 <= qtdColocadas; cont1++){
        for (int cont2 = 0; cont2 <= N; cont2++){
            if (jaColocadas[cont1] == duracaoMusicas[cont2]){
                for (int cont3 = cont1; cont3 <= N-1; cont3++){
                    duracaoMusicas[cont3] = duracaoMusicas[cont3+1];
                }
            }
        }

    }
}

// função para verificar quais musicas compõem o cartucho.
int verificaCartucho(int tabela_PD[3][MAX][55], int sizeCartucho, int N, int cartucho){
    int aux, counter = 0;
    int musicasComponentes[50];

    for (int i = N; i > 0; i--){
        aux = tabela_PD[cartucho][i - 1][sizeCartucho];
        // se houve alteração no valor ótimo da mochila, devemos mapear se o valor foi herdado ou somado com o item atual.
        if (tabela_PD[cartucho][i][sizeCartucho] != aux){
            musicasComponentes[counter] = i;
            sizeCartucho = tabela_PD[cartucho][i][sizeCartucho];
            counter += 1;
        }

    }
    musicasComponentes[counter] = -1;
    return *musicasComponentes;
}

int main() {
    int K = 0, N = 0, duracaoMusicas[MAX];  // declarando variável quantidade de cartuchos e músicas e lista de durações.
    int tabela_PD[3][MAX][55];  // Cria uma tabela genérica de tamanho máximo baseado no valor máximo das entradas.
    int sizeCartuchos[] = {0, 0, 0};  // inicializando a lista referente à capacidade dos cartuchos.
    int j = 0;  // declarando o índice j (coluna) da tabela.
    int resultado = 0, *musicasComponentes;
    int qtdColocadas;

    scanf("%d %d", &N, &K);  // escaneando o N (numero de musicas) e o K (numero de cartuchos)
    for (int c1 = 1; c1 <= N; c1++){
        scanf("%d", &duracaoMusicas[c1]);  // escaneando as duracoes das musicas
    }
    for (int c2 = 0; c2 < K; c2++) {
        scanf("%d", &sizeCartuchos[c2]);  // escaneando a capacidade de cada cartucho
    }

    memset(tabela_PD, 0, sizeof(tabela_PD));  // preenchendo com zeros a tabela.

    // início da programação dinâmica.
    for (int cartucho = 0; cartucho < K; cartucho++) {
        // percorremos a tabela de forma top-down, ou seja, de cima para baixo por coluna.
        while (j != sizeCartuchos[cartucho] + 1) {
            for (int i = 1; i <= N; i++) {
                // Se a música de duração "duracaoMusicas[i]" couber no cartucho de tamanho "j"...
                if (duracaoMusicas[i] <= j) {
                    // Se a soma da duração da música atual com a música do cartucho "j - duração atual" for maior que
                    // o elemento da linha superior do mesmo cartucho...
                    if (tabela_PD[cartucho][i - 1][j - duracaoMusicas[i]] + duracaoMusicas[i] > tabela_PD[cartucho][i - 1][j]) {
                        // Então o elemento "tabela_PD[i][j]" recebe a soma mencionada.
                        tabela_PD[cartucho][i][j] = tabela_PD[cartucho][i - 1][j - duracaoMusicas[i]] + duracaoMusicas[i];

                        // senão, o elemento "tabela_PD[i][j]" recebe o valor anterior do mesmo cartucho.
                    } else tabela_PD[cartucho][i][j] = tabela_PD[cartucho][i - 1][j];

                    // senão, o elemento "tabela_PD[i][j]" recebe o valor anterior do mesmo cartucho.
                } else tabela_PD[cartucho][i][j] = tabela_PD[cartucho][i - 1][j];
            }
            j += 1;
        }
        // chamada de função para remover as músicas que já foram inseridas no cartucho que acabou de rodar.
        *musicasComponentes = verificaCartucho(tabela_PD, sizeCartuchos[cartucho], N, cartucho);

    }

    // auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar
    printf("\n\n\n");
    printf("\t\t  ");
    for (int c = 0; c < maximo(sizeCartuchos[0], maximo(sizeCartuchos[1], sizeCartuchos[2])) + 1; c++) {
        printf("%d \t", c);
    }
    printf("\n\n");
    for (int c2 = 0; c2 <= N; c2++){
        printf("%2d: \t\t", c2);
        for (int c = 0; c < maximo(sizeCartuchos[0], maximo(sizeCartuchos[1], sizeCartuchos[2])) + 1; c++){
            printf("%d \t", tabela_PD[c2][c]);
        }
        printf("\n");
    }
    printf("\n");
    // auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar auxiliar

    // Iterar pelo tamanho dos cartuchos e recuperar a informacão correspondente na tabela (elemento N(maior valor da
    // linha) e sizeCartuchos(maior valor da coluna para cada cartucho).
    for (int c3 = 0; c3 < K; c3++){
        resultado += tabela_PD[N][sizeCartuchos[c3]];
    }

    printf("%d\n", resultado);
    return 0;
}
