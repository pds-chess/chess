#include "Pawn.hpp"

class Pawn: Piece{
    private:
        bool moved_;
    public:
        Pawn(Coordinates initial_coords, Color color) : moved_(false), Piece::Piece(initial_coords, color){
        };
        bool validateMove(Coordinates final_coordinates) const {
        };
        void en_passant();
};