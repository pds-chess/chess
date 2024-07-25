#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

class Coordinates {
private:
    int row_;
    int column_;

public:
    Coordinates() : row_(0), column_(0) {}
    Coordinates(int row, int column) : row_(row), column_(column) {}

    int getRow() const {
        return row_;
    }

    int getCol() const {
        return column_;
    }

    std::string toString() const {
        return std::to_string(row_) + "," + std::to_string(column_);
    }

    static Coordinates fromString(const std::string& str) {
        std::istringstream iss(str);
        std::string token;
        int row, column;

        if (std::getline(iss, token, ',')) {
            row = std::stoi(token);
        } else {
            throw std::invalid_argument("String format is incorrect for Coordinates.");
        }

        if (std::getline(iss, token, ',')) {
            column = std::stoi(token);
        } else {
            throw std::invalid_argument("String format is incorrect for Coordinates.");
        }

        return Coordinates(row, column);
    }
};
