# How


import random


# Card is a tuple (a,b)
# a e [1-4] - kind (suits)
# b e [2-14] - val (kind) :))


highCards = []
lowCards = []

def getLowCard():
    while(True):
        val = random.randint(2,10)
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

for i  in range(0,5):
    highCards.append(getHighCard())
    lowCards.append(getLowCard())

print(highCards)

def ReckognizeCombo(cards):
    cards.sort(key=lambda x: x[1])
    
    # return cards
    

# possible combos
# high four of kind is always better than low one,
# high full house is ...
# high                | low
#--------------------------------------
#                     | straight flush
# four of kind        |
#                     | four  of kind
# full house          |
#                     | full house
#                     | flush
#                     | straight
# 3 of a kind(suits)  |
#                     | 3 of kind
# two pair            |
#                     | two pair
# one pair            |
#                     | one pair
#                     | high card
def wining_set(high,low):
    pass

print(ReckognizeCombo(highCards))