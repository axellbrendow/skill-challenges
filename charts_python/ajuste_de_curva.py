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

abscissas = []
ordenadas = []

for i in range(numPontos):
    coordenadas = input(f'Informe x{i + 1} y{i + 1} separados por um espaço: ').split()
    abscissas.append(float(coordenadas[0]))
    ordenadas.append(float(coordenadas[1]))

print()
x = float(input('Informe o valor da abscissa, x, em que a ordenada, y, deve ser estimada: '))

# Funções auxiliares para somatórios

def somar_lista(lista):
    soma = 0.0

    for valor in lista:
        soma += valor

    return soma


def somar_produto_de(lista1, lista2):
    soma = 0.0

    for i in range(len(lista1)):
        soma += lista1[i] * lista2[i]

    return soma


def somar_o_quadrado_de(lista):
    soma = 0.0

    for valor in lista:
        soma += valor * valor

    return soma


def obter_o_logaritmo_natural_de_cada_elemento(lista):
    nova_lista = []

    for valor in lista:
        nova_lista.append(math.log(valor))

    return nova_lista

# Cálculo dos somatórios

if metodo == '2': # Método exponencial
    ordenadas_definitivas = obter_o_logaritmo_natural_de_cada_elemento(ordenadas)
else:
    ordenadas_definitivas = ordenadas

somatorioDasAbscissas = somar_lista(abscissas)
somatorioDasOrdenadas = somar_lista(ordenadas_definitivas)
somatorioDoProduto = somar_produto_de(abscissas, ordenadas_definitivas)
somatorioDoQuadradoDasAbscissas = somar_o_quadrado_de(abscissas)
somatorioDoQuadradoDasOrdenadas = somar_o_quadrado_de(ordenadas_definitivas)

# Cálculo dos coeficientes a e b

if metodo == '2': # Método exponencial
    a_linha = (numPontos * somatorioDoProduto - somatorioDasAbscissas * somatorioDasOrdenadas)\
        / (numPontos * somatorioDoQuadradoDasAbscissas - math.pow(somatorioDasAbscissas, 2))
    
    b_linha = (somatorioDasOrdenadas - a_linha * somatorioDasAbscissas) / numPontos
    a = a_linha
    b = math.exp(b_linha)  # mesmo que: b = e ^ b_linha
else:
    b = (numPontos * somatorioDoProduto - somatorioDasAbscissas * somatorioDasOrdenadas)\
        / (numPontos * somatorioDoQuadradoDasAbscissas - math.pow(somatorioDasAbscissas, 2))

    a = (somatorioDasOrdenadas - b * somatorioDasAbscissas) / numPontos

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

colchete1 = somatorioDoProduto - (somatorioDasAbscissas * somatorioDasOrdenadas) / numPontos
colchete2 = somatorioDoQuadradoDasAbscissas - math.pow(somatorioDasAbscissas, 2) / numPontos
colchete3 = somatorioDoQuadradoDasOrdenadas - math.pow(somatorioDasOrdenadas, 2) / numPontos

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
    print(f'O ponto estimado é ({x}, {truncar(b * math.exp(a * x), 6)})')
else:
    print(f'O ponto estimado é ({x}, {truncar(a + b * x, 6)})')

# Desenhando os gráficos
# REFERÊNCIAS:
# https://www.youtube.com/watch?v=dbYFVDhhUpk&ab_channel=MyStudy
# https://www.youtube.com/watch?v=BGg349k6BCs&ab_channel=SimplyCoding

import matplotlib.pyplot as plt

ordenadas_estimadas = []

if metodo == '2': # Método exponencial
    for abscissa in abscissas:
        ordenadas_estimadas.append(b * math.exp(a * abscissa))
else:
    for abscissa in abscissas:
        ordenadas_estimadas.append(a + b * abscissa)

# plt.scatter(abscissas, ordenadas, color='orange', label='pontos originais (x_i, y_i)')
plt.plot(abscissas, ordenadas, linestyle='dashed', marker='D', label='pontos originais (x_i, y_i)')

if metodo == '2': # Método exponencial
    label_grafico_estimado = f'ŷ_i = {truncar(b, 6)} e ^ ({truncar(a, 6)} * x_i)'
else:
    label_grafico_estimado = f'ŷ_i = {truncar(a, 6)} + {truncar(b, 6)} * x_i'

plt.plot(
    abscissas,
    ordenadas_estimadas,
    linestyle='solid',
    marker='o',
    label=label_grafico_estimado
)
plt.legend()
plt.show()
