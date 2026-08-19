import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_theme(style="whitegrid")

df = pd.read_csv('resultados.csv')

vetor_types = df['Tipo_Vetor'].unique()

for vetor_type in vetor_types:
    plt.figure(figsize=(10, 6))
    subset = df[df['Tipo_Vetor'] == vetor_type]
    
    sns.lineplot(
        data=subset, 
        x='Tamanho_Vetor', 
        y='Tempo_Medio_ms', 
        hue='Algoritmo', 
        marker='o'
    )
    
    plt.title(f'Desempenho do QuickSort - Vetores {vetor_type}')
    plt.xlabel('Tamanho do Vetor')
    plt.ylabel('Tempo Médio (ms)')
    plt.legend(title='Estratégia de Pivô')
    plt.tight_layout()
    
    clean_name = str(vetor_type).lower().replace(' ', '_')
    filename = f'plot_{clean_name}.png'
    
    plt.savefig(filename, dpi=300)
    plt.close()
    print(f'Gráfico salvo: {filename}')

plt.figure(figsize=(12, 8))
sns.lineplot(
    data=df, 
    x='Tamanho_Vetor', 
    y='Tempo_Medio_ms', 
    hue='Algoritmo', 
    style='Tipo_Vetor', 
    markers=True
)
plt.yscale('log')
plt.title('Comparação Geral do QuickSort (Escala Logarítmica)')
plt.xlabel('Tamanho do Vetor')
plt.ylabel('Tempo Médio (ms) - Log')
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()

plt.savefig('plot_comparativo_geral.png', dpi=300)
plt.close()
print('Gráfico comparativo geral salvo: plot_comparativo_geral.png')