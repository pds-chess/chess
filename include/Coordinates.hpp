#pragma once;

class Coordinates{
    private:
    int row_;
    int column_;
    public:
        Coordinates(int row, char column);
        int getRow() const;
        int getCol() const;
};
