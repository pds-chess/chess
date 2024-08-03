#include "ConsoleView.hpp"
#include "GameState.hpp"
#include <iostream>

Console::Console() {
}

Console::~Console() {}

void Console::printMenu() {
    int choice;
    std::string playerA, playerB;
    do {
        std::cout << "\n1. Novo Jogo" << std::endl;
        std::cout << "2. Histórico de Partidas" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Escreva o nome do Jogador 1: " <<std::endl;
                std::cin >> playerA;
                std::cout << "Escreva o nome do Jogador 2: " <<std::endl;
                std::cin >> playerB;
                createNewGame(playerA, playerB);
                break;
            case 2:
                printMatchHistory();
                break;
            case 0:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida!" << std::endl;
        }
    } while (choice != 0);
}

void Console::createNewGame(std::string playerA, std::string playerB) {
    Match match = Match(playerA, playerB);
    while (match.getGameState() == inProgress){
        std::cout << std::endl << std::endl;
        std::cout << match.boardToString() << std::endl;
        printGameActions(match);
    }
    printGameEnd();
}

void Console::printGameActions(Match& match) {
    int choice;
    std::cout << "\n1. Fazer Movimento" << std::endl;
    std::cout << "2. Propor Empate" << std::endl;
    std::cout << "3. Ver todas as peças adversárias que foram capturadas" << std::endl;
    std::cout << "Escolha uma ação: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            movePiece(match);
            break;
        case 2:
            handleDraw(match);
            break;
        case 3:
            showCapturedPieces(match);
            break;
        default:
            std::cout << "Ação inválida!" << std::endl;
    }
}

void Console::movePiece(Match& match){
    int row_origin, col_origin, row_destiny, col_destiny;
    std::cout << "Escreva a linha da peça que deseja mover: ";
    std::cin >> row_origin;
    std::cout << "Escreva a coluna da peça que deseja mover: ";
    std::cin >> col_origin;
    std::cout << "Escreva a linha para onde deseja mover a peça: ";
    std::cin >> row_destiny;
    std::cout << "Escreva a coluna para onde deseja mover a peça: ";
    std::cin >> col_destiny;
    try{
        match.movePiece(row_origin, col_origin, row_destiny, col_destiny);
    } catch(...){
        std::cout << "Movimento inválido" << std::endl;
    }
}

void Console::handleDraw(Match& match) {
    char response;
    std::cout << match.getCurrentPlayerName() <<" propôs um empate." << std::endl;
    std::cout << "Ambos jogadores concordam em finalizar o jogo? (s/n): ";
    std::cin >> response;

    if (response == 's') {
        match.draw();
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

void Console::showCapturedPieces(Match& match){

}