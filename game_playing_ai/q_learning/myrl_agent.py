__author__ = "<your name>"
__organization__ = "COSC343/AIML402, University of Otago"
__email__ = "<your e-mail>"

import numpy as np
import pickle
import os

agentName = "<your agent name>"

# Example of a training specification - in this case it's two sessions,
# one 100 games against two opponents, value_agent and valueplus_agent,
# the other 50 games against random_agent and value_agent. 
training = [("value_agent.py", "valueplus_agent.py", 100000), ("random_agent.py", "value_agent.py", 0)]

# Name of the file to save the agent to.  If you want to retrain your agent
# delete that file.
save_filename="saved_myrl_agent.pkl"

class RajAgent():
   """
             A class that encapsulates the code dictating the
             behaviour of the agent playing the game of Raj.

             ...

             Attributes
             ----------
             item_values : list of ints
                 values of items to bid on
             card_values: list of ints
                 cards agent bids with

             Methods
             -------
             AgentFunction(percepts)
                 Returns the card value from hand to bid with
             """

   def __init__(self, item_values, card_values):
      """
      :param item_values: list of ints, values of items to bid on
      :card_values: list of ints, cards agent bids with
      """
      self.card_values = card_values
      self.item_values = item_values

      self.Q = dict()
      self.learning_rate = 0.1
      self.discount_factor = 0.9
      self.exploration_rate = 1.0
      self.game = 1

      self.transitions = []
      self.last_state = None
      self.last_action = None
      self.last_bank = None

   """ Load and save function for the agent.
      
       Currently, these load the object properties from a file 
       (all things that are stored in 'self').  You may modify
       them if you need to store more things.

       The load function is called by the engine if the save_file
       is found, the save function is called by the engine after
       the training (which is carried out only if the save file
       hasn't been found)
   """
   def load(self, filename):
        print(f'Loading trained {agentName} agent from {filename}...')
        f = open(filename, 'rb')
        tmp_dict = pickle.load(f)
        f.close()          
        self.__dict__.update(tmp_dict) 

   def save(self, filename):
        print(f'Saving trained {agentName} agent to {filename}...')
        f = open(filename, 'wb')
        pickle.dump(self.__dict__, f)
        f.close()
   
   def train_game_start(self):
       """ Invoked by the engine at the start of each game in training

           You may use it to initialise game-specific training variables 
           You may remove this method if you don't need it.
       """
       # Reset values before each game
       self.transitions = []
       self.last_bank = 0
       self.last_action = None
       self.last_state = None
       print("GAME: %d" % self.game)
       self.game = self.game + 1
       pass
      
   def train_game_end(self, banks):
        """ Invoked by the engine at the end of each game training,
            passing in the banks of all players

            Args: banks - a list of integers, the banks of all players at the end of the game
            
            You may remove this method if you don't need it.
        """
        # Add final state, action, reward group
        self.transitions.append((self.last_state, self.last_action, banks[0] - self.last_bank))
        terminal = True

        if(banks[0] != max(banks)):
            game_outcome = -1
        else:
            game_outcome = 1

        # Loop through each state-action pair used in reverse order
        for state, action, reward in reversed(self.transitions):
            index = state[1].index(action)
            if(game_outcome == -1):
                reward -= 1

            # Set the reward for the state-action pair
            if(terminal):
                self.Q[state][index] = reward
                terminal = False
            else:
                self.Q[state][index] = reward + self.learning_rate * (Q_star - reward)
            # Update reward for next state
            Q_star = reward + self.discount_factor * np.max(self.Q[state])
        # Epsilon decay
        self.exploration_rate *= 0.99999
        pass

   def AgentFunction(self, percepts):
      """Returns the bid value of the next bid

            :param percepts: a tuple of four items: bidding_on, items_left, my_cards, opponents_cards

                     , where

                     bidding_on - is an integer value of the item to bid on;

                     items_left - the items still to bid on after this bid (the length of the list is the number of
                                  bids left in the game)

                     my_cards - the list of cards in the agent's hand

                     bank - total value of items won by this agent in this game
                     
                     opponents_cards - a list of lists of cards in the opponents' hands, so in two player game, this is
                                      a list of one list of cards, in three player game, this is a list of two lists, etc.


            :return: value - card value to bid with, must be a number from my_cards
      """

      # Extract different parts of percepts.
      bidding_on = percepts[0]
      items_left = percepts[1]
      my_cards = percepts[2]
      bank = percepts[3]
      opponents_cards = percepts[4:]

      # Define each state
      state = (bidding_on, tuple(my_cards), tuple(map(tuple, opponents_cards)))

      # Set a base reward for each state and associated action
      if self.last_state is not None:
          self.transitions.append((self.last_state, self.last_action, bank - self.last_bank))

      # Add state to Q table, with actions, if not already added
      if state not in self.Q:
          self.Q[state] = np.zeros(len(my_cards))

      
      qvector = self.Q[state]

      p = qvector - np.min(qvector)
      p = np.exp(p/self.exploration_rate)
      p = p/np.sum(p)

      action = np.random.choice(my_cards, p=p)

      self.last_state = state
      self.last_action = action
      self.last_bank = bank
      # Return the bid
      return action
