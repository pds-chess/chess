#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include "Bishop.hpp"


TEST_CASE("ValidateMove") {
    Coordinates bishopB=Coordinates(0,5);
    Coordinates bishopW=Coordinates(7,5);

    //WHITE
    SUBCASE ("Bishop move NW") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(5,5));
    b_.update();
    bishopW=Coordinates(5,5);
    b_.update();
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(2,2)) == true);
    }
    SUBCASE ("Bishop move NE") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(5,4));
    b_.update();
    bishopW=Coordinates(5,4);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(2,7)) == true);
    }
    SUBCASE ("Bishop move SE") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.update();
    bishopW=Coordinates(3,5);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(5,7)) == true);
    }
    SUBCASE ("Bishop move SW") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.update();
    bishopW=Coordinates(3,5);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(5,3)) == true);
    }
    SUBCASE ("Bishop fails to move NW due to piece in the way") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(4,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(3,4));
    b_.update();
    bishopW=Coordinates(4,5);
    bishopB=Coordinates(3,4);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(2,3)) == false);
    }
    SUBCASE ("Bishop fails to move NE due to piece in the way") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(4,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(3,6));
    b_.update();
    bishopW=Coordinates(4,5);
    bishopB=Coordinates(3,6);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(2,7)) == false);
    }
    SUBCASE ("Bishop fails to move SE due to piece in the way") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(4,6));
    b_.update();
    bishopW=Coordinates(3,5);
    bishopB=Coordinates(4,6);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(5,7)) == false);
    }
    SUBCASE ("Bishop fails to move SW due to piece in the way") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(4,4));
    b_.update();
    bishopW=Coordinates(3,5);
    bishopB=Coordinates(4,4);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(5,3)) == false);
    }
}

TEST_CASE("ValidateCapture") {
    Coordinates bishopB=Coordinates(0,5);
    Coordinates bishopW=Coordinates(7,5);
    
    SUBCASE ("White Bishop capture Black Bishop - NW") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(4,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(2,3));
    b_.update();
    bishopW=Coordinates(4,5);
    bishopB=Coordinates(2,3);
    CHECK(b_.getPiece(bishopW)->validateMove(bishopB) == true);
    }
    SUBCASE ("White Bishop capture Black Bishop - NE") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(4,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(2,7));
    b_.update();
    bishopW=Coordinates(4,5);
    bishopB=Coordinates(2,7);
    CHECK(b_.getPiece(bishopW)->validateMove(bishopB) == true);
    }
    SUBCASE ("White Bishop capture Black Bishop - SE") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(5,7));
    b_.update();
    bishopW=Coordinates(3,5);
    bishopB=Coordinates(5,7);
    CHECK(b_.getPiece(bishopW)->validateMove(bishopB) == true);
    }
    SUBCASE ("White Bishop capture Black Bishop - SW") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.getPiece(bishopB)->setCoords(Coordinates(5,3));
    b_.update();
    bishopW=Coordinates(3,5);
    bishopB=Coordinates(5,3);
    CHECK(b_.getPiece(bishopW)->validateMove(bishopB) == true);
    }
    SUBCASE ("White Bishop fails to capture White Piece - NW") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(2,3));
    b_.update();
    bishopW=Coordinates(4,5);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(2,3)) == false);
    }
    SUBCASE ("White Bishop fails to capture White Piece - NE") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(2,7));
    b_.update();
    bishopW=Coordinates(4,5);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(2,7)) == false);
    }
    SUBCASE ("White Bishop fails to capture White Piece - SE") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(5,7));
    b_.update();
    bishopW=Coordinates(3,5);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(5,7)) == false);
    }
    SUBCASE ("White Bishop fails to capture White Piece - SW") {
    Board b_;
    b_.getPiece(bishopW)->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(5,3));
    b_.update();
    bishopW=Coordinates(3,5);
    CHECK(b_.getPiece(bishopW)->validateMove(Coordinates(5,3)) == false);
    }
}
