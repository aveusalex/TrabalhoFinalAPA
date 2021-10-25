# Problema:
"""
Entrada:
A primeira linha da entrada consiste de dois inteiros positivos N e K (N ≤ 100, K ≤ 3), os quais representam
respectivamente o número de canções no computador de Fernando e o número de cartuchos que ele tem. A segunda
linha da entrada consiste de N inteiros positivos, os quais representam as durações em minutos de cada música.
A última linha da entrada consiste de K inteiros positivos, os quais representam o número máximo de minutos de
música que é possível gravar em cada cartucho. Nenhuma música possui mais de 50 minutos, e em nenhum cartucho
cabe mais de 50 minutos de música.

Saída:
Imprima uma linha contendo unicamente o número máximo total de minutos de música que é possível gravar nos cartuchos.
"""

# Solução:
""" 
Veja que é relativamente fácil resolver o problema da mochila por força bruta: basta enumerar todos os subconjuntos 
possíveis de itens, verificar se eles cabem na mochila, calcular o valor total e guardar o melhor possível de todos. 
No entanto, existem 2**n subconjuntos diferentes de itens pois, para cada item, temos a opção de colocá-lo ou não no 
subconjunto. Para cada subconjunto, levamos tempo O(n) para checar se os itens cabem na mochila e calcular seu valor 
total. Ou seja, esse algoritmo leva tempo O(n2n) e, portanto, não é eficiente.
"""


def textToNumber(list):
    aux = []
    for element in list:
        aux.append(int(element))
    return aux


def recursao(indice_musica, capacidade_cartucho1, capacidade_cartucho2, capacidade_cartucho3):
    escolha1, escolha2, escolha3, escolha4 = 0, 0, 0, 0

    if indice_musica == N:  # se o indice da musica for igual a quantidade de musicas, nao tem mais o que fazer
        return 0
    if duracaoMusicas[indice_musica] <= capacidade_cartucho1:
        escolha1 = recursao(indice_musica + 1, capacidade_cartucho1 - duracaoMusicas[indice_musica],
                            capacidade_cartucho2, capacidade_cartucho3) + duracaoMusicas[indice_musica]

    if duracaoMusicas[indice_musica] <= capacidade_cartucho2:
        escolha2 = recursao(indice_musica + 1, capacidade_cartucho1, capacidade_cartucho2 - duracaoMusicas[indice_musica],
                            capacidade_cartucho3) + duracaoMusicas[indice_musica]

    if duracaoMusicas[indice_musica] <= capacidade_cartucho3:
        escolha3 = recursao(indice_musica + 1, capacidade_cartucho1, capacidade_cartucho2,
                            capacidade_cartucho3 - duracaoMusicas[indice_musica]) + duracaoMusicas[indice_musica]

    escolha4 = recursao(indice_musica + 1, capacidade_cartucho1, capacidade_cartucho2, capacidade_cartucho3)
    return max([escolha1, escolha2, escolha3, escolha4])


# fb = força bruta
def chamada_fb(N, K, list_dur_musicas, list_capacidade_individual):
    cartuchos = [0, 0, 0]
    for i in range(int(K)):  # Colocar na lista a capacidade de tres cartuchos, se o cartucho nao existir recebe 0
        cartuchos[i] = list_capacidade_individual[i]

    print(recursao(0, cartuchos[0], cartuchos[1], cartuchos[2]))


def pd(indice_musica, capacidade_cartucho1, capacidade_cartucho2, capacidade_cartucho3):
    escolha1, escolha2, escolha3, escolha4 = 0, 0, 0, 0

    if indice_musica == N:  # se o indice da musica for igual a quantidade de musicas, nao tem mais o que fazer
        return 0

    global memo
    if memo[indice_musica][capacidade_cartucho1][capacidade_cartucho2][capacidade_cartucho3] != -1:
        return memo[indice_musica][capacidade_cartucho1][capacidade_cartucho2][capacidade_cartucho3]

    if duracaoMusicas[indice_musica] <= capacidade_cartucho1:
        escolha1 = pd(indice_musica + 1, capacidade_cartucho1 - duracaoMusicas[indice_musica],
                      capacidade_cartucho2, capacidade_cartucho3) + duracaoMusicas[indice_musica]

    if duracaoMusicas[indice_musica] <= capacidade_cartucho2:
        escolha2 = pd(indice_musica + 1, capacidade_cartucho1, capacidade_cartucho2 - duracaoMusicas[indice_musica],
                      capacidade_cartucho3) + duracaoMusicas[indice_musica]

    if duracaoMusicas[indice_musica] <= capacidade_cartucho3:
        escolha3 = pd(indice_musica + 1, capacidade_cartucho1, capacidade_cartucho2,
                      capacidade_cartucho3 - duracaoMusicas[indice_musica]) + duracaoMusicas[indice_musica]

    escolha4 = pd(indice_musica + 1, capacidade_cartucho1, capacidade_cartucho2, capacidade_cartucho3)

    memo[indice_musica][capacidade_cartucho1][capacidade_cartucho2][capacidade_cartucho3] = max([escolha1, escolha2, escolha3, escolha4])
    return memo[indice_musica][capacidade_cartucho1][capacidade_cartucho2][capacidade_cartucho3]


def chamada_pd(N, K, list_dur_musicas, list_capacidade_individual):
    import numpy as np

    max = 112  # numero maximo de musicas no pc do rapaz (na vdd eh 100, mas nao eh bom deixar justo)
    global memo
    memo = np.full([max, 60, 60, 60], -1)
    cartuchos = [0, 0, 0]

    for i in range(int(K)):  # Colocar na lista a capacidade de tres cartuchos, se o cartucho nao existir recebe 0
        cartuchos[i] = list_capacidade_individual[i]

    print(pd(0, cartuchos[0], cartuchos[1], cartuchos[2]))


if __name__ == '__main__':
    # N, K = textToNumber(input().split())  # N = numero de cancoes, K = numero de cartuchos
    # duracaoMusicas = textToNumber(input().split())
    # capacidadeCartuchos = textToNumber(input().split())

    # N, K = 8, 3
    # duracaoMusicas = [7, 3, 3, 2, 4, 4, 2, 3]
    # capacidadeCartuchos = [9, 8, 9]

    # N, K = 10, 1
    # duracaoMusicas = [31, 36, 16, 13, 10, 13, 36, 47, 1, 21]
    # capacidadeCartuchos = [20]

    # N, K = 10, 2
    # duracaoMusicas = [41, 8, 48, 49, 33, 2, 41, 26, 5, 39]
    # capacidadeCartuchos = [22, 37]

    N, K = 87, 2
    duracaoMusicas = textToNumber("28 16 44 36 37 43 50 22 13 28 41 10 14 27 41 27 23 37 12 19 18 30 33 31 13 24 18 36 30 3 23 9 20 18 44 7 12 43 30 24 22 20 35 38 49 25 16 21 14 27 42 31 7 24 13 21 47 32 6 26 35 28 37 6 47 30 14 8 25 46 33 46 15 18 35 15 44 1 38 9 27 29 39 35 4 2 5".split())
    capacidadeCartuchos = [50, 33]

    #chamada_fb(N, K, duracaoMusicas, capacidadeCartuchos)
    chamada_pd(N, K, duracaoMusicas, capacidadeCartuchos)
