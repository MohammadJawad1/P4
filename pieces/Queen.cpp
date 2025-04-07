#include "Queen.hpp"

/**
 * @brief Default Constructor.
 * @post Sets piece_size_ to 9 and type to "QUEEN"
 */
Queen::Queen() : ChessPiece() { setSize(4); setType("QUEEN"); }

/**
 * @brief Parameterized constructor.
 * @param color: The color of the Queen.
 * @param row: 0-indexed row position of the Queen.
 * @param col: 0-indexed column position of the Queen.
 * @param movingUp: Flag indicating whether the Queen is moving up.
 */
Queen::Queen(const std::string& color, const int& row, const int& col, const bool& movingUp)
    : ChessPiece(color, row, col, movingUp, 4, "QUEEN") {}

// YOUR CODE HERE 
bool Queen::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const 
{
    // Not on the board 
    if (getRow() == -1 || getColumn() == -1) { return false; } 
    // Out of bounds target
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; };

    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece && target_piece->getColor() == getColor()) { return false; }

    return false;
}