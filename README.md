# ⚡ Comparação do QuickSort em Diferentes Cenários

> 1° Trabalho de Projeto e Análise de Algoritmos (PAA) — Análise comparativa entre diferentes variações do algoritmo **QuickSort** aplicadas a diferentes tipos e tamanhos de entrada.

![Badge Language](https://img.shields.io/badge/Language-Python-3776AB?logo=python&logoColor=white)
![Badge Topic](https://img.shields.io/badge/Topic-Algoritmos%20de%20Ordenação-orange)
![Badge Academic](https://img.shields.io/badge/Type-Academic%20Project-blue)

## 📖 Sobre o Projeto

Este projeto foi desenvolvido como o **1º Trabalho da disciplina de Projeto e Análise de Algoritmos (PAA)**, com o objetivo de implementar e comparar experimentalmente diferentes variações do algoritmo de ordenação **QuickSort**, avaliando seu desempenho em distintos cenários de entrada (por exemplo: dados aleatórios, já ordenados, ordenados de forma inversa e com muitos elementos repetidos).

A análise busca evidenciar, na prática, como a escolha da estratégia de particionamento/pivô impacta diretamente o desempenho do algoritmo, aproximando ou afastando sua execução do melhor caso O(N log N) e do pior caso O(N²).

Os resultados completos da análise, gráficos e discussão estão documentados em [`QuickSort - Relatório.pdf`](<./QuickSort - Relatório.pdf>). O enunciado original do trabalho está em [`1º_Trabalho_de_PAA_2026.pdf`](<./1º_Trabalho_de_PAA_2026%201.pdf>).

## 📂 Estrutura do Projeto

```bash
Comparacao-do-QuickSort-em-diferentes-cenarios/
├── src/                                 # Implementações das variações do QuickSort e scripts de benchmark
├── outputs/                             # Resultados dos testes (dados brutos, gráficos, tabelas)
├── 1º_Trabalho_de_PAA_2026 1.pdf        # Enunciado do trabalho
├── QuickSort - Relatório.pdf            # Relatório com a análise comparativa e conclusões
└── README.md                            # Esta documentação
```

## 🧪 Cenários Avaliados

Os testes comparam o comportamento do QuickSort (e suas variações de escolha de pivô/particionamento) frente a diferentes perfis de entrada, como:

* **Dados aleatórios** — caso médio esperado;
* **Dados em ordem decrescente** — outro cenário propenso ao pior caso;
* **Dados já ordenados** — cenário que tende ao pior caso em implementações ingênuas;
* **Dados parcialmente ordenados** — avalia o impacto de partições desbalanceadas.

Os tempos de execução e/ou número de comparações/trocas são coletados e salvos em `outputs/`, servindo de base para os gráficos e conclusões do relatório.

## 🚀 Como Executar

**Pré-requisito:** Python 3 instalado.

1.  **Clone o repositório:**
```bash
    git clone https://github.com/yVinicin/Comparacao-do-QuickSort-em-diferentes-cenarios.git
    cd Comparacao-do-QuickSort-em-diferentes-cenarios
```

2.  **Execute os testes/benchmarks:**
```bash
    python3 src/main.py
```

3.  **Confira os resultados** gerados na pasta `outputs/`.

## 📈 Complexidade do QuickSort

| Cenário | Complexidade |
|---|---|
| Melhor caso | $O(N \log N)$ |
| Caso médio | $O(N \log N)$ |
| Pior caso | $O(N^2)$ |

A estratégia de escolha do pivô é o principal fator que determina em qual desses cenários a execução real vai se aproximar — é justamente essa relação que este trabalho investiga.
