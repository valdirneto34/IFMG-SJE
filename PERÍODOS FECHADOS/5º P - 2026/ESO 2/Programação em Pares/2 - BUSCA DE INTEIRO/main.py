from random import randint

vetor = []

for c in range(0, 100):
    n = randint(1, 100)
    vetor.append(n)

escolha = int(input('Digite um número entre 1 e 100: '))

existe = 0
for v in vetor:
    if escolha == v:
        existe = 1

if existe:
    print(f'Elemento {escolha} \033[32mencontrado\033[m na posição {vetor.index(escolha)}!')
else:
    print(f'Elemento {escolha} \033[31mnão encontrado\033[m!')