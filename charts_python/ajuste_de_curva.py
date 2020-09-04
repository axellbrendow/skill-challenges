"""
Desenvolver, em Python, aplicativo para ajuste de curvas linear e exponencial (por linearização).
Este problema deve ser resolvido pelo Método dos Mínimos Quadrados.

Cálculo Numérico, Camila Valias
"""

import math


# Leitura da entrada

print('Escolha o método a ser aplicado:')
print('1 - Linear')
print('2 - Exponencial, por linearização')
metodo = input(': ')

print()
numPontos = int(input('Informe o número de pontos: '))

x = []
y = []

for i in range(numPontos):
    coordenadas = input(f'Informe x{i + 1} y{i + 1} separados por um espaço: ').split()
    x.append(float(coordenadas[0]))
    y.append(float(coordenadas[1]))

print()
x_solicitado = float(input('Informe o valor da abscissa, x, em que a ordenada, y, deve ser estimada: '))

# Cálculo dos somatórios

if metodo == '2': # Método exponencial
    y_definitivos = []
    for ordenada in y:
        y_definitivos.append(math.log(ordenada))
else:
    y_definitivos = y

somax = 0.0
somay = 0.0
somaxy = 0.0
somax2 = 0.0
somay2 = 0.0

for i in range(numPontos):
    somax += x[i]
    somay += y_definitivos[i]
    somaxy += x[i] * y_definitivos[i]
    somax2 += x[i] * x[i]
    somay2 += y_definitivos[i] * y_definitivos[i]

# Cálculo dos coeficientes a e b

if metodo == '2': # Método exponencial
    a_linha = (numPontos * somaxy - somax * somay)\
        / (numPontos * somax2 - math.pow(somax, 2))
    
    b_linha = (somay - a_linha * somax) / numPontos
    a = a_linha
    b = math.exp(b_linha)  # mesmo que: b = e ^ b_linha
else:
    b = (numPontos * somaxy - somax * somay)\
        / (numPontos * somax2 - math.pow(somax, 2))

    a = (somay - b * somax) / numPontos

# Mostrando a equação da reta

def truncar(valor, num_casas):
    str_valor = str(valor)
    try:
        indice_do_ponto = str_valor.index('.')
    except ValueError:
        indice_do_ponto = len(str_valor) - 1

    return str_valor[0:indice_do_ponto + 1 + num_casas]


print()
if metodo == '2': # Método exponencial
    print(f'Equação do ajuste: ŷ_i = {truncar(b, 6)} e ^ ({truncar(a, 6)} * x_i)')
else:
    print(f'Equação do ajuste: ŷ_i = {truncar(a, 6)} + {truncar(b, 6)} * x_i')

# Cálculo de partes da fórmula do coeficiente de determinação

colchete1 = somaxy - (somax * somay) / numPontos
colchete2 = somax2 - math.pow(somax, 2) / numPontos
colchete3 = somay2 - math.pow(somay, 2) / numPontos

# Cálculo do coeficiente de determinação (r²)
coeficienteDeDeterminacao = math.pow(colchete1, 2) / (colchete2 * colchete3)

def obter_classificao(coeficiente_de_determinacao):
    classificacao = ''

    if coeficiente_de_determinacao < 0.3:
        classificacao = 'muito fraco ou inexistente'

    elif coeficiente_de_determinacao < 0.5:
        classificacao = 'fraco'

    elif coeficiente_de_determinacao < 0.7:
        classificacao = 'moderado'

    elif coeficiente_de_determinacao < 0.9:
        classificacao = 'forte'

    else:
        classificacao = 'muito forte ou perfeito'

    return classificacao


classificacao = obter_classificao(coeficienteDeDeterminacao)
print()
print(f'Coeficiente de determinação: {coeficienteDeDeterminacao} ({classificacao})')

print()
if metodo == '2': # Método exponencial
    print(f'O ponto estimado é ({x_solicitado}, {truncar(b * math.exp(a * x_solicitado), 6)})')
else:
    print(f'O ponto estimado é ({x_solicitado}, {truncar(a + b * x_solicitado, 6)})')

# Desenhando os gráficos
# REFERÊNCIAS:
# https://www.youtube.com/watch?v=dbYFVDhhUpk&ab_channel=MyStudy
# https://www.youtube.com/watch?v=BGg349k6BCs&ab_channel=SimplyCoding

import matplotlib.pyplot as plt

y_estimados = []

if metodo == '2': # Método exponencial
    for abscissa in x:
        y_estimados.append(b * math.exp(a * abscissa))
else:
    for abscissa in x:
        y_estimados.append(a + b * abscissa)

# plt.scatter(abscissas, ordenadas, color='orange', label='pontos originais (x_i, y_i)')
plt.plot(x, y, linestyle='dashed', marker='D', label='pontos originais (x_i, y_i)')

if metodo == '2': # Método exponencial
    label_grafico_estimado = f'ŷ_i = {truncar(b, 6)} e ^ ({truncar(a, 6)} * x_i)'
else:
    label_grafico_estimado = f'ŷ_i = {truncar(a, 6)} + {truncar(b, 6)} * x_i'

plt.plot(
    x,
    y_estimados,
    linestyle='solid',
    marker='o',
    label=label_grafico_estimado
)
plt.legend()
plt.show()
