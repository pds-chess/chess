#include "ConsoleView.hpp"
#include "GameState.hpp"
#include <iostream>
#include <stdexcept>

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
        std::cout << "\nEscolha uma opção: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\nEscreva o nome do Jogador de peças BRANCAS: " <<std::endl;
                std::cin >> playerA;
                std::cout << "Escreva o nome do Jogador de peças PRETAS: " <<std::endl;
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
                std::cin.clear();
                std::cin.ignore(512, '\n');
        }
    } while (choice != 0);
}

void Console::createNewGame(std::string playerA, std::string playerB) {
    Match match = Match(playerA, playerB);
    while (match.getGameState() == inProgress){
        std::cout << "==================================================" << std::endl << std::endl;
        std::cout << match.boardToString() << std::endl;
        printGameActions(match);
    }
    printGameEnd(match);
}

void Console::printGameActions(Match& match) {
    int choice;
    std::cout << "\nVez de " << match.getCurrentPlayerName() << ": " << std::endl;
    std::cout << "1. Fazer Movimento" << std::endl;
    std::cout << "2. Propor Empate" << std::endl;
    std::cout << "3. Ver todas as peças adversárias que foram capturadas" << std::endl;
    std::cout << "\nEscolha uma ação: ";
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
            std::cin.clear();
            std::cin.ignore(512, '\n');
    }
}

void Console::movePiece(Match& match){
    int row_origin, col_origin, row_destiny, col_destiny;
    std::string input;

    std::cout << "Escreva a coordenada da peça que deseja mover (Ex: a1): ";
    std::cin >> input;
    row_origin = abs((input[1]-48)-9);
    col_origin = input[0]-96;

    std::cout << "Escreva a coordenada para onde deseja mover a peça (Ex: a2): ";
    std::cin >> input;
    row_destiny = abs((input[1]-48)-9);
    col_destiny = input[0]-96;

    try{
        match.movePiece(row_origin-1, col_origin-1, row_destiny-1, col_destiny-1);
    } catch(std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    } catch(std::logic_error& e){
        std::cout << e.what() << std::endl;
    } catch(...){
        std::cout << "Erro não identificado" << std::endl;
    }
}

void Console::handleDraw(Match& match) {
    char response;
    std::cout << match.getCurrentPlayerName() <<" propôs um empate." << std::endl;
    std::cout << "Ambos jogadores concordam em finalizar o jogo? (s/n): ";
    std::cin >> response;

    if (response == 's') {
        match.draw();
        std::cout << "Empate aceito." << std::endl;
    } else {
        std::cout << "Empate rejeitado. O jogo continua." << std::endl;
    }
}



void Console::printGameEnd(Match& match) {
    std::cout << "==================================================" << std::endl << std::endl;
    std::cout << match.boardToString() << std::endl;

    std::cout << "\nFIM DE JOGO!" << std::endl;
    Gamestate game_state = match.getGameState();
    if(game_state==Draw){
        std::cout << "Jogo terminou em empate." << std::endl;
    }
    else if(game_state==VictoryW){
        std::cout << "Jogador de peças brancas venceu." << std::endl;
    }
    else {
        std::cout << "Jogador de peças pretas venceu." << std::endl;
    }
}

void Console::printMatchHistory() {
    // Código para imprimir o histórico de partidas
}

void Console::printMatch(int matchId) {
    // Código para imprimir uma partida específica
}

void Console::showCapturedPieces(Match& match){
    std::cout << "\n" + match.showCapturedPieces() << std::endl;
    std::cout << "\nAperte enter para continuar.";
    std::cin.clear();
    std::cin.ignore(512, '\n');
    std::cin.get();
}