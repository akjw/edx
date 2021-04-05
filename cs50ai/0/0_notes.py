"""
Search problems
- Initial state
- Actions
- Transition model
- Goal Test
- Path cost function

Use a node to keep track of:
- a state
- a parent (node that preceded this one)
- an action (that transformed previous state to this one)
- path cost (from initial state to node)

Approach
-- the frontier: all possibilities that could be explored
-- start with frontier that contains initial state
-- repeat:
    - if frontier is empty, then no solution
    - remove node from frontier
    - if node contains goal state, return the solution
    - otherwise, expand node (i.e. look at the neighbors of the node), add resulting nodes to the frontier

Potential problems
-- get stuck in infinite loop if bidirectional travel between nodes is possible

Revised solution
-- add explored set category
-- add explored nodes to explored set
-- only expand to nodes that have not been explored 

How to choose between nodes
STACK: last in first out (depth-first search)
-- always expands the deepest node in the frontier
-- might end up finding a non-optimal solution

QUEUE: first in first out (breadth-first search)
-- always expands the shallowest node in the frontier
-- explores all paths at the same time, bouncing between them

Uninformed search
-- search strategy that uses no problem-specific knowledge

Informed search
-- search strategy that uses problem-specific knowledge to find solutions more efficiently
  - greedy best-first search: expands node that it thinks is closest to the goal, as estimated by a heuristic function h(n)
    - Manhattan distance (calculating for each node how many steps away from goal)
    - but only considers best solution locally; can miss big picture
  
  - A* search: search algorithm that expands node with lowest value of g(n) + h (n)
    - g(n) = cost to reach node; h(n) = estimated cost to goal
    - optimal if 
      1) h(n) is admissible (never overestimates true cost)
      2) h(n) is consistent ( for every node n & successor n' with step cost c, h(n) <= h(n') + c)
  
Adverserial search
  - eg. tic-tac-toe

Minimax algorithm
  - -1 (o wins), 0 (draw), 1 (x wins)
  - max (x) aims to maximize score
  - min (o) aims to minimize score

    function MAX-VALUE(state):
      if TERMINAL(state):
        return UTILITY(state)
      v = -infinity
      for action in ACTIONS(state):
        v = MAX(v, MIN-VALUE(RESULT(state, action)))
      return v

    function MIN-VALUE(state):
      if TERMINAL(state):
        return UTILITY(state)
      v = infinity
      for action in ACTIONS(state):
        v = MIN(v, MAX-VALUE(RESULT(state, action)))
      return v
Game
- S: initial state
- Player(s): returns which player to move in state s
- Action(s): returns legal moves in state s
- Result(s, a): returns state after action a taken in state s
- Terminal(s): checks if state s is a terminal state
- Utility(s): final numerical state for terminal state s

Alpha-Beta Pruning

Depth-limited minimax
  - after a certain number of moves, stop considering moves after that
  - evaluation function: estimates expected utility of game from a given state

"""




  

