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
/**
 * @brief Determines whether the Bishop can move to the specified target position on the board.
 * @pre The row & col members of the Bishop object match its actual position on the passed board object.
 * 
 * The Bishop's movement follows these rules:
 * 1. The Bishop may move any number of squares diagonally from its current position
 * 2. The path to the target square must be unobstructed by (ie. contain) other pieces, 
 *      except for the target square itself.
 * 3. The target square must either be empty (moving) or contain a piece of another color (capturing)
 * 4. The target square must stay within the board's bounds, ie. not outside [0, BOARD_LENGTH)
 * 5. The Bishop cannot move to its currently occupied position (i.e. it can't stand still).
 * 
 * @param target_row An integer representing the row index of the target square on the board.
 * @param target_col An integer representing the column index of the target square on the board.
 * @param board A 2D vector representing the current board state, 
 *              where each cell points to a ChessPiece object or is null.
 * 
 * @return True if the Bishop can move to the specified position; false otherwise.
 */

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
    bool moves_diagonal = (std::abs(row_difference) == std::abs(col_difference));
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