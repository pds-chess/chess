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

TEST_CASE("Remove Piece"){
    Board board_;
    CHECK(board_.getPiece(Coordinates(0,0))!=nullptr);
    board_.removePiece(Coordinates(0,0));
    CHECK(board_.getPiece(Coordinates(0,0))==nullptr);
}

TEST_CASE("Create Match"){
    Match match = Match("lebraga", "davi");
    CHECK(match.getCurrentPlayerName()=="lebraga");
}

TEST_CASE("Piece String"){
    Board board_;
    auto piece = board_.getPiece(Coordinates(0,0));
    CHECK(piece->pieceToString()=="Rb");
    piece = board_.getPiece(Coordinates(7,7));
    CHECK(piece->pieceToString()=="Rw");
}

TEST_CASE("Match state"){
    Match match = Match("lebraga", "davi");
    SUBCASE("Match Ongoing"){
        CHECK(match.getGameState()==inProgress);
    }
}

TEST_CASE("King in Check"){
    Board board_ = Board();
    board_.movePiece(board_.getPiece(Coordinates(6,6)), Coordinates(4,6));
    board_.movePiece(board_.getPiece(Coordinates(6,5)), Coordinates(5,5));
    board_.movePiece(board_.getPiece(Coordinates(1,4)), Coordinates(3,4));
    board_.movePiece(board_.getPiece(Coordinates(0,3)), Coordinates(4,7));
    bool checkBoard = board_.isCheck(White);
    CHECK(checkBoard);
}

TEST_CASE("King in Check 2"){
    Board board_ = Board();
    board_.removePiece(Coordinates(0,4));
    board_.createPiece(Coordinates(5,2), Black, KING);
    board_.update();
    CHECK(board_.isCheck(Black));
}

TEST_CASE("Promote pawn"){
    Match match("lebraga", "davi");
    match.movePiece(6, 7, 4 ,7);
    match.movePiece(1, 0, 3, 0);
    match.movePiece(4, 7, 3, 7);
    match.movePiece(3, 0, 4, 0);
    match.movePiece(3, 7, 2, 7);
    match.movePiece(4, 0, 5, 0);
    match.movePiece(2, 7, 1, 6);
    match.movePiece(5, 0, 6, 1);
    match.movePiece(1, 6, 0, 7);
    CHECK(match.isPromote(0, 7));
    match.promotePawn(0, 7, QUEEN);
    match.movePiece(6,1, 7, 0);
    CHECK(match.isPromote(7, 0));
    match.promotePawn(7, 0, KNIGHT);
    match.movePiece(0, 7, 5, 2);
    match.movePiece(7, 0, 5, 1);
}

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
}

// Para executar os testes comentados, coloque todos os métodos e atributos de Match.hpp e Board.hpp como públicos.

// TEST_CASE("En passant validation"){
//     Match m("Branco", "Preto");

//     SUBCASE("Middle board - White"){
//         m.movePiece(6,4,4,4);
//         m.movePiece(1,0,2,0);
//         m.movePiece(4,4,3,4);
//         m.movePiece(1,3,3,3);
//         m.movePiece(3,4,2,3);
//         CHECK(m.board_.getPiece(Coordinates(2,3)) != nullptr);
//     }
// }

// TEST_CASE("Pawn Promotion"){
//     Match m("Branco","Preto");

//     m.board_.clearBoard(); m.board_.update();
//     m.board_.createPiece(Coordinates(1,4), White, PAWN); m.board_.update();
//     std::cout << "\n******DIGITE 'R' PARA VALIDAR O TESTE******\n" << std::endl;
//     m.movePiece(1,4,0,4);
//     //Digitar 'R'
//     CHECK(m.board_.getPiece(Coordinates(0,4))->getType() == QUEEN);
// }

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
    SUBCASE ("PawnWhite move twice (moved=false) and then move one") {
    Board b_;
    b_.getPiece(pawnW)->movePiece(Coordinates(4,6));
    b_.update();
    pawnW=Coordinates(4,6);
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(3,6)) == true);
    }
    SUBCASE ("PawnWhite move one and get behind PawnBlack") {
    Board b_;
    b_.getPiece(pawnB)->setCoords(Coordinates(4,6));
    b_.update();
    pawnB=Coordinates(4,6);
    CHECK(b_.getPiece(pawnW)->validateMove(Coordinates(5,6)) == true);
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
    SUBCASE ("PawnBlack move twice (moved=false) and then move one") {
    Board b_;
    b_.getPiece(pawnB)->movePiece(Coordinates(3,6));
    b_.update();
    pawnB=Coordinates(3,6);
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(4,6)) == true);
    }
    SUBCASE ("PawnBlack move one and get behind PawnWhite") {
    Board b_;
    b_.getPiece(pawnW)->setCoords(Coordinates(3,6));
    b_.update();
    pawnW=Coordinates(3,6);
    CHECK(b_.getPiece(pawnB)->validateMove(Coordinates(2,6)) == true);
    }
}

TEST_CASE("ValidateCapture") {
    Coordinates pawnB=Coordinates(1,6);
    Coordinates pawnW=Coordinates(6,6);

    //WHITE
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