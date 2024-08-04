#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include "Knight.hpp"


TEST_CASE("ValidateMove") {
    Coordinates KnightB=Coordinates(0,1);
    Coordinates KnightW=Coordinates(7,1);

 //WHITE
    SUBCASE ("Knight move NNW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,4)) == true);
    }
    SUBCASE ("Knight move WNW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,3)) == true);
    }
    SUBCASE ("Knight move NNE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,6)) == true);
    }
    SUBCASE ("Knight move ESE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,7)) == true);
    }
    SUBCASE ("Knight move SSW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,4)) == true);
    }
    SUBCASE ("Knight move WSW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,3)) == true);
    }
    SUBCASE ("Knight move SSE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,6)) == true);
    }
    SUBCASE ("Knight move ESE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,7)) == true);
    }
}
TEST_CASE("ValidateCapture") {
    Coordinates KnightB=Coordinates(0,1);
    Coordinates KnightW=Coordinates(7,1);

    SUBCASE ("White Knight capture Black Knight - NNW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    KnightB=Coordinates(3,4);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight capture Black Knight - WNW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(4,3));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    KnightB=Coordinates(4,3);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight capture Black Knight - NNE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    KnightB=Coordinates(3,6);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight capture Black Knight - ESE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(4,7));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    KnightB=Coordinates(4,7);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight capture Black Knight - SSW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    KnightB=Coordinates(4,4);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight capture Black Knight - WSW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(3,3));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    KnightB=Coordinates(3,3);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight capture Black Knight - SSE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(4,6));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    KnightB=Coordinates(4,6);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight capture Black Knight - ESE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(KnightB)->setCoords(Coordinates(3,7));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    KnightB=Coordinates(3,7);
    CHECK(b_.getPiece(KnightW)->validateMove(KnightB) == true);
    }
    SUBCASE ("White Knight fails to capture White Piece - NNW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,4)) == false);
    }
    SUBCASE ("White Knight fails to capture White Piece - WNW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,3));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,3)) == false);
    }
    SUBCASE ("White Knight fails to capture White Piece - NNE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,6)) == false);
    }
    SUBCASE ("White Knight fails to capture White Piece - ESE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(5,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,7));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(5,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(4,5));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(5,6));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(4,6));
    b_.update();
    KnightW=Coordinates(5,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,7)) == false);
    }
    SUBCASE ("White Knight fails to capture White Piece - SSW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,4));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,4)) == false);
    }
    SUBCASE ("White Knight fails to capture White Piece - WSW") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(3,3));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,3)) == false);
    }
    SUBCASE ("White Knight fails to capture White Piece - SSE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(4,6));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(4,6)) == false);
    }
    SUBCASE ("White Knight fails to capture White Piece - ESE") {
    Board b_;
    b_.getPiece(KnightW)->setCoords(Coordinates(2,5));
    b_.getPiece(Coordinates(7,7))->setCoords(Coordinates(3,7));
    b_.getPiece(Coordinates(6,0))->setCoords(Coordinates(2,4));
    b_.getPiece(Coordinates(7,0))->setCoords(Coordinates(3,4));
    b_.getPiece(Coordinates(6,1))->setCoords(Coordinates(3,5));
    b_.getPiece(Coordinates(6,3))->setCoords(Coordinates(3,6));
    b_.getPiece(Coordinates(6,2))->setCoords(Coordinates(2,6));
    b_.update();
    KnightW=Coordinates(2,5);
    CHECK(b_.getPiece(KnightW)->validateMove(Coordinates(3,7)) == false);
    }
}
