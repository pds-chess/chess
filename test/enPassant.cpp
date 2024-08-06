#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include "Pawn.hpp"

TEST_CASE("En passant validation (Match.hpp public)"){
    // SUBCASE("Using board"){
    //     Board b_;

    //     b_.getPiece(Coordinates(6,4))->setCoords(Coordinates(3,4)); b_.update();
    //     b_.getPiece(Coordinates(1,3))->movePiece(Coordinates(3,3)); b_.update();
    //     //b_.movePiece(b_.getPiece(Coordinates(3,4)), Coordinates(2,3)); b_.update();

    //     //CHECK(b_.getPiece(Coordinates(2,3)) != nullptr);
    //     CHECK(b_.getPiece(Coordinates(3,4))->validateMove(Coordinates(2,3)));
    //     //CHECK(b_.getPiece(Coordinates(3,3)) == nullptr);
    // }
    SUBCASE("Using match"){
        Match m("branco", "preto");

        m.movePiece(6,4,4,4);
        m.movePiece(1,0,3,0);
        m.movePiece(4,4,3,4);
        m.movePiece(1,3,3,3);
        m.movePiece(3,4,2,3);
        CHECK(m.board_.getPiece(Coordinates(2,3)) != nullptr);
        CHECK(m.board_.getPiece(Coordinates(3,3)) == nullptr);
        // CHECK(m.board_.getPiece(Coordinates(3,3)) != nullptr);
        // CHECK(m.board_.getPiece(Coordinates(2,3)) == nullptr);
        // Pawn* pawn = dynamic_cast<Pawn*>(m.board_.getPiece(Coordinates(3,4)));
        // CHECK(pawn != nullptr);
        // CHECK(pawn->validateEnPassant(Coordinates(2,3)));
        // CHECK(pawn->validateMove(Coordinates(2,3)));
    }
}