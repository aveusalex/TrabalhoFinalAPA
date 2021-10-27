#include <stdio.h>
#include <string.h>

#define MAX 105


// função para remover as músicas que já foram inseridas no cartucho que acabou de rodar.
void removeMusicas(int (*musComponentes)[50], int (*duracaoMusicas)[MAX], int N, int (*NcadaCartucho)[3], int cart){
    int abandonaLaco = 0;  // Essa variável é para saber qual valor

    // estipular a quantidade de musicas que pertencem a musComponentes.
    int qtdColocadas = 0;
    for (int cont = 0; cont < MAX; cont++){
        if ((*musComponentes)[cont] != -1){
            qtdColocadas += 1;
        }
        else break;
    }

    // colocar no array NcadaCartucho o N de cada cartucho (numero de musicas disponiveis).
    (*NcadaCartucho)[cart + 1] = (*NcadaCartucho)[cart] - qtdColocadas;

    // conjunto de laços que removem as musicas já postas no cartucho.
    for (int cont1 = 0;  cont1 < qtdColocadas; cont1++){
        for (int cont2 = 1; cont2 <= (*NcadaCartucho)[cart]; cont2++){
            if ((*duracaoMusicas)[(*musComponentes)[cont1]] == (*duracaoMusicas)[cont2]){
                for (int cont3 = cont2; cont3 <= (*NcadaCartucho)[cart] - cont1 - 1; cont3++){
                    (*duracaoMusicas)[cont3] = (*duracaoMusicas)[cont3 + 1];
                    abandonaLaco = cont3 + 1;
                }

                // o -1 demarca o fim do array.
                (*duracaoMusicas)[abandonaLaco] = -1;
                break;
            }
        }
    }
}

// função para verificar quais musicas compõem o cartucho.
void verificaCartucho(int tabela_PD[3][MAX][55], int (*musicasComponentes)[50], int sizeCartucho, int (* NcadaCartucho)[3], int cartucho, int (* duracaoMus)[MAX]){
    int aux, counter = 0, negativo = -1;

    for (int i = (*NcadaCartucho)[cartucho]; i > 0; i--){
        aux = tabela_PD[cartucho][i - 1][sizeCartucho];
        // se houve alteração no valor ótimo da mochila, devemos mapear se o valor foi herdado ou somado com o item atual.
        if (tabela_PD[cartucho][i][sizeCartucho] != aux){
            (*musicasComponentes)[counter] = i;
            sizeCartucho = sizeCartucho - (*duracaoMus)[i];
            counter += 1;
        }
    }
    (*musicasComponentes)[counter] = negativo;
}

int main() {
    int K = 0, N = 0;  // declarando variável quantidade de cartuchos e músicas.
    int sizeCartuchos[] = {0, 0, 0};  // inicializando a lista referente à capacidade dos cartuchos.
    int j = 0, resultado = 0;  // declarando o índice j (coluna) da tabela.

    // arrays
    int musicasComponentes[50];
    int tabela_PD[3][MAX][55], duracaoMusicas[MAX];  // Cria uma tabela genérica de tamanho máximo baseado no valor máximo das entradas.
    int NcadaCartucho[] = {0, 0, 0};  // Cada cartucho terá um numero de musicas diferente para levar em consideracao na tabela.

    // ponteiros para arrays
    int (*ptr_duracaoMusicas)[MAX] = &duracaoMusicas;
    int (*ptr_musicasComponentes)[50] = &musicasComponentes;
    int (*ptr_NcadaCartucho)[3] = &NcadaCartucho;

    scanf("%d %d", &N, &K);  // escaneando o N (numero de musicas) e o K (numero de cartuchos)
    for (int c1 = 1; c1 <= N; c1++){
        scanf("%d", &duracaoMusicas[c1]);  // escaneando as duracoes das musicas
    }
    for (int c2 = 0; c2 < K; c2++) {
        scanf("%d", &sizeCartuchos[c2]);  // escaneando a capacidade de cada cartucho
    }

    // já colocar a quantidade de musicas disponiveis para o primeiro cartucho
    NcadaCartucho[0] = N;

    memset(tabela_PD, 0, sizeof(tabela_PD));  // preenchendo com zeros a tabela.

    // início da programação dinâmica.
    for (int cartucho = 0; cartucho < K; cartucho++) {
        // percorremos a tabela de forma top-down, ou seja, de cima para baixo por coluna.
        j = 0;
        while (j != sizeCartuchos[cartucho] + 1) {
            for (int i = 1; i <= NcadaCartucho[cartucho]; i++) {
                // caso a duracao da música esteja marcada como -1, deve pular para a próxima coluna.
                if (duracaoMusicas[i] == -1){
                    break;
                }

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
        verificaCartucho(tabela_PD, ptr_musicasComponentes, sizeCartuchos[cartucho], ptr_NcadaCartucho, cartucho, ptr_duracaoMusicas);
        removeMusicas(ptr_musicasComponentes, ptr_duracaoMusicas, N, ptr_NcadaCartucho, cartucho);

    }

    // Iterar pelo tamanho dos cartuchos e recuperar a informacão correspondente na tabela (elemento N(maior valor da
    // linha) e sizeCartuchos(maior valor da coluna para cada cartucho).
    for (int cart = 0; cart<K; cart++) {
        resultado += tabela_PD[cart][(NcadaCartucho)[cart]][sizeCartuchos[cart]];
    }

    printf("%d\n", resultado);
    return 0;
}
