#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"

TEST_CASE ("Castle"){
    Board b_;

    Coordinates kingW = Coordinates(7,4);
    Coordinates rookWS = Coordinates(7,7);
    Coordinates rookWL = Coordinates(7,0);
    Coordinates short_W_1 = Coordinates(7,5);
    Coordinates short_W_2 = Coordinates(7,6);
    Coordinates long_W_1 = Coordinates(7,1);
    Coordinates long_W_2 = Coordinates(7,2);
    Coordinates long_W_3 = Coordinates(7,3);

    Coordinates kingB = Coordinates(0,4);
    Coordinates rookBS = Coordinates(0,7);
    Coordinates rookBL = Coordinates(0,0);
    Coordinates short_B_1 = Coordinates(0,5);
    Coordinates short_B_2 = Coordinates(0,6);
    Coordinates long_B_1 = Coordinates(0,1);
    Coordinates long_B_2 = Coordinates(0,2);
    Coordinates long_B_3 = Coordinates(0,3);

    SUBCASE("White king"){
        SUBCASE("Short Castle"){
            SUBCASE("No pieces between, no move"){
                b_.removePiece(short_W_1);
                b_.removePiece(short_W_2);
                CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == true);
                b_.getPiece(kingW)->movePiece(short_W_2);
                b_.update();
                King* king = dynamic_cast<King*>(b_.getPiece(short_W_2));
                Rook* rook = dynamic_cast<Rook*>(b_.getPiece(short_W_1));
                CHECK(king!=nullptr);
                CHECK(rook!=nullptr);
            }
            SUBCASE("One piece between 1"){
                b_.removePiece(short_W_1);
                CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
            }
            SUBCASE("One piece between 2"){
                b_.removePiece(short_W_2);
                CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
            }
            SUBCASE("Rook has moved"){
                b_.removePiece(short_W_1);
                b_.removePiece(short_W_2);
                b_.getPiece(rookWS)->movePiece(short_W_2);
                b_.update();
                b_.getPiece(short_W_2)->movePiece(rookWS);
                b_.update();
                CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
            }
            SUBCASE("King has moved"){
                b_.removePiece(short_W_1);
                b_.removePiece(short_W_2);   
                b_.getPiece(kingW)->movePiece(short_W_1);
                b_.update();
                b_.getPiece(short_W_1)->movePiece(kingW);
                b_.update();           
                CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
            }
        }
        SUBCASE("Long Castle"){
            SUBCASE("No pieces between, no move"){
                b_.removePiece(long_W_1);
                b_.removePiece(long_W_2);
                b_.removePiece(long_W_3);
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == true);
                b_.getPiece(kingW)->movePiece(long_W_2);
                b_.update();
                King* king = dynamic_cast<King*>(b_.getPiece(long_W_2));
                Rook* rook = dynamic_cast<Rook*>(b_.getPiece(long_W_3));
                CHECK(king!=nullptr);
                CHECK(rook!=nullptr);
            }
            SUBCASE("One piece between 1"){
                b_.removePiece(long_W_1);
                b_.removePiece(long_W_2);
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("One piece between 2"){
                b_.removePiece(long_W_1);
                b_.removePiece(long_W_3);
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("One piece between 3"){
                b_.removePiece(long_W_3);
                b_.removePiece(long_W_2);
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("Two pieces between 1"){
                b_.removePiece(long_W_1);
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("Two pieces between 2"){
                b_.removePiece(long_W_2);
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("Two pieces between 3"){
                b_.removePiece(long_W_3);
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("Rook has moved 1"){
                b_.removePiece(long_W_1);
                b_.removePiece(long_W_2);
                b_.removePiece(long_W_3);
                b_.getPiece(rookWL)->movePiece(long_W_2);
                b_.update();
                b_.getPiece(long_W_2)->movePiece(rookWL);
                b_.update();
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("Rook has moved 2"){
                b_.removePiece(long_W_1);
                b_.removePiece(long_W_2);
                b_.removePiece(long_W_3);
                b_.getPiece(rookWL)->movePiece(long_W_1);
                b_.update();
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
            SUBCASE("King has moved "){
                b_.removePiece(long_W_1);
                b_.removePiece(long_W_2);
                b_.removePiece(long_W_3);
                b_.getPiece(kingW)->movePiece(long_W_3);
                b_.update();
                b_.getPiece(long_W_3)->movePiece(kingW);
                b_.update();
                CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
            }
        }
    }
    SUBCASE("Black king"){
        SUBCASE("Short Castle"){
            SUBCASE("No pieces between, no move"){
                b_.removePiece(short_B_1);
                b_.removePiece(short_B_2);
                CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == true);
                b_.getPiece(kingB)->movePiece(short_B_2);
                b_.update();
                King* king = dynamic_cast<King*>(b_.getPiece(short_B_2));
                Rook* rook = dynamic_cast<Rook*>(b_.getPiece(short_B_1));
                CHECK(king!=nullptr);
                CHECK(rook!=nullptr);
            }
            SUBCASE("One piece between 1"){
                b_.removePiece(short_B_1);
                CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
            }
            SUBCASE("One piece between 2"){
                b_.removePiece(short_B_2);
                CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
            }
            SUBCASE("Rook has moved"){
                b_.removePiece(short_B_1);
                b_.removePiece(short_B_2);
                b_.getPiece(rookBS)->movePiece(short_B_2);
                b_.update();
                b_.getPiece(short_B_2)->movePiece(rookBS);
                b_.update();
                CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
            }
            SUBCASE("King has moved"){
                b_.removePiece(short_B_1);
                b_.removePiece(short_B_2);
                b_.getPiece(kingB)->movePiece(short_B_1);
                b_.update();
                b_.getPiece(short_B_1)->movePiece(kingB);
                b_.update();
                CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
            }
        }
        SUBCASE("Long Castle"){
            SUBCASE("No pieces between"){
                b_.removePiece(long_B_1);
                b_.removePiece(long_B_2);
                b_.removePiece(long_B_3);
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == true);
                b_.getPiece(kingB)->movePiece(long_B_2);
                b_.update();
                King* king = dynamic_cast<King*>(b_.getPiece(long_B_2));
                Rook* rook = dynamic_cast<Rook*>(b_.getPiece(long_B_3));
                CHECK(king!=nullptr);
                CHECK(rook!=nullptr);
            }
            SUBCASE("One piece between 1"){
                b_.removePiece(long_B_1);
                b_.removePiece(long_B_2);
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("One piece between 2"){
                b_.removePiece(long_B_1);
                b_.removePiece(long_B_3);
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("One piece between 3"){
                b_.removePiece(long_B_3);
                b_.removePiece(long_B_2);
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("Two pieces between 1"){
                b_.removePiece(long_B_1);
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("Two pieces between 2"){
                b_.removePiece(long_B_2);
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("Two pieces between 3"){
                b_.removePiece(long_B_3);
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("Rook has moved 1"){
                b_.removePiece(long_B_1);
                b_.removePiece(long_B_2);
                b_.removePiece(long_B_3);
                b_.getPiece(rookBL)->movePiece(long_B_2);
                b_.update();
                b_.getPiece(long_B_2)->movePiece(rookBL);
                b_.update();
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("Rook has moved 2"){
                b_.removePiece(long_B_1);
                b_.removePiece(long_B_2);
                b_.removePiece(long_B_3);
                b_.getPiece(rookBL)->movePiece(long_B_1);
                b_.update();
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
            SUBCASE("King has moved"){
                b_.removePiece(long_B_1);
                b_.removePiece(long_B_2);
                b_.removePiece(long_B_3);
                b_.getPiece(kingB)->movePiece(long_B_3);
                b_.update();
                b_.getPiece(long_B_3)->movePiece(kingB);
                b_.update();
                CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
            }
        }
    }
};