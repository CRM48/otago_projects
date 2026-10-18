# Game Playing AI

Two Python AI agents developed for COSC343 at the University of Otago, using search-based decision-making and reinforcement learning to play the Raj bidding game.

## Overview

- **Search Agent:** Evaluates possible bidding combinations and their expected payoffs to select moves.
- **Q-Learning Agent:** Uses reinforcement learning to develop a bidding strategy through repeated games, storing learned values in a Q-table.

Both agents compete against other strategies in the Raj game environment.

## Key Concepts

- Game-tree search and decision-making
- Reinforcement learning and Q-learning
- Reward-based strategy development
- Exploration and exploitation
- Evaluating AI agents against baseline strategies

## Running

Requires Python 3 and NumPy.

Install NumPy:

```bash
pip install numpy
```

Run the search agent:

```bash
cd search_agent
python raj.py
```

Run the Q-learning agent:

```bash
cd q_learning
python raj.py
```

The Q-learning agent uses a saved Q-table (`saved_myrl_agent.pkl`).

## Testing

From the main project directory:

```bash
python tests.py
```

The tests check that both agents generate valid moves and that the saved Q-learning model loads correctly.