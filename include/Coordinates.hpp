#pragma once;

class Coordinates{
    private:
    int row_;
    int column_;
    public:
        Coordinates();
        Coordinates(int row, int column);
        int getRow() const;
        int getCol() const;
};