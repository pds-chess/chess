#pragma once

#include <string>
#include <sstream>

class Coordinates {
private:
    int row_;
    int column_;
public:
    Coordinates();
    Coordinates(int row, int column);
    int getRow() const;
    int getCol() const;
    std::string toString();
    void fromString(const std::string& str);
};
