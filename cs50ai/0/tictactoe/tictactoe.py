"""
Tic Tac Toe Player
"""

from copy import deepcopy
import math

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    x_turns, o_turns = 0, 0

    for row in board:
        if X in row:
            x_turns += row.count(X)

        if O in row:
            o_turns += row.count(O)

    return X if x_turns <= o_turns else O



def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    actions = set()

    for i, row in enumerate(board):
        if EMPTY in row:
            for j, col in enumerate(row):
                if col is EMPTY:
                    actions.add((i, j))

    return actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """

    updated_board = deepcopy(board)
    player_mark = player(updated_board)
    i, j = action
    

    if updated_board[i][j] is not EMPTY:
        raise Exception("Out of bounds.")
    else:
        updated_board[i][j] = player_mark

    return updated_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for i in range(3):
      # horizontal 
      if board[i][0] is not EMPTY and board[i][0] == board[i][1] == board[i][2]:
        return board[i][0]
      # vertical
      if board[0][i] is not EMPTY and board[0][i] == board[1][i] == board[2][i]:
        return board[0][i]

    # diagonal
    if board[1][1] is not EMPTY and (board[0][0] == board[1][1] == board [2][2] 
      or board[0][2] == board [1][1] == board[2][0]):
      return board[1][1]

    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) is not None:
      return True
    
    for i in range(3):
      for j in range(3):
        if board[i][j] == EMPTY:
          return False

    # board is full
    return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    the_winner = winner(board)

    if the_winner == X:
        return 1
    elif the_winner == O:
        return -1
    else:
        return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
      return None
    
    if player(board) == X:
      score = -math.inf
      opt_action = None

      for action in actions(board):
        min_value = minval(result(board, action))

        if min_value > score:
          score = min_value
          opt_action = action

      return opt_action

    elif player(board) == O:
      score = math.inf
      opt_action = None

      for action in actions(board):
        max_value = maxval(result(board, action))

        if max_value < score:
          score = max_value
          opt_action = action
      
      return opt_action

def maxval(board):
  if terminal(board):
    return utility(board)

  max_val = -math.inf

  for action in actions(board):
    max_val = max(max_val, minval(result(board, action)))
  
  return max_val

def minval(board):
  if terminal(board):
    return utility(board)

  min_val = math.inf

  for action in actions(board):
    min_val = min(min_val, maxval(result(board, action)))
  
  return min_val 

