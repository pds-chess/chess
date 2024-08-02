#include "ConsoleView.hpp"
#include <iostream>

Console::Console() : match() {
    printMenu();
}

Console::~Console() {}

void Console::printMenu() {
    int choice;
    do {
        std::cout << "1. Novo Jogo" << std::endl;
        std::cout << "2. Histórico de Partidas" << std::endl;
        std::cout << "3. Ver todas as peças adversárias que foram capturadas" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                printNewGame();
                break;
            case 2:
                printMatchHistory();
                break;
            case 3:
                showCapturedPieces();
                break;
            case 0:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida!" << std::endl;
        }
    } while (choice != 0);
}

void Console::printNewGame() {
    match.startNewGame();
    while (!match.isGameOver()) {
        printBoard();
        printGameActions();
    }
    printGameEnd();
}

void Console::printBoard() {
    // Código para imprimir o tabuleiro
}

void Console::printGameActions() {
    int choice;
    std::cout << "1. Fazer Movimento" << std::endl;
    std::cout << "2. Propor Empate" << std::endl;
    std::cout << "Escolha uma ação: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            // Código para fazer movimento
            break;
        case 2:
            proposeDraw();
            handleDrawResponse();
            break;
        default:
            std::cout << "Ação inválida!" << std::endl;
    }
}

void Console::proposeDraw() {
    std::cout << "Propondo empate..." << std::endl;
    // Código para lidar com a lógica de proposta de empate
}

void Console::handleDrawResponse() {
    char response;
    std::cout << "Seu oponente propôs um empate. Você aceita? (s/n): ";
    std::cin >> response;

    if (response == 's') {
        match.endGameInDraw();
        std::cout << "Empate aceito. O jogo terminou em empate." << std::endl;
    } else {
        std::cout << "Empate rejeitado. O jogo continua." << std::endl;
    }
}

void Console::printGameEnd() {
    // Código para imprimir o final do jogo
}

void Console::printMatchHistory() {
    // Código para imprimir o histórico de partidas
}

void Console::printMatch(int matchId) {
    // Código para imprimir uma partida específica
}
