#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include "Queen.hpp"


TEST_CASE("ValidateMove") {
    Coordinates QueenB=Coordinates(0,3);
    Coordinates QueenW=Coordinates(7,3);

    //WHITE
    SUBCASE ("Queen move NW") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(5,5));
    b_.update();
    QueenW=Coordinates(5,5);
    b_.update();
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,2)) == true);
    }
    SUBCASE ("Queen move NE") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(5,4));
    b_.update();
    QueenW=Coordinates(5,4);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,7)) == true);
    }
    SUBCASE ("Queen move SE") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.update();
    QueenW=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,7)) == true);
    }
    SUBCASE ("Queen move SW") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.update();
    QueenW=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,3)) == true);
    }
    SUBCASE ("Queen fails to move NW due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(3,4));
    b_.update();
    QueenW=Coordinates(4,5);
    QueenB=Coordinates(3,4);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,3)) == false);
    }
    SUBCASE ("Queen fails to move NE due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(3,6));
    b_.update();
    QueenW=Coordinates(4,5);
    QueenB=Coordinates(3,6);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,7)) == false);
    }
    SUBCASE ("Queen fails to move SE due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(4,6));
    b_.update();
    QueenW=Coordinates(3,5);
    QueenB=Coordinates(4,6);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,7)) == false);
    }
    SUBCASE ("Queen fails to move SW due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(4,4));
    b_.update();
    QueenW=Coordinates(3,5);
    QueenB=Coordinates(4,4);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,3)) == false);
    }
    SUBCASE ("Queen move N") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,3));
    b_.update();
    QueenW=Coordinates(4,3);
    b_.update();
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,3)) == true);
    }
    SUBCASE ("Queen move E") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(2,3));
    b_.update();
    QueenW=Coordinates(2,3);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,7)) == true);
    }
    SUBCASE ("Queen move W") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.update();
    QueenW=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(3,0)) == true);
    }
    SUBCASE ("Queen move S") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.update();
    QueenW=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,5)) == true);
    }
    SUBCASE ("Queen fails to move N due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(3,5));
    b_.update();
    QueenW=Coordinates(4,5);
    QueenB=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,5)) == false);
    }
    SUBCASE ("Queen fails to move E due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,0));
    b_.getPiece(QueenB)->setCoords(Coordinates(4,4));
    b_.update();
    QueenW=Coordinates(4,0);
    QueenB=Coordinates(4,4);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(4,7)) == false);
    }
    SUBCASE ("Queen fails to move W due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,7));
    b_.getPiece(QueenB)->setCoords(Coordinates(3,3));
    b_.update();
    QueenW=Coordinates(3,7);
    QueenB=Coordinates(3,3);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(3,0)) == false);
    }
    SUBCASE ("Queen fails to move S due to piece in the way") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(2,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(3,5));
    b_.update();
    QueenW=Coordinates(2,5);
    QueenB=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,5)) == false);
    }
}

TEST_CASE("ValidateCapture") {
    Coordinates QueenB=Coordinates(0,3);
    Coordinates QueenW=Coordinates(7,3);
    
    SUBCASE ("White Queen capture Black Queen - NW") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(2,3));
    b_.update();
    QueenW=Coordinates(4,5);
    QueenB=Coordinates(2,3);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen capture Black Queen - NE") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(2,7));
    b_.update();
    QueenW=Coordinates(4,5);
    QueenB=Coordinates(2,7);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen capture Black Queen - SE") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(5,7));
    b_.update();
    QueenW=Coordinates(3,5);
    QueenB=Coordinates(5,7);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen capture Black Queen - SW") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(5,3));
    b_.update();
    QueenW=Coordinates(3,5);
    QueenB=Coordinates(5,3);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen fails to capture White Piece - NW") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(2,3));
    b_.update();
    QueenW=Coordinates(4,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,3)) == false);
    }
    SUBCASE ("White Queen fails to capture White Piece - NE") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(2,7));
    b_.update();
    QueenW=Coordinates(4,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,7)) == false);
    }
    SUBCASE ("White Queen fails to capture White Piece - SE") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(5,7));
    b_.update();
    QueenW=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,7)) == false);
    }
    SUBCASE ("White Queen fails to capture White Piece - SW") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(7,2))->setCoords(Coordinates(5,3));
    b_.update();
    QueenW=Coordinates(3,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,3)) == false);
    }
    SUBCASE ("White Queen capture Black Queen - N") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(2,5));
    b_.update();
    QueenW=Coordinates(4,5);
    QueenB=Coordinates(2,5);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen capture Black Queen - E") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,0));
    b_.getPiece(QueenB)->setCoords(Coordinates(4,7));
    b_.update();
    QueenW=Coordinates(4,0);
    QueenB=Coordinates(4,7);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen capture Black Queen - W") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,7));
    b_.getPiece(QueenB)->setCoords(Coordinates(4,0));
    b_.update();
    QueenW=Coordinates(4,7);
    QueenB=Coordinates(4,0);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen capture Black Queen - S") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(2,5));
    b_.getPiece(QueenB)->setCoords(Coordinates(5,5));
    b_.update();
    QueenW=Coordinates(2,5);
    QueenB=Coordinates(5,5);
    CHECK(b_.getPiece(QueenW)->validateMove(QueenB) == true);
    }
    SUBCASE ("White Queen fails to capture White Piece - N") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(2,5));
    b_.update();
    QueenW=Coordinates(4,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(2,5)) == false);
    }
    SUBCASE ("White Queen fails to capture White Piece - E") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,0));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,7));
    b_.update();
    QueenW=Coordinates(4,0);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(4,7)) == false);
    }
    SUBCASE ("White Queen fails to capture White Piece - W") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(4,7));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,0));
    b_.update();
    QueenW=Coordinates(4,7);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(4,0)) == false);
    }
    SUBCASE ("White Queen fails to capture White Piece - S") {
    Board b_;
    b_.getPiece(QueenW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(5,5));
    b_.update();
    QueenW=Coordinates(2,5);
    CHECK(b_.getPiece(QueenW)->validateMove(Coordinates(5,5)) == false);
    }
}
