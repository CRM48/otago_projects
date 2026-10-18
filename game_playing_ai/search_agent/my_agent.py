__author__ = "<your name>"
__organization__ = "COSC343/AIML402, University of Otago"
__email__ = "<your e-mail>"

import numpy as np
import itertools

agentName = "<your agent name>"

class RajAgent():

   def __init__(self, item_values, card_values):
      self.card_values = card_values
      self.item_values = item_values



   def AgentFunction(self, percepts):
      # Extract different parts of percepts.
      bidding_on = percepts[0]
      items_left = percepts[1]
      my_cards = percepts[2]
      bank = percepts[3]
      opponents_cards = percepts[4]

      # Create an empty matrix of the right size
      int_matrix = np.zeros((len(my_cards), len(opponents_cards)))

      # Fill that matrix with their expected values
      payoff_matrix = self.genPayoffMatrix(bidding_on, items_left, my_cards, opponents_cards, int_matrix)
      
      # Use the matrix to calculate the optimal bet
      best_bid_loc = self.maximax(payoff_matrix)

      # Return the bid
      return my_cards[best_bid_loc]
   
   def computePermutations(self, remaining_values, remaining_bets_p1, remaining_bets_p2):
    # Compute the permutations for the three lists using np
    all_value_orders = np.array(list(itertools.permutations(remaining_values)))
    all_bet_pairs_p1 = np.array(list(itertools.permutations(remaining_bets_p1)))
    all_bet_pairs_p2 = np.array(list(itertools.permutations(remaining_bets_p2)))
    return all_value_orders, all_bet_pairs_p1, all_bet_pairs_p2
   
   def genPayoffMatrix(self, bidding_on, items_left, my_cards, opponents_cards, matrix):
      # Loop through all possible bets, creating a matrix of values for each pair
      for i in range(len(my_cards)):
         temp_my_cards = my_cards[:i] + my_cards[i+1:]
         for j in range(len(opponents_cards)):
            temp_opp_cards = opponents_cards[:j] + opponents_cards[j+1:]
            matrix[i][j] = self.genPayoffValue(bidding_on, my_cards[i], opponents_cards[j], temp_my_cards, temp_opp_cards, items_left)

      return matrix
   
   def genPayoffValue(self, bidding_on, my_init_bet, opp_init_bet, my_rem_cards, opp_rem_cards, rem_vals):
      my_score = 0
      opp_score = 0
      rem = 0

      # Generate scores from initial bets
      if(my_init_bet > opp_init_bet):
         my_score += bidding_on
      elif(opp_init_bet > my_init_bet):
         opp_score += bidding_on
      else:
         rem = bidding_on

      # Generate permutations
      all_val_orders, all_my_bets_orders, all_opp_bets_order = self.computePermutations(rem_vals, my_rem_cards, opp_rem_cards)

      # Ajust list dimensions for broadcasting
      all_val_orders = all_val_orders[:, np.newaxis, :]
      all_my_bets_orders = all_my_bets_orders[np.newaxis, :, :]
      all_opp_bets_order = all_opp_bets_order[np.newaxis, :, :]

      # In case of tie, add remainder to all first values
      if rem > 0:
         all_val_orders[:, :, 0] += rem

      # Calculate all wins and ties
      my_wins = all_my_bets_orders > all_opp_bets_order
      opp_wins = all_opp_bets_order > all_my_bets_orders
      ties = all_my_bets_orders == all_opp_bets_order
      
      # Ties functionality wasn't working due to different broadcasts
      """
      # If ties, add to following value
      if(ties.any()):
         tie_values = np.roll(all_val_orders, -1, axis=2)*ties
         all_val_orders += tie_values
         # If tie at end of game, don't add so subtract from all first values
         all_val_orders[:, :, -1] -= tie_values[:, :, 0]
      """

      # Calculate scores
      all_my_scores = np.sum(my_wins * all_val_orders, axis=-1)
      all_opp_scores = np.sum(opp_wins * all_val_orders, axis=-1)
      all_my_scores += my_score
      all_opp_scores += opp_score

      net_scores = all_my_scores - all_opp_scores

      return np.mean(net_scores)

   def minimax(self, matrix):
      min_val = float('inf')
      max_val = float('-inf')
      sum = 0
      min_col = None
      max_row = None

      # Find the lowest value column
      for i in range(len(matrix)):
         for j in range(len(matrix[i])):
            sum += matrix[j][i]
         if(sum < min_val):
            min_val = sum
            min_col = i
         sum = 0

      # Find the highest value in that column
      for i in range(len(matrix[min_col])):
         if matrix[i][min_col] > max_val:
            max_val = matrix[i][min_col]
            max_row = i
      return max_row
   
   def maximax(self, matrix):
      max_sum = float('-inf')
      sum = 0

      # Find the highest value row
      for i in range(len(matrix)):
         for j in range(len(matrix[i])):
            sum += matrix[i][j]
         if(sum > max_sum):
            max_sum = sum
            max_row = i
         sum = 0
      return max_row

      





      