def print_board(board):
    for row in board:
        print(" | ".join(row))
        print("-" * 5)

def check_winner(board, player):
    win_conditions = [
        [board[0][0], board[0][1], board[0][2]],
        [board[1][0], board[1][1], board[1][2]],
        [board[2][0], board[2][1], board[2][2]],
        [board[0][0], board[1][0], board[2][0]],
        [board[0][1], board[1][1], board[2][1]],
        [board[0][2], board[1][2], board[2][2]],
        [board[0][0], board[1][1], board[2][2]],
        [board[2][0], board[1][1], board[0][2]]
    ]
    return [player, player, player] in win_conditions

def get_valid_input(board):
    while True:
        try:
            row = int(input("Enter the row number (1-3): ")) - 1
            col = int(input("Enter the column number (1-3): ")) - 1
            if board[row][col] == ' ':
                return row, col
            else:
                print("This cell is already taken. Please try again.")
        except (IndexError, ValueError):
            print("Invalid input. Please enter numbers from 1 to 3.")

def tic_tac_toe():
    board = [[' ' for _ in range(3)] for _ in range(3)]
    players = ['X', 'O']
    turn = 0
    num_moves = 0

    while num_moves < 9:
        current_player = players[turn % 2]
        print(f"\nPlayer {current_player}'s turn:")
        print_board(board)

        row, col = get_valid_input(board)
        board[row][col] = current_player

        if check_winner(board, current_player):
            print_board(board)
            print(f"\nPlayer {current_player} wins!")
            break

        turn += 1
        num_moves += 1

    else:
        print_board(board)
        print("\nIt's a draw!")

if __name__ == "__main__":
    tic_tac_toe()
