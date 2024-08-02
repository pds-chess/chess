#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "King.hpp"
#include "Board.hpp"

//Comando para compilar:
//g++ include/Color.hpp include/GameState.hpp chess/model/util/Coordinates.cpp include/Move.hpp include/PieceType.hpp chess/model/Pieces/Piece.cpp chess/model/Pieces/PieceFactory.cpp chess/model/Player.cpp chess/model/Pieces/King.cpp chess/model/Pieces/Queen.cpp chess/model/Pieces/Knight.cpp chess/model/Pieces/Pawn.cpp chess/model/Pieces/Bishop.cpp chess/model/Pieces/Rook.cpp chess/model/Board.cpp chess/model/History.cpp chess/model/Match.cpp test/testezinho.cpp -I include -o test/testezinho
//Execute o comando fora de qualquer pasta

TEST_CASE("example"){
    Board b_;
    CHECK(b_.getPiece(Coordinates(7,4))->validateMove(Coordinates(7,6)) == false);
}