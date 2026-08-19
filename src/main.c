#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

// Inclui as implementações do QuickSort
#include <ctype.h>
#include "quicksort_implementacoes.c"

// ============================================================
// Lê um vetor de números inteiros a partir de um arquivo
// ============================================================
int* ler_vetor_do_arquivo(const char* nome_arquivo, int* tamanho) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        *tamanho = 0;
        return NULL;
    }

    int capacidade = 1000;
    int* vet = (int*)malloc(sizeof(int) * capacidade);
    if (vet == NULL) {
        perror("Erro de alocação de memória");
        *tamanho = 0;
        fclose(arquivo);
        return NULL;
    }

    *tamanho = 0;
    int numero;
    while (fscanf(arquivo, "%d", &numero) == 1) {
        // Se o vetor ficou cheio, dobra a capacidade
        if (*tamanho == capacidade) {
            capacidade *= 2;
            int* novo_vet = (int*)realloc(vet, sizeof(int) * capacidade);
            if (novo_vet == NULL) {
                perror("Erro de realocação de memória");
                free(vet);
                *tamanho = 0;
                fclose(arquivo);
                return NULL;
            }
            vet = novo_vet;
        }
        vet[*tamanho] = numero;
        (*tamanho)++;
    }

    fclose(arquivo);
    return vet;
}

// ============================================================
// Copia um vetor (para não estragar o vetor original nos testes)
// ============================================================
int* copiar_vetor(const int* origem, int tamanho) {
    int* destino = (int*)malloc(sizeof(int) * tamanho);
    if (destino == NULL) {
        perror("Erro de alocação de memória para cópia");
        return NULL;
    }
    memcpy(destino, origem, sizeof(int) * tamanho);
    return destino;
}

// ============================================================
// Mede o tempo de execução da ordenação em milissegundos
// ============================================================
double medir_tempo(void (*funcao_ordenar)(int*, int, int), int* vet, int tamanho) {
    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);
    funcao_ordenar(vet, 0, tamanho - 1);
    gettimeofday(&fim, NULL);
    return (double)(fim.tv_sec - inicio.tv_sec) * 1000.0 + (double)(fim.tv_usec - inicio.tv_usec) / 1000.0;
}

int main() {
    // Inicializa o gerador de números aleatórios uma única vez
    srand(time(NULL));

    const char* caminho_base = "";

    const char* tipos[] = {"Aleatórios", 
        "Ordenados", 
        "Decrescentes", 
        "ParcialmenteOrdenados"
        };

    const char* tamanhos[] = {"100", "200", "500", "1000", "2000", "5000", "7500",
                              "10000", "15000", "30000", "50000", "75000", "100000",
                              "200000", "500000", "750000", "1000000", "1250000", "1500000", "2000000"};

    // As estratégias de pivô
    void (*funcoes_ordenacao[])(int*, int, int) = {
        QuickSortCentral,
        QuickSortRandomico,
        QuickSortMediana3,
        QuickSortUltimo
    };
    const char* nomes_algoritmos[] = {
        "QuickSortCentral",
        "QuickSortRandomico",
        "QuickSortMediana3",
        "QuickSortUltimo"
    };
    int quantidade_algoritmos = sizeof(funcoes_ordenacao) / sizeof(funcoes_ordenacao[0]);

    FILE* arquivo_resultados = fopen("resultados.csv", "w");
    if (arquivo_resultados == NULL) {
        perror("Erro ao criar o arquivo de resultados");
        return 1;
    }
    fprintf(arquivo_resultados, "Tipo_Vetor,Tamanho_Vetor,Algoritmo,Tempo_Medio_ms\n");

    // Percorre cada tipo de vetor
    for (size_t t = 0; t < sizeof(tipos) / sizeof(tipos[0]); t++) {
        // Percorre cada tamanho
        for (size_t s = 0; s < sizeof(tamanhos) / sizeof(tamanhos[0]); s++) {
            char nome_arquivo[256];
            // Monta o nome do arquivo: a100.txt, o100.txt, d100.txt ou po100.txt
            char prefixo = tolower(tipos[t][0]);
            if (strcmp(tipos[t], "ParcialmenteOrdenados") == 0) {
                sprintf(nome_arquivo, "%s%s/po%s.txt", caminho_base, tipos[t], tamanhos[s]);
            } else {
                sprintf(nome_arquivo, "%s%s/%c%s.txt", caminho_base, tipos[t], prefixo, tamanhos[s]);
            }

            // Lê o vetor original do arquivo
            int tamanho_original;
            int* vetor_original = ler_vetor_do_arquivo(nome_arquivo, &tamanho_original);

            if (vetor_original == NULL || tamanho_original == 0) {
                fprintf(stderr, "Aviso: Não foi possível ler o arquivo %s ou ele está vazio. Pulando.\n", nome_arquivo);
                continue;
            }

            printf("Testando %s com vetor %s (tamanho %d)...\n", tipos[t], tamanhos[s], tamanho_original);

            // Testa cada algoritmo de ordenação
            for (int f = 0; f < quantidade_algoritmos; f++) {
                double tempo_total = 0;

                // Executa 6 vezes: descarta a 1ª e faz a média das outras 5
                for (int execucao = 0; execucao < 6; execucao++) {
                    int* vetor_atual = copiar_vetor(vetor_original, tamanho_original);
                    if (vetor_atual == NULL) {
                        free(vetor_original);
                        fclose(arquivo_resultados);
                        return 1;
                    }

                    double tempo = medir_tempo(funcoes_ordenacao[f], vetor_atual, tamanho_original);
                    free(vetor_atual);

                    // Descarta a primeira execução
                    if (execucao > 0) {
                        tempo_total += tempo;
                    }
                }

                double tempo_medio = tempo_total / 5.0;
                printf("  %s: %.4f ms\n", nomes_algoritmos[f], tempo_medio);
                fprintf(arquivo_resultados, "%s,%s,%s,%.4f\n", tipos[t], tamanhos[s], nomes_algoritmos[f], tempo_medio);
            }

            free(vetor_original);
        }
    }

    fclose(arquivo_resultados);
    printf("Testes concluídos. Resultados salvos em resultados.csv\n");
    return 0;
}
