#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"

//Comando para compilar:
//g++ include/Color.hpp include/GameState.hpp chess/model/util/Coordinates.cpp include/Move.hpp include/PieceType.hpp chess/model/Pieces/Piece.cpp chess/model/Pieces/PieceFactory.cpp chess/model/Player.cpp chess/model/Pieces/King.cpp chess/model/Pieces/Queen.cpp chess/model/Pieces/Knight.cpp chess/model/Pieces/Pawn.cpp chess/model/Pieces/Bishop.cpp chess/model/Pieces/Rook.cpp chess/model/Board.cpp chess/model/History.cpp chess/model/Match.cpp test/testezinho.cpp -I include -o test/testezinho
//Execute o comando fora de qualquer pasta

TEST_CASE("example"){
    Board b_;
    CHECK(b_.getPiece(Coordinates(7,4))->validateMove(Coordinates(7,6)) == false);
}

TEST_CASE("Pawn Promotion"){
    Match m("Branco","Preto");

    SUBCASE("White Promotion"){
        m.board_.clearBoard(); m.board_.update();
        m.board_.createPiece(Coordinates(1,4), White, PAWN); m.board_.update();
        m.movePiece(1,4,0,4);
        //Digitar 'R'
        CHECK(m.board_.getPiece(Coordinates(0,4))->getType() == QUEEN);
    }
    SUBCASE("Black Promotion"){
        m.board_.clearBoard(); m.board_.update();
        m.board_.createPiece(Coordinates(6,4), Black, PAWN); m.board_.update();
        m.endTurn();
        m.movePiece(6,4,7,4);
        //Digitar 'R'
        CHECK(m.board_.getPiece(Coordinates(0,4))->getType() == QUEEN);
    }
}