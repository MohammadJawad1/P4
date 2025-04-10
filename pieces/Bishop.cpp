#include "Bishop.hpp"

/**
 * @brief Default Constructor.
 * @post Sets piece_size_ to 3 and type to "BISHOP"
 */
Bishop::Bishop() : ChessPiece() { setSize(3); setType("BISHOP"); }

/**
 * @brief Parameterized constructor.
 * @param color: The color of the Bishop.
 * @param row: 0-indexed row position of the Bishop.
 * @param col: 0-indexed column position of the Bishop.
 * @param movingUp: Flag indicating whether the Bishop is moving up.
 */
Bishop::Bishop(const std::string& color, const int& row, const int& col, const bool& movingUp)
    : ChessPiece(color, row, col, movingUp, 3, "BISHOP") {}

// YOUR CODE HERE
bool Bishop::canMove(const int& target_row, const int& target_col, const std::vector<std::vector<ChessPiece*>>& board) const 
{
    // Not on the board 
    if (getRow() == -1 || getColumn() == -1) { return false; } 
    // Out of bounds target
    if (target_row < 0 || target_row >= BOARD_LENGTH || target_col < 0 || target_col >= BOARD_LENGTH) { return false; };

    ChessPiece* target_piece = board[target_row][target_col];
    if (target_piece && target_piece->getColor() == getColor()) { return false; }

    // Get the difference between the current position and the target position
    int row_difference = target_row - getRow(); 
    // -,0,+  -->  represents down, no movement, up
    int col_difference = target_col - getColumn(); 

    // Same cell OR not a diagonal line
    bool stays_in_same_position = (row_difference == 0) && (col_difference == 0);
    bool moves_diagonal = (std::abs(row_difference) == std::abs(col_difference));;
    if (stays_in_same_position || !moves_diagonal) { return false; }

    // Find what direction we should step
    int increment_row = 0;
    int increment_col = 0;
    if (row_difference > 0) { increment_row = 1; }  // Moving up
    if (row_difference < 0) { increment_row = -1; } // Moving down

    if (col_difference > 0) { increment_col = 1; }  // Moving right
    if (col_difference < 0) { increment_col = -1; } // Moving left

    // Iterate from the original space to target space and check if there is any obstructing Chess Piece
    int temp_row = getRow();
    int temp_col = getColumn();

    while (temp_row != target_row || temp_col != target_col) {
        temp_row += increment_row;
        temp_col += increment_col;
        if (board[temp_row][temp_col]) { return false; }
    }

    return true;
}