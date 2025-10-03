# PROGRAMA QUE CALCULA A FÓRMULA DE BHASKARA

from math import pow ,sqrt
from time import sleep
print('=-' * 35)
print('Olá, eu sou um programa que calcula a Fórmula de Bhaskara para você!!')
print('=-' * 35)

cont = 1

while True:
    a = float(input('Insira o valor de A: '))
    b = float(input('Insira o valor de B: '))
    c = float(input('Insira o valor de C: '))
    print('Calculando...\n')
    sleep(2)
    delta = pow(b, 2) - (4 * a * c)
    if delta < 0:
        print(f'O Delta é igual a {delta}.')
        sleep(1)
        print('E por ele ser menor que zero, não existe raiz real!')
    elif delta == 0:
        x1 = ( -b + sqrt(delta)) / (2 * a)
        print(f"Equação possui apenas uma raiz, pois o delta é igual a zero.")
        print(f"A raiz é igual a: {x1}.")
    else:
        x1 = ( -b + sqrt(delta)) / (2 * a)
        x2 = (-b - sqrt(delta)) / (2 * a)
        print(f'O Delta é igual a {delta}.')
        sleep(1)
        print(f'X1 é igual a {x1}.')
        sleep(1)
        print(f'X2 é igual a {x2}.')
        sleep(1)
    opc = str(input('\nVocê quer continuar? [S/N] ')).strip().upper()[0]
    while opc not in 'SN':
        opc = str(input("Opção inválida! Digite novamente: [S/N] ")).strip().upper()[0]
    if opc in 'N':
        break
    cont+=1
print('=-' * 20)
if cont == 1:
    print(f'Realizamos {cont} cálculo hoje!')
else:
    print(f'Realizamos {cont} cálculos hoje!')
sleep(0.5)
print('Programa Encerrado!')
sleep(0.5)
print('Volte sempre que precisar!!')
