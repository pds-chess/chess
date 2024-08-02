#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"

TEST_CASE("En passant validation"){
    Match m("Branco", "Preto");
    Board b_;

    SUBCASE("Middle board - White"){
        m.movePiece(6,4,4,4);
        m.movePiece(1,0,2,0);
        m.movePiece(4,4,3,4);
        m.movePiece(1,3,3,3);
        m.movePiece(3,4,2,3);
        CHECK(b_.getPiece(Coordinates(2,3)) != nullptr); //true
    }
    SUBCASE("Middle board, moved twice - White"){
        b_.getPiece(Coordinates(6,4))->setCoords(Coordinates(4,4));
        b_.getPiece(Coordinates(1,3))->setCoords(Coordinates(2,3));
        b_.getPiece(Coordinates(4,4))->setCoords(Coordinates(3,4));
        b_.getPiece(Coordinates(2,3))->setCoords(Coordinates(3,3));
        b_.getPiece(Coordinates(3,4))->movePiece(Coordinates(2,3));
        CHECK(b_.getPiece(Coordinates(2,3)) == nullptr); //false
    }
    SUBCASE("Middle board - Black"){
        b_.getPiece(Coordinates(6,0))->movePiece(Coordinates(6,1));
        b_.getPiece(Coordinates(1,3))->movePiece(Coordinates(3,3));
        b_.getPiece(Coordinates(6,1))->movePiece(Coordinates(6,2));
        b_.getPiece(Coordinates(3,3))->movePiece(Coordinates(4,3));
        b_.getPiece(Coordinates(6,4))->movePiece(Coordinates(4,4));
        b_.getPiece(Coordinates(4,3))->movePiece(Coordinates(5,4));
        CHECK(b_.getPiece(Coordinates(5,4)) != nullptr); //true
    }
}