#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"

TEST_CASE("En passant validation"){
    Match m("Branco", "Preto");

    SUBCASE("Middle board - White"){
        m.movePiece(6,4,4,4);
        m.movePiece(1,0,2,0);
        m.movePiece(4,4,3,4);
        m.movePiece(1,3,3,3);
        m.movePiece(3,4,2,3);
        CHECK(m.board_.getPiece(Coordinates(2,3)) != nullptr); //true
    }
    SUBCASE("Middle board, moved twice - White"){
        m.movePiece(6,4,4,4);
        m.movePiece(1,3,2,3);
        m.movePiece(4,4,3,4);
        m.movePiece(2,3,3,3);
        //m.movePiece(3,4,2,3);
        CHECK(m.board_.getPiece(Coordinates(2,3)) == nullptr); //false
    }
}