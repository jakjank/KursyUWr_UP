import random
import numpy as np
from board import *

class QLearner:
    def __init__(self, me):
        self.me = me
        self.weights = {
            "figures_sum_diff" : 0,
            "sum_distance_diff" : 0,
            "captured_piece_value" : 0,
            "closest_piece_diff" : 0
        }
        self.epsilon = 1
        self.epsilon_decay = 0.99
        self.history = []
        self.alpha = 0.001
        self.gamma = 0.99

    def figures_sum_diff(self, board : Board):
        return (sum(i for i in range(1,9) if board.players_board(self.me)[i-1] != (-1,-1)) -
                sum(i for i in range(1,9) if board.ops_board(self.me)[i-1] != (-1,-1)))

    def distance(self, posA, posB):
        return abs(posA[0] - posB[0]) + abs(posA[1] - posB[1])

    def sum_distance_diff(self, board : Board):
        my_sum = sum([self.distance(piece, board.my_goto_hole(self.me)) for piece in board.players_board(self.me) if piece != (-1,-1)])
        opp_sum = sum([self.distance(piece, board.my_goto_hole((self.me+1)%2)) for piece in board.players_board(self.me) if piece != (-1,-1)])
        return my_sum - opp_sum

    def closests_diff(self, board : Board):
        my_sum = min([self.distance(piece, board.my_goto_hole(self.me)) for piece in board.players_board(self.me) if piece != (-1,-1)])
        opp_sum = min([self.distance(piece, board.my_goto_hole((self.me+1)%2)) for piece in board.players_board(self.me) if piece != (-1,-1)])
        return my_sum - opp_sum


    def dot_product(self, features : dict[str, float]):
        return sum(self.weights[k] * features.get(k, 0.0) for k in self.weights)

    # quality of state and move
    def extract_features(self, move_data, board):
        figs = round(self.figures_sum_diff(board) / 8.0 , 5)
        dists = round(self.sum_distance_diff(board) / 100.0 , 5)
        captured = round(move_data["captured"] / 8.0 , 5)
        closests = round(self.closests_diff(board) / 8.0 , 5)
        return {
            "figures_sum_diff": figs,
            "sum_distance_diff": dists,
            "captured_piece_value": captured,
            "closest_piece_diff": closests
        }
    def update_weights(self, features, reward, next_features):
        current_q = self.dot_product(features)
        next_q = self.dot_product(next_features) if next_features is not None else 0
        td_error = reward + self.gamma * next_q - current_q

        # Q = Q + alpha * (reward + gamma * next_q - current_q) po pojedynczych featureach
        for k in self.weights:
            self.weights[k] += self.alpha * td_error * features.get(k, 0.0)
            self.weights[k] = round(self.weights[k], 5)


    def update(self, final_reward, move_history):
        next_features = None  # Brak następnego stanu po ostatnim ruchu

        for old_board, move, p in reversed(move_history):
            if p != self.me:
                continue

            board_copy = copy.deepcopy(old_board)
            move_data = board_copy.move((move[0], move[1]), (move[2], move[3]), self.me)
            features = self.extract_features(move_data, board_copy)

            # reward to final_reward tylko dla ostatniego kroku
            reward = final_reward if next_features is None else 0  

            self.update_weights(features, reward, next_features)

            next_features = features  # dla poprzedniego kroku to będzie następny stan



    def get_move(self, board : Board):
        self.epsilon *= self.epsilon_decay
        self.epsilon = max(0.05, self.epsilon)

        moves = board.get_possible_moves(self.me)
        if len(moves) == 0:
            return (-1,-1,-1,-1)
        
        r = random.random()
        if r  < self.epsilon:
            return random.choice(moves)

        best_move = (-1,-1,-1,-1)
        best_value = float('-inf')

        for sx, sy, ex, ey in moves:
            board_copy = copy.deepcopy(board) # or add undo method to board
            move_data = board_copy.move((sx,sy), (ex,ey), self.me)
            features = self.extract_features(move_data, board_copy)
            value = self.dot_product(features)
            if value > best_value:
                best_move = (sx,sy,ex,ey)
                best_value = value

        self.history.append((best_move,self.me))
        return best_move



