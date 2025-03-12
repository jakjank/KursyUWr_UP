# How
# We get randomly two sets of 5 cards (low and high)
# and then compare who won (ifology)

import random
from collections import Counter

# Card is a tuple (a,b)
# a e [1-4] - kind (suits)
# b e [2-14] - val (kind) :))

def getLowCard():
    while(True):
        val = random.randint(2,10)
        kind = random.randint(1,4)
        card = (kind,val)
        if card not in lowCards:
            return card

def getLowCardPrim(min_val):
    while(True):
        val = random.randint(min_val,10)
        kind = random.randint(1,4)
        card = (kind,val)
        if card not in lowCards:
            return card

def getHighCard():
    while(True):
        val = random.randint(11,14)
        kind = random.randint(1,4)
        card = (kind,val)
        if card not in highCards:
            return card

def ReckognizeCombo(cards):
    cards.sort(key=lambda x: x[1])
    # print("-------------",cards)
    if (all(cards[i][1] + 1 == cards[i+1][1] for i in range(4)) and
        all(cards[i][0] == cards[i+1][0] for i in range(4))):
        return 1 # straight flush
    if (all(cards[i][1] == cards[i+1][1] for i in range(3)) or
        all(cards[i][1] == cards[i+1][1] for i in range(1,4))):
        return 2 #4 of kind
    if ((all(cards[i][1] == cards[i+1][1] for i in range(2)) and cards[3][1] == cards[4][1]) or
        (all(cards[i][1] == cards[i+1][1] for i in range(2,4)) and cards[0][1] == cards[1][1])):
        # print(all(cards[i][1] == cards[i+1][1] for i in range(2)),
        #     cards[3][1] == cards[4][1],
        #     all(cards[i][1] == cards[i+1][1] for i in range(2,3)),
        #     cards[0][1] == cards[1][1]
        # )
        return 3 #full house
    if all(cards[i][0] == cards[i+1][0] for i in range(4)):
        return 4 # flush
    if all(cards[i][1] + 1 == cards[i+1][1] for i in range(4)):
        return 5 # straight
    if (all(cards[i][1] == cards[i+1][1] for i in range(2)) or
        all(cards[i][1] == cards[i+1][1] for i in range(1,3)) or
        all(cards[i][1] == cards[i+1][1] for i in range(2,4))):
        return 6 # 3 of kind
    count_b = Counter(b for _, b in cards)
    pairs = [b for b, count in count_b.items() if count == 2]
    if len(pairs) == 2:
        return 7 # two pairs
    if len(pairs) == 1:
        return 8 # one pair
    return 9 # high card

myMap = {
    1:"straight flush",
    2:"4 of kind",
    3:"full house",
    4:"flush",
    5:"straight",
    6:"3 of kind",
    7:"two pairs",
    8:"one pair",
    9:"high card"
    }

# Tests
# print(ReckognizeCombo([(2,2),(2,3),(2,4),(2,5),(2,6)]))
# print(ReckognizeCombo([(2,2),(3,2),(1,2),(4,2),(2,6)]))
# print(ReckognizeCombo([(2,2),(3,2),(1,2),(4,6),(2,6)]))
# print(ReckognizeCombo([(2,2),(2,7),(2,4),(2,5),(2,6)]))
# print(ReckognizeCombo([(2,2),(2,3),(3,4),(2,5),(2,6)]))
# print(ReckognizeCombo([(2,2),(3,2),(4,2),(2,5),(2,6)]))
# print(ReckognizeCombo([(2,2),(3,2),(4,8),(2,5),(3,5)]))
# print(ReckognizeCombo([(2,2),(3,1),(4,8),(2,5),(3,5)]))
# print(ReckognizeCombo([(2,2),(3,1),(4,8),(2,5),(3,7)]))
# print(ReckognizeCombo([(2, 5), (3, 5), (3, 7), (1, 7), (4, 8)]))

# possible combos
# high four of kind is always better than low one,
# high full house is ...
# high                | low
#--------------------------------------
#                     | straight flush 1
# four of kind        |                2 
#                     | four  of kind  
# full house          |                3
#                     | full house
#                     | flush          4
#                     | straight       5
# 3 of a kind(suits)  |                6
#                     | 3 of kind        
# two pair            |                7
#                     | two pair
# one pair            |                8
#                     | one pair       9
#                     | high card      10

# returns true if high won and false if left won
def wining_set(high,low):
    if(ReckognizeCombo(high) <= ReckognizeCombo(low)): return True
    return False

no_tries = 10_000
no_hw = 0
no_lw = 0
for i in range(no_tries):
    highCards = []
    lowCards = []
    for i  in range(5):
        highCards.append(getHighCard())
        lowCards.append(getLowCard())

    if wining_set(highCards,lowCards):
        no_hw += 1
    else:
        no_lw += 1
        # print(highCards,"-",myMap[ReckognizeCombo(highCards)], lowCards,"-",myMap[ReckognizeCombo(lowCards)])

# for 1_000_000 was 8.41%
#print(f"Low cards have {(no_lw / no_tries)*100}% chances to win agains high cards")

# throwing cards away idea 
# lower cards are worse then high ones 
# we wont be taking {2s}, {2s,3s}, ... to our deck
# we need to leave at least 9s (or at least one 9) and 10s

for min_val in range(2,10):
    no_tries = 10_000
    no_hw = 0
    no_lw = 0
    for i in range(no_tries):
        highCards = []
        lowCards = []
        for i  in range(5):
            highCards.append(getHighCard())
            lowCards.append(getLowCardPrim(min_val))

        if wining_set(highCards,lowCards):
            no_hw += 1
        else:
            no_lw += 1
    print(f"Min val: {min_val}; low's chances {(no_lw / no_tries)*100}%")

# so low has over 50% (firs time) chances of win if
# his deck is {8s,9s,10s}

# so the biggest possible deck would be {8s,9s,10s} + some of 7s