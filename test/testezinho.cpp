#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "/home/brenodt/PDS2/chess/include/King.hpp"
#include "/home/brenodt/PDS2/chess/include/Match.hpp"

TEST_CASE("example"){
    Board b_;
    CHECK(b_.getPiece(Coordinates(7,4))->validateMove(Coordinates(7,6)));
}