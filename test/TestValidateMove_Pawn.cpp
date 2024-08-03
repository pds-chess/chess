#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include "Pawn.hpp"


TEST_CASE("ValidateMove") {
    Coordinates pawnB=Coordinates(1,6);
    Coordinates pawnW=Coordinates(6,6);

    //WHITE
    SUBCASE ("PawnWhite move 1") {
    Board b_;
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(5,6)) == true);
    }
    SUBCASE ("PawnWhite move 2") {
    Board b_;
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(4,6)) == true);
    }
    SUBCASE ("PawnWhite fails to move due to piece in the way") {
    Board b_;
    b_.getPiece(pawnB)->setCoords(Coordinates(5,6));
    b_.update();
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(5,6)) == false);
    }
    SUBCASE ("PawnWhite fails to move due to piece in the way - 2") {
    Board b_;
    b_.getPiece(pawnB)->setCoords(Coordinates(5,6));
    b_.update();
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(4,6)) == false);
    }
    SUBCASE ("PawnWhite fails to move twice (moved=true)") {
    Board b_;
    b_.getPiece(pawnW)->movePiece(Coordinates(5,6));
    b_.update();
    pawnW=Coordinates(5,6);
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(3,6)) == false);
    }
    SUBCASE ("PawnWhite capture PawnBlack") {
    Board b_;
    b_.getPiece(pawnB)->setCoords(Coordinates(5,5));
    b_.update();
    pawnB=Coordinates(5,5);
    CHECK(b_.getPiece(pawnW)->validateMove(pawnB) == true);
    }
    SUBCASE ("PawnWhite capture PawnBlack 2") {
    Board b_;
    b_.getPiece(pawnB)->setCoords(Coordinates(5,7));
    b_.update();
    pawnB=Coordinates(5,7);
    CHECK(b_.getPiece(pawnW)->validateMove(pawnB) == true);
    }
    SUBCASE ("PawnWhite fails to capture White Piece") {
    Board b_;
    b_.getPiece(Coordinates (6,5))->setCoords(Coordinates(5,5));
    b_.update();
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(5,5)) == false);
    }


    //BLACK
    SUBCASE ("PawnBlack move 1") {
    Board b_;
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(2,6)) == true);
    }
    SUBCASE ("PawnBlack move 2") {
    Board b_;
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(3,6)) == true);
    }
    SUBCASE ("PawnBlack fails to move due to piece in the way") {
    Board b_;
    b_.getPiece(pawnW)->setCoords(Coordinates(2,6));
    b_.update();
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(2,6)) == false);
    }
    SUBCASE ("PawnBlack fails to move due to piece in the way - 2") {
    Board b_;
    b_.getPiece(pawnW)->setCoords(Coordinates(2,6));
    b_.update();
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(3,6)) == false);
    }
    SUBCASE ("PawnBlack fails to move twice (moved=true)") {
    Board b_;
    b_.getPiece(pawnB)->movePiece(Coordinates(2,6));
    b_.update();
    pawnB=Coordinates(2,6);
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(4,6)) == false);
    }
    SUBCASE ("PawnBlack capture PawnWhite") {
    Board b_;
    b_.getPiece(pawnW)->setCoords(Coordinates(2,5));
    b_.update();
    pawnW=Coordinates(2,5);
    CHECK(b_.getPiece(pawnB)->validateMove(pawnW) == true);
    }
    SUBCASE ("PawnBlack capture PawnWhite 2") {
    Board b_;
    b_.getPiece(pawnW)->setCoords(Coordinates(2,7));
    b_.update();
    pawnW=Coordinates(2,7);
    CHECK(b_.getPiece(pawnB)->validateMove(pawnW) == true);
    }
    SUBCASE ("PawnBlack fails to capture Black Piece") {
    Board b_;
    b_.getPiece(Coordinates (1,5))->setCoords(Coordinates(2,5));
    b_.update();
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(2,5)) == false);
    }
}
