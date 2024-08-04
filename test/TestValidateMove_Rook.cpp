#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include "Rook.hpp"


TEST_CASE("ValidateMove") {
    Coordinates rookB=Coordinates(0,0);
    Coordinates rookW=Coordinates(7,0);

    //WHITE
    SUBCASE ("Rook move N") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,3));
    b_.update();
    rookW=Coordinates(4,3);
    b_.update();
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(2,3)) == true);
    }
    SUBCASE ("Rook move E") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(2,3));
    b_.update();
    rookW=Coordinates(2,3);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(2,7)) == true);
    }
    SUBCASE ("Rook move W") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(3,5));
    b_.update();
    rookW=Coordinates(3,5);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(3,0)) == true);
    }
    SUBCASE ("Rook move S") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(3,5));
    b_.update();
    rookW=Coordinates(3,5);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(5,5)) == true);
    }
    SUBCASE ("Rook fails to move N due to piece in the way") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,5));
    b_.getPiece(rookB)->setCoords(Coordinates(3,5));
    b_.update();
    rookW=Coordinates(4,5);
    rookB=Coordinates(3,5);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(2,5)) == false);
    }
    SUBCASE ("Rook fails to move E due to piece in the way") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,0));
    b_.getPiece(rookB)->setCoords(Coordinates(4,4));
    b_.update();
    rookW=Coordinates(4,0);
    rookB=Coordinates(4,4);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(4,7)) == false);
    }
    SUBCASE ("Rook fails to move W due to piece in the way") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(3,7));
    b_.getPiece(rookB)->setCoords(Coordinates(3,3));
    b_.update();
    rookW=Coordinates(3,7);
    rookB=Coordinates(3,3);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(3,0)) == false);
    }
    SUBCASE ("Rook fails to move S due to piece in the way") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(2,5));
    b_.getPiece(rookB)->setCoords(Coordinates(3,5));
    b_.update();
    rookW=Coordinates(2,5);
    rookB=Coordinates(3,5);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(5,5)) == false);
    }
}

TEST_CASE("ValidateCapture") {
    Coordinates rookB=Coordinates(0,0);
    Coordinates rookW=Coordinates(7,0);
    
    SUBCASE ("White Rook capture Black Rook - N") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,5));
    b_.getPiece(rookB)->setCoords(Coordinates(2,5));
    b_.update();
    rookW=Coordinates(4,5);
    rookB=Coordinates(2,5);
    CHECK(b_.getPiece(rookW)->validateMove(rookB) == true);
    }
    SUBCASE ("White Rook capture Black Rook - E") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,0));
    b_.getPiece(rookB)->setCoords(Coordinates(4,7));
    b_.update();
    rookW=Coordinates(4,0);
    rookB=Coordinates(4,7);
    CHECK(b_.getPiece(rookW)->validateMove(rookB) == true);
    }
    SUBCASE ("White Rook capture Black Rook - W") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,7));
    b_.getPiece(rookB)->setCoords(Coordinates(4,0));
    b_.update();
    rookW=Coordinates(4,7);
    rookB=Coordinates(4,0);
    CHECK(b_.getPiece(rookW)->validateMove(rookB) == true);
    }
    SUBCASE ("White Rook capture Black Rook - S") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(2,5));
    b_.getPiece(rookB)->setCoords(Coordinates(5,5));
    b_.update();
    rookW=Coordinates(2,5);
    rookB=Coordinates(5,5);
    CHECK(b_.getPiece(rookW)->validateMove(rookB) == true);
    }
    SUBCASE ("White Rook fails to capture White Piece - N") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(2,5));
    b_.update();
    rookW=Coordinates(4,5);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(2,5)) == false);
    }
    SUBCASE ("White Rook fails to capture White Piece - E") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,0));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,7));
    b_.update();
    rookW=Coordinates(4,0);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(4,7)) == false);
    }
    SUBCASE ("White Rook fails to capture White Piece - W") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(4,7));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,0));
    b_.update();
    rookW=Coordinates(4,7);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(4,0)) == false);
    }
    SUBCASE ("White Rook fails to capture White Piece - S") {
    Board b_;
    b_.getPiece(rookW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(5,5));
    b_.update();
    rookW=Coordinates(2,5);
    CHECK(b_.getPiece(rookW)->validateMove(Coordinates(5,5)) == false);
    }
}
