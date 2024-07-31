#include "History.hpp"
#include "Move.hpp"
#include "Coordinates.hpp"
#include "Color.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <list>
#include <algorithm>

History::History(std::string path) : path_to_file_(path) {}

void History::saveMove(Move move){
    std::ofstream file(path_to_file_, std::ios::app); // Abrir o arquivo em modo de adição (append)
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de histórico.");
    }

    file << move.game_id_ << ", "
         << move.origin_coordinates_ << " para "
         << move.final_coordinates_ << ", "
         << (move.color_ == White ? "White" : "Black") << ", "
         << move.player_name_ << "\n";

    file.close();
}

std::list<Move> History::getMoves(int game_id) const {
    std::ifstream file(path_to_file_);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de histórico.");
    }

    std::list<Move> moves;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        int id;
        Coordinates origin, destination;
        Color color;
        std::string player_name;

        std::getline(iss, token, ',');
        id = std::stoi(token);

        if (id != game_id) continue;

        std::getline(iss, token, ',');
        origin = Coordinates::fromString(token);

        std::getline(iss, token, ',');
        destination = Coordinates::fromString(token);

        std::getline(iss, token, ',');
        color = (token == "White") ? White : Black;

        std::getline(iss, token, ',');
        player_name = token;

        // Criar um Move com as informações lidas e adicionar à lista de movimentos
        Move move(origin, destination, color, player_name, game_id);
        moves.push_back(move);
    }

    file.close();
    return moves;
}

std::list<int> History::getGames() const {
    std::ifstream file(path_to_file_);
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo de histórico.");
    }

    std::list<int> game_ids;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::getline(iss, token, ',');

        int game_id = std::stoi(token);
        if (std::find(game_ids.begin(), game_ids.end(), game_id) == game_ids.end()) {
            game_ids.push_back(game_id);
        }
    }

    file.close();
    return game_ids;
}
