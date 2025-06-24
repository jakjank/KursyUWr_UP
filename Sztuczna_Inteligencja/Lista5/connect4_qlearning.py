from random import choice, random

import numpy as np

class Connect4:
    COLS_NUM = 7
    ROWS_NUM = 6

    ALPHA = 0.001
    GAMMA = 0.95
    EPSILON_DECAY = 0.995

    FEATURE_COUNT = 7
    
    # Features:
    # 1: Number of 2 pieces in a row for player
    # 2: Number of 3 pieces in a row for player
    # 3: Number of center column pieces for player
    # 4: Number of 2 pieces in a row for opponent
    # 5: Number of 3 pieces in a row for opponent
    # 6: Number of 2 extendable pieces in a row for player
    # 7: Number of 2 extendable pieces in a row for opponent

    def __init__(self, epsilon: float = 1):
        self.board = [[None] * self.COLS_NUM for _ in range(self.ROWS_NUM)]
        self.epsilon = epsilon
        self.weights = np.zeros(self.FEATURE_COUNT)
        self.history = []

    def move(self, col: int, player: int):
        for row in range(0, self.ROWS_NUM):
            if self.board[row][col] is None:
                self.board[row][col] = player
                return row, col
        raise ValueError("Column is full")

    def is_terminal(self) -> int | None:
        for row in range(self.ROWS_NUM):
            for col in range(self.COLS_NUM):
                player = self.board[row][col]
                if player is None:
                    continue
                # horizontal →
                if col <= self.COLS_NUM - 4:
                    if all(self.board[row][col + i] == player for i in range(4)):
                        return player
                # vertical ↓
                if row <= self.ROWS_NUM - 4:
                    if all(self.board[row + i][col] == player for i in range(4)):
                        return player
                # left diagonal ↘
                if row <= self.ROWS_NUM - 4 and col <= self.COLS_NUM - 4:
                    if all(self.board[row + i][col + i] == player for i in range(4)):
                        return player
                # right diagonal ↗
                if row >= 3 and col <= self.COLS_NUM - 4:
                    if all(self.board[row - i][col + i] == player for i in range(4)):
                        return player
        # draw
        if all(cell is not None for row in self.board for cell in row):
            return -1
        return None

    def print_board(self):
        symbols = {None: ".", 0: "X", 1: "O"}
        for row in reversed(self.board):
            print(" ".join(symbols[cell] for cell in row))
        print("0 1 2 3 4 5 6\n")

    def all_possible_moves(self):
        return [col for col in range(self.COLS_NUM)
                if self.board[self.ROWS_NUM - 1][col] is None]

    def reset_game(self):
        self.board = [[None] * self.COLS_NUM for _ in range(self.ROWS_NUM)]
        self.history = []
        self.epsilon *= self.EPSILON_DECAY  # decay after every episode

    def random_agent_move(self, player: int):
        valid_cols = self.all_possible_moves()
        self.move(choice(valid_cols), player)
    
    def extract_features(self, player: int):
        features = np.zeros(self.FEATURE_COUNT)
        
        player_2_in_row = 0
        player_3_in_row = 0
        opponent_2_in_row = 0
        opponent_3_in_row = 0
        player_center = 0
        
        opponent = 1 - player
        
        # Count center column pieces for player
        center_col = self.COLS_NUM // 2
        for row in range(self.ROWS_NUM):
            if self.board[row][center_col] == player:
                player_center += 1
                
        # Check horizontal, vertical, and diagonal lines
        # Horizontal
        for row in range(self.ROWS_NUM):
            for col in range(self.COLS_NUM - 1):
                # Check for player's 2 in a row
                if col <= self.COLS_NUM - 2:
                    if all(self.board[row][col + i] == player for i in range(2)):
                        player_2_in_row += 1
                # Check for player's 3 in a row
                if col <= self.COLS_NUM - 3:
                    if all(self.board[row][col + i] == player for i in range(3)):
                        player_3_in_row += 1
                # Check for opponent's 2 in a row
                if col <= self.COLS_NUM - 2:
                    if all(self.board[row][col + i] == opponent for i in range(2)):
                        opponent_2_in_row += 1
                # Check for opponent's 3 in a row
                if col <= self.COLS_NUM - 3:
                    if all(self.board[row][col + i] == opponent for i in range(3)):
                        opponent_3_in_row += 1
        
        # Vertical
        for col in range(self.COLS_NUM):
            for row in range(self.ROWS_NUM - 1):
                # Check for player's 2 in a row
                if row <= self.ROWS_NUM - 2:
                    if all(self.board[row + i][col] == player for i in range(2)):
                        player_2_in_row += 1
                # Check for player's 3 in a row
                if row <= self.ROWS_NUM - 3:
                    if all(self.board[row + i][col] == player for i in range(3)):
                        player_3_in_row += 1
                # Check for opponent's 2 in a row
                if row <= self.ROWS_NUM - 2:
                    if all(self.board[row + i][col] == opponent for i in range(2)):
                        opponent_2_in_row += 1
                # Check for opponent's 3 in a row
                if row <= self.ROWS_NUM - 3:
                    if all(self.board[row + i][col] == opponent for i in range(3)):
                        opponent_3_in_row += 1

        # Extendable 2s 
        player_2_ext_in_row = 0
        opponent_2_ext_in_row = 0

        for row in range(self.ROWS_NUM):
            for col in range(self.COLS_NUM):
                # Horizontal
                if col <= self.COLS_NUM - 2:
                    # Player
                    if self.board[row][col] == player and self.board[row][col + 1] == player:
                        left_open = col > 0 and self.board[row][col - 1] is None
                        right_open = col + 2 < self.COLS_NUM and self.board[row][col + 2] is None
                        if left_open or right_open:
                            player_2_ext_in_row += 1
                    # Opponent
                    if self.board[row][col] == opponent and self.board[row][col + 1] == opponent:
                        left_open = col > 0 and self.board[row][col - 1] is None
                        right_open = col + 2 < self.COLS_NUM and self.board[row][col + 2] is None
                        if left_open or right_open:
                            opponent_2_ext_in_row += 1

                # Vertical
                if row <= self.ROWS_NUM - 2:
                    # Player
                    if self.board[row][col] == player and self.board[row + 1][col] == player:
                        above_open = row > 0 and self.board[row - 1][col] is None
                        below_open = row + 2 < self.ROWS_NUM and self.board[row + 2][col] is None
                        if above_open or below_open:
                            player_2_ext_in_row += 1
                    # Opponent
                    if self.board[row][col] == opponent and self.board[row + 1][col] == opponent:
                        above_open = row > 0 and self.board[row - 1][col] is None
                        below_open = row + 2 < self.ROWS_NUM and self.board[row + 2][col] is None
                        if above_open or below_open:
                            opponent_2_ext_in_row += 1

                # Diagonal (/)
                if row >= 1 and col <= self.COLS_NUM - 2:
                    # Player
                    if self.board[row][col] == player and self.board[row - 1][col + 1] == player:
                        upper_right = row - 2 >= 0 and col + 2 < self.COLS_NUM and self.board[row - 2][col + 2] is None
                        lower_left = row + 1 < self.ROWS_NUM and col - 1 >= 0 and self.board[row + 1][col - 1] is None
                        if upper_right or lower_left:
                            player_2_ext_in_row += 1
                    # Opponent
                    if self.board[row][col] == opponent and self.board[row - 1][col + 1] == opponent:
                        upper_right = row - 2 >= 0 and col + 2 < self.COLS_NUM and self.board[row - 2][col + 2] is None
                        lower_left = row + 1 < self.ROWS_NUM and col - 1 >= 0 and self.board[row + 1][col - 1] is None
                        if upper_right or lower_left:
                            opponent_2_ext_in_row += 1

                # Anti-diagonal (\)
                if row <= self.ROWS_NUM - 2 and col <= self.COLS_NUM - 2:
                    # Player
                    if self.board[row][col] == player and self.board[row + 1][col + 1] == player:
                        lower_right = row + 2 < self.ROWS_NUM and col + 2 < self.COLS_NUM and self.board[row + 2][col + 2] is None
                        upper_left = row - 1 >= 0 and col - 1 >= 0 and self.board[row - 1][col - 1] is None
                        if lower_right or upper_left:
                            player_2_ext_in_row += 1
                    # Opponent
                    if self.board[row][col] == opponent and self.board[row + 1][col + 1] == opponent:
                        lower_right = row + 2 < self.ROWS_NUM and col + 2 < self.COLS_NUM and self.board[row + 2][col + 2] is None
                        upper_left = row - 1 >= 0 and col - 1 >= 0 and self.board[row - 1][col - 1] is None
                        if lower_right or upper_left:
                            opponent_2_ext_in_row += 1
        
        features[0] = player_2_in_row
        features[1] = player_3_in_row
        features[2] = player_center
        features[3] = opponent_2_in_row
        features[4] = opponent_3_in_row
        features[5] = player_2_ext_in_row
        features[6] = opponent_2_ext_in_row
        
        return features
    
    def calculate_value(self, features):
        return np.dot(self.weights[1:], features[1:])

    def td_agent_move(self, player: int):
        current_features = self.extract_features(player)
        
        possible_moves = self.all_possible_moves()
        if random() < self.epsilon:
            chosen_col = choice(possible_moves)
        else:
            best_value = -float('inf')
            best_move = None
            for col in possible_moves:
                row, _ = self.move(col, player)

                next_features = self.extract_features(player)
                value = self.calculate_value(next_features)
                
                self.board[row][col] = None

                if value > best_value:
                    best_value = value
                    best_move = col
            chosen_col = best_move if best_move is not None else choice(possible_moves)
        
        row, col = self.move(chosen_col, player)
        self.history.append(current_features)

    def update_weights(self, reward: float):
        target = 0
        
        for features in reversed(self.history):
            current_value = self.calculate_value(features)
            
            td_error = reward + target - current_value
            update = self.ALPHA * td_error * features

            update = np.clip(update, -1.0, 1.0)
            self.weights += update

            target = self.calculate_value(features) * self.GAMMA

if __name__ == "__main__":
    game = Connect4()

    td_player = 0
    random_player = 1

    td_wins = 0
    for i in range(1, 5001):
        turn = 0
        while game.is_terminal() is None:
            if turn%2 == 0:
                game.td_agent_move(td_player)
            else:
                game.random_agent_move(random_player)
            # game.print_board()
            turn += 1
            # if turn == 30:
            #     game.print_board()
            #     print(game.extract_features(0))

        rew = game.is_terminal()
        if rew == td_player:
        #     game.update_weights(1.0)
            td_wins += 1
        #     # print(f"Player {td_player} wins")
        # elif rew == random_player:
        #     game.update_weights(-1.0)
        #     # print(f"Player {random_player} wins")
        # else:
        #     game.update_weights(0.0)
        #     # print(f"DRAW")

        if i % 100 == 0:
            print(f"After {i} games, TD agent won {td_wins} times in last 100 games ({(td_wins / 100) * 100:.1f}%)")
            # print(f"Current weights: {game.weights}")
            game.update_weights(td_wins / 100.0)
            td_wins = 0

        game.reset_game()