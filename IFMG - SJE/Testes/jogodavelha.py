def main():
    game = [' '] * 9
    char = ['X', 'O']
    preenchidos = []
    turn = True
    cont = 0
    while True:
        draw(game)
        print(f'Turno: Jogador: {getPlayer(turn)}')
        check = newPosition(preenchidos)
        game[check-1] = char[getPlayer(turn)-1]
        preenchidos.append(check)
        cont += 1
        if finishGame(game, cont, turn):
            break
        turn = not turn


def finishGame(game, qtd, turn):
    if not win(game) and qtd >= 9:
        draw(game)
        print(f'\n\033[33mDeu Velha! Tentem novamente!\033[m')
        return True
    elif win(game):
        draw(game)
        print(f'\033[32mO Jogador {getPlayer(turn)} Venceu!\033[m')
        return True
    return False


def newPosition(preenchidos):
    while True:
        position = int(
            input(f'Digite uma posição disponível no intervalo de (1-9): '))
        if position not in preenchidos:
            break
        print(f'\033[31mPosição inválida!\033[m',end=' ')
    return position


def win(game):
    # Horizontal Lines
    if game[0] != ' ' and game[0] == game[1] and game[1] == game[2]:
        return True
    if game[3] != ' ' and game[3] == game[4] and game[4] == game[5]:
        return True
    if game[6] != ' ' and game[6] == game[7] and game[7] == game[8]:
        return True
        # Vertical Lines
    if game[0] != ' ' and game[0] == game[3] and game[3] == game[6]:
        return True
    if game[1] != ' ' and game[1] == game[4] and game[4] == game[7]:
        return True
    if game[2] != ' ' and game[2] == game[5] and game[5] == game[8]:
        return True
    # Diagonal Lines
    if game[0] != ' ' and game[0] == game[4] and game[4] == game[8]:
        return True
    if game[2] != ' ' and game[2] == game[4] and game[4] == game[6]:
        return True


def getPlayer(turn):
    if turn:
        return 1
    return 2


def draw(game):
    print('\n')
    line1 = ' | '.join(game[0:3])
    line2 = ' | '.join(game[3:6])
    line3 = ' | '.join(game[6:9])
    print(line1)
    print(line2)
    print(line3)


main()
