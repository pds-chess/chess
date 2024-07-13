#include "Pawn.hpp"

class Pawn: Piece{
    private:
        bool moved_;
    public:
        Pawn(Coordinates initial_coords, Color color) : moved_(false), Piece::Piece(initial_coords, color, *getBoard()){
        };
        bool validateMove(Coordinates final_coordinates) const {
            int incremento = 0;
            if(Piece::getColor())
                 int incremento = -1;
            else int incremento = 1;
            int DeltaRow = (final_coordinates.getRow() - Piece::getCoords().getRow())*incremento;
            int DeltaCol = (final_coordinates.getCol() - Piece::getCoords().getCol())*incremento;
            if (DeltaRow >0 && DeltaRow <= 2  && (DeltaCol==0)) {
                for (int i=2; i<=3 && (i<3 || !moved_); i++)
                    if (getBoard()->getPiece(Coordinates (Piece::getCoords().getRow()+i*incremento, Piece::getCoords().getCol()))!=nullptr)
                        return false;
            }
            else
            if (getBoard()->getPiece(final_coordinates)!=nullptr && getBoard()->getPiece(final_coordinates)->getColor()!=Piece::getColor() && DeltaCol==1 && DeltaRow==1)
                return true;
            return false;
        };
        void en_passant();
};
