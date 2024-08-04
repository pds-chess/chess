#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Match.hpp"
#include <stdexcept>

TEST_CASE ("Valid coordinate"){
    int row = 0, col =0;
    Coordinates coords = Coordinates(row, col);
    CHECK(coords.getRow() == row);
    CHECK(coords.getCol() == col);
    row =4, col = 3;
    coords = Coordinates(row, col);
    CHECK(coords.getRow() == row);
    CHECK(coords.getCol() == col);
};

TEST_CASE("Invalid coordinate"){
    int row=0, col=8;
    CHECK_THROWS_AS(Coordinates(row, col), std::invalid_argument);
    row=0, col=-1;
    CHECK_THROWS_AS(Coordinates(row, col), std::invalid_argument);
    row=-1, col=5;
    CHECK_THROWS_AS(Coordinates(row, col), std::invalid_argument);
    row=8, col=5;
    CHECK_THROWS_AS(Coordinates(row, col), std::invalid_argument);
}

TEST_CASE("Create Board"){
    Board board_;
    std::list<Piece*> pieces_ = board_.getPieces();
    CHECK(pieces_.size()==32);
    std::map<PieceType, int> num_pieces;
    for(auto item: pieces_){
        num_pieces[item->getType()]++;
    }
    CHECK(num_pieces[PAWN]==16);
    CHECK(num_pieces[ROOK]==4);
    CHECK(num_pieces[KNIGHT]==4);
    CHECK(num_pieces[BISHOP]==4);
    CHECK(num_pieces[QUEEN]==2);
    CHECK(num_pieces[KING]==2);

}

TEST_CASE("Get Piece"){
    Board board_;
    CHECK(board_.getPiece(Coordinates(0, 0))->getType()==ROOK);
    CHECK(board_.getPiece(Coordinates(7, 7))->getType()==ROOK);
    CHECK(board_.getPiece(Coordinates(2,0))==nullptr);
}

TEST_CASE("Create Piece"){
    Board board_;
    SUBCASE("Valid Creation"){
        REQUIRE(board_.getPiece(Coordinates(2,0))==nullptr);
        board_.createPiece(Coordinates(2,0), White, ROOK);
        CHECK(board_.getPiece(Coordinates(2,0))->getType()==ROOK);
    }
    SUBCASE("Invalid Creation"){
        CHECK_THROWS_AS(board_.createPiece(Coordinates(1,0), White, ROOK), std::logic_error);
    }
}



// TEST_CASE ("Castle validation"){
//     Board b_;

//     Coordinates kingW = Coordinates(7,4);
//     Coordinates rookWS = Coordinates(7,7);
//     Coordinates rookWL = Coordinates(7,0);
//     Coordinates short_W_1 = Coordinates(7,5);
//     Coordinates short_W_2 = Coordinates(7,6);
//     Coordinates long_W_1 = Coordinates(7,1);
//     Coordinates long_W_2 = Coordinates(7,2);
//     Coordinates long_W_3 = Coordinates(7,3);

//     Coordinates kingB = Coordinates(0,4);
//     Coordinates rookBS = Coordinates(0,7);
//     Coordinates rookBL = Coordinates(0,0);
//     Coordinates short_B_1 = Coordinates(0,5);
//     Coordinates short_B_2 = Coordinates(0,6);
//     Coordinates long_B_1 = Coordinates(0,1);
//     Coordinates long_B_2 = Coordinates(0,2);
//     Coordinates long_B_3 = Coordinates(0,3);

//     SUBCASE("White king"){
//         SUBCASE("Short Castle"){
//             SUBCASE("No pieces between, no move"){
//                 b_.removePiece(short_W_1);
//                 b_.removePiece(short_W_2);
//                 CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == true);
//             }
//             SUBCASE("One piece between 1"){
//                 b_.removePiece(short_W_1);
//                 CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
//             }
//             SUBCASE("One piece between 2"){
//                 b_.removePiece(short_W_2);
//                 CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
//             }
//             SUBCASE("Rook has moved"){
//                 b_.removePiece(short_W_1);
//                 b_.removePiece(short_W_2);
//                 b_.getPiece(rookWS)->movePiece(short_W_2);
//                 b_.update();
//                 b_.getPiece(short_W_2)->movePiece(rookWS);
//                 b_.update();
//                 CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
//             }
//             SUBCASE("King has moved"){
//                 b_.removePiece(short_W_1);
//                 b_.removePiece(short_W_2);   
//                 b_.getPiece(kingW)->movePiece(short_W_1);
//                 b_.update();
//                 b_.getPiece(short_W_1)->movePiece(kingW);
//                 b_.update();           
//                 CHECK(b_.getPiece(kingW)->validateMove(short_W_2) == false);
//             }
//         }
//         SUBCASE("Long Castle"){
//             SUBCASE("No pieces between"){
//                 b_.removePiece(long_W_1);
//                 b_.removePiece(long_W_2);
//                 b_.removePiece(long_W_3);
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == true);
//             }
//             SUBCASE("One piece between 1"){
//                 b_.removePiece(long_W_1);
//                 b_.removePiece(long_W_2);
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("One piece between 2"){
//                 b_.removePiece(long_W_1);
//                 b_.removePiece(long_W_3);
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("One piece between 3"){
//                 b_.removePiece(long_W_3);
//                 b_.removePiece(long_W_2);
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("Two pieces between 1"){
//                 b_.removePiece(long_W_1);
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("Two pieces between 2"){
//                 b_.removePiece(long_W_2);
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("Two pieces between 3"){
//                 b_.removePiece(long_W_3);
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("Rook has moved 1"){
//                 b_.removePiece(long_W_1);
//                 b_.removePiece(long_W_2);
//                 b_.removePiece(long_W_3);
//                 b_.getPiece(rookWL)->movePiece(long_W_2);
//                 b_.update();
//                 b_.getPiece(long_W_2)->movePiece(rookWL);
//                 b_.update();
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("Rook has moved 2"){
//                 b_.removePiece(long_W_1);
//                 b_.removePiece(long_W_2);
//                 b_.removePiece(long_W_3);
//                 b_.getPiece(rookWL)->movePiece(long_W_1);
//                 b_.update();
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//             SUBCASE("King has moved "){
//                 b_.removePiece(long_W_1);
//                 b_.removePiece(long_W_2);
//                 b_.removePiece(long_W_3);
//                 b_.getPiece(kingW)->movePiece(long_W_3);
//                 b_.update();
//                 b_.getPiece(long_W_3)->movePiece(kingW);
//                 b_.update();
//                 CHECK(b_.getPiece(kingW)->validateMove(long_W_2) == false);
//             }
//         }
//     }
//     SUBCASE("Black king"){
//         SUBCASE("Short Castle"){
//             SUBCASE("No pieces between, no move"){
//                 b_.removePiece(short_B_1);
//                 b_.removePiece(short_B_2);
//                 CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == true);
//             }
//             SUBCASE("One piece between 1"){
//                 b_.removePiece(short_B_1);
//                 CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
//             }
//             SUBCASE("One piece between 2"){
//                 b_.removePiece(short_B_2);
//                 CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
//             }
//             SUBCASE("Rook has moved"){
//                 b_.removePiece(short_B_1);
//                 b_.removePiece(short_B_2);
//                 b_.getPiece(rookBS)->movePiece(short_B_2);
//                 b_.update();
//                 b_.getPiece(short_B_2)->movePiece(rookBS);
//                 b_.update();
//                 CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
//             }
//             SUBCASE("King has moved"){
//                 b_.removePiece(short_B_1);
//                 b_.removePiece(short_B_2);
//                 b_.getPiece(kingB)->movePiece(short_B_1);
//                 b_.update();
//                 b_.getPiece(short_W_1)->movePiece(kingW);
//                 b_.update();
//                 CHECK(b_.getPiece(kingB)->validateMove(short_B_2) == false);
//             }
//         }
//         SUBCASE("Long Castle"){
//             SUBCASE("No pieces between"){
//                 b_.removePiece(long_B_1);
//                 b_.removePiece(long_B_2);
//                 b_.removePiece(long_B_3);
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == true);
//             }
//             SUBCASE("One piece between 1"){
//                 b_.removePiece(long_B_1);
//                 b_.removePiece(long_B_2);
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("One piece between 2"){
//                 b_.removePiece(long_B_1);
//                 b_.removePiece(long_B_3);
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("One piece between 3"){
//                 b_.removePiece(long_B_3);
//                 b_.removePiece(long_B_2);
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("Two pieces between 1"){
//                 b_.removePiece(long_B_1);
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("Two pieces between 2"){
//                 b_.removePiece(long_B_2);
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("Two pieces between 3"){
//                 b_.removePiece(long_B_3);
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("Rook has moved 1"){
//                 b_.removePiece(long_B_1);
//                 b_.removePiece(long_B_2);
//                 b_.removePiece(long_B_3);
//                 b_.getPiece(rookBL)->movePiece(long_B_2);
//                 b_.update();
//                 b_.getPiece(long_B_2)->movePiece(rookBL);
//                 b_.update();
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("Rook has moved 2"){
//                 b_.removePiece(long_B_1);
//                 b_.removePiece(long_B_2);
//                 b_.removePiece(long_B_3);
//                 b_.getPiece(rookBL)->movePiece(long_B_1);
//                 b_.update();
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//             SUBCASE("King has moved"){
//                 b_.removePiece(long_B_1);
//                 b_.removePiece(long_B_2);
//                 b_.removePiece(long_B_3);
//                 b_.getPiece(kingB)->movePiece(long_B_3);
//                 b_.update();
//                 b_.getPiece(long_B_3)->movePiece(kingB);
//                 b_.update();
//                 CHECK(b_.getPiece(kingB)->validateMove(long_B_2) == false);
//             }
//         }
//     }
// };

// TEST_CASE("En passant validation"){
//     Match m("Branco", "Preto");
//     Board b_;

//     SUBCASE("Middle board - White"){
//         m.movePiece(6,4,4,4);
//         m.movePiece(1,0,2,0);
//         m.movePiece(4,4,3,4);
//         m.movePiece(1,3,3,3);
//         m.movePiece(3,4,2,3);
//         CHECK(b_.getPiece(Coordinates(2,3)) != nullptr); //true
//     }
//     SUBCASE("Middle board, moved twice - White"){
//         b_.getPiece(Coordinates(6,4))->setCoords(Coordinates(4,4));
//         b_.getPiece(Coordinates(1,3))->setCoords(Coordinates(2,3));
//         b_.getPiece(Coordinates(4,4))->setCoords(Coordinates(3,4));
//         b_.getPiece(Coordinates(2,3))->setCoords(Coordinates(3,3));
//         b_.getPiece(Coordinates(3,4))->movePiece(Coordinates(2,3));
//         CHECK(b_.getPiece(Coordinates(2,3)) == nullptr); //false
//     }
//     SUBCASE("Middle board - Black"){
//         b_.getPiece(Coordinates(6,0))->movePiece(Coordinates(6,1));
//         b_.getPiece(Coordinates(1,3))->movePiece(Coordinates(3,3));
//         b_.getPiece(Coordinates(6,1))->movePiece(Coordinates(6,2));
//         b_.getPiece(Coordinates(3,3))->movePiece(Coordinates(4,3));
//         b_.getPiece(Coordinates(6,4))->movePiece(Coordinates(4,4));
//         b_.getPiece(Coordinates(4,3))->movePiece(Coordinates(5,4));
//         CHECK(b_.getPiece(Coordinates(5,4)) != nullptr); //true
//     }
// }