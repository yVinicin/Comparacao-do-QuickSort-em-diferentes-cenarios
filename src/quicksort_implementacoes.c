#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

// 1) QuickSort CENTRAL
void QuickSortCentral(int *vet, int esq, int dir)
{
    while (esq < dir)
    {
        int i = esq, j = dir;
        int pivo = vet[(esq + dir) / 2];

        while (i <= j)
        {
            while (vet[i] < pivo && i < dir) i++;
            while (vet[j] > pivo && j > esq) j--;

            if (i <= j)
            {
                trocar(&vet[i], &vet[j]);
                i++;
                j--;
            }
        }

        if ((j - esq) < (dir - i))
        {
            if (j > esq) QuickSortCentral(vet, esq, j);
            esq = i;
        }
        else
        {
            if (i < dir) QuickSortCentral(vet, i, dir);
            dir = j;
        }
    }
}

// 2) QuickSort RANDÔMICO
void QuickSortRandomico(int *vet, int esq, int dir)
{
    while (esq < dir)
    {
        int i = esq, j = dir;
        
        int indice_pivo = esq + rand() % (dir - esq + 1);
        int pivo = vet[indice_pivo];

        while (i <= j)
        {
            while (vet[i] < pivo && i < dir) i++;
            while (vet[j] > pivo && j > esq) j--;

            if (i <= j)
            {
                trocar(&vet[i], &vet[j]);
                i++;
                j--;
            }
        }

        if ((j - esq) < (dir - i))
        {
            if (j > esq) QuickSortRandomico(vet, esq, j);
            esq = i;
        }
        else
        {
            if (i < dir) QuickSortRandomico(vet, i, dir);
            dir = j;
        }
    }
}

// 3) QuickSort MEDIANA DE 3 (Três Sorteados)
void QuickSortMediana3(int *vet, int esq, int dir)
{
    while (esq < dir)
    {
        int i = esq, j = dir;

        // Sorteia três posições aleatórias no intervalo atual
        int idx1 = esq + rand() % (dir - esq + 1);
        int idx2 = esq + rand() % (dir - esq + 1);
        int idx3 = esq + rand() % (dir - esq + 1);

        int v1 = vet[idx1], v2 = vet[idx2], v3 = vet[idx3];
        int pivo;

        // Identifica a mediana dos três valores sorteados
        if ((v1 >= v2 && v1 <= v3) || (v1 <= v2 && v1 >= v3)) pivo = v1;
        else if ((v2 >= v1 && v2 <= v3) || (v2 <= v1 && v2 >= v3)) pivo = v2;
        else pivo = v3;

        while (i <= j)
        {
            while (vet[i] < pivo && i < dir) i++;
            while (vet[j] > pivo && j > esq) j--;

            if (i <= j)
            {
                trocar(&vet[i], &vet[j]);
                i++;
                j--;
            }
        }

        if ((j - esq) < (dir - i))
        {
            if (j > esq) QuickSortMediana3(vet, esq, j);
            esq = i;
        }
        else
        {
            if (i < dir) QuickSortMediana3(vet, i, dir);
            dir = j;
        }
    }
}

// 4) QuickSort ÚLTIMO
void QuickSortUltimo(int *vet, int esq, int dir)
{
    while (esq < dir)
    {
        int i = esq, j = dir;
        int pivo = vet[dir];

        while (i <= j)
        {
            while (vet[i] < pivo && i < dir) i++;
            while (vet[j] > pivo && j > esq) j--;

            if (i <= j)
            {
                trocar(&vet[i], &vet[j]);
                i++;
                j--;
            }
        }

        if ((j - esq) < (dir - i))
        {
            if (j > esq) QuickSortUltimo(vet, esq, j);
            esq = i;
        }
        else
        {
            if (i < dir) QuickSortUltimo(vet, i, dir);
            dir = j;
        }
    }
}
