#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include "King.hpp"


TEST_CASE("ValidateMove") {
    Coordinates BlackPiece=Coordinates(1,0);
    Coordinates KingW=Coordinates(7,4);

 //WHITE
    SUBCASE ("King move N") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(4,5)) == true);
    }
    SUBCASE ("King move NW") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(4,4)) == true);
    }
    SUBCASE ("King move W") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(5,4)) == true);
    }
    SUBCASE ("King move E") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(5,6)) == true);
    }
    SUBCASE ("King move NE") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(4,6)) == true);
    }
    SUBCASE ("King move SW") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.update();
    KingW=Coordinates(2,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(3,4)) == true);
    }
    SUBCASE ("King move S") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.update();
    KingW=Coordinates(2,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(3,5)) == true);
    }
    SUBCASE ("King move SE") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.update();
    KingW=Coordinates(2,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(3,6)) == true);
    }
}
TEST_CASE("ValidateCapture") {
    Coordinates BlackPiece=Coordinates(1,0);
    Coordinates KingW=Coordinates(7,4);

    SUBCASE ("White King capture Black Piece - N") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(4,5));
    b_.update();
    KingW=Coordinates(5,5);
    BlackPiece=Coordinates(4,5);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King capture Black Piece - NW") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(4,4));
    b_.update();
    KingW=Coordinates(5,5);
    BlackPiece=Coordinates(4,4);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King capture Black Piece - W") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(5,4));
    b_.update();
    KingW=Coordinates(5,5);
    BlackPiece=Coordinates(5,4);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King capture Black Piece - E") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(5,6));
    b_.update();
    KingW=Coordinates(5,5);
    BlackPiece=Coordinates(5,6);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King capture Black Piece - NE") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(4,6));
    b_.update();
    KingW=Coordinates(5,5);
    BlackPiece=Coordinates(4,6);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King capture Black Piece - SW") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(3,4));
    b_.update();
    KingW=Coordinates(2,5);
    BlackPiece=Coordinates(3,4);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King capture Black Piece - S") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(3,5));
    b_.update();
    KingW=Coordinates(2,5);
    BlackPiece=Coordinates(3,5);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King capture Black Piece - SE") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.getPiece(BlackPiece)->setCoords(Coordinates(3,6));
    b_.update();
    KingW=Coordinates(2,5);
    BlackPiece=Coordinates(3,6);
    CHECK(b_.getPiece(KingW)->validateMove(BlackPiece) == true);
    }
    SUBCASE ("White King fails to capture White Piece - N") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,5));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(4,5)) == false);
    }
    SUBCASE ("White King fails to capture White Piece - NW") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,4));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(4,4)) == false);
    }
    SUBCASE ("White King fails to capture White Piece - W") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(5,4));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(5,4)) == false);
    }
    SUBCASE ("White King fails to capture White Piece - E") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(5,6));
    b_.update();
    KingW=Coordinates(5,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(5,6)) == false);
    }
    SUBCASE ("White King fails to capture White Piece - NE") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,6));
    b_.update();
    KingW=Coordinates(2,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(4,6)) == false);
    }
    SUBCASE ("White King fails to capture White Piece - SW") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(3,4));
    b_.update();
    KingW=Coordinates(2,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(3,4)) == false);
    }
    SUBCASE ("White King fails to capture White Piece - S") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(3,5));
    b_.update();
    KingW=Coordinates(2,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(3,5)) == false);
    }
    SUBCASE ("White King fails to capture White Piece - SE") {
    Board b_;
    b_.getPiece(KingW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(3,6));
    b_.update();
    KingW=Coordinates(2,5);
    CHECK(b_.getPiece(KingW)->validateMove(Coordinates(3,6)) == false);
    }
}
