from itertools import combinations
from collections import Counter

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

colors = [1,2,3,4]
low_kind = [2,3,4,5,6,7,8,9,10]
high_kind = [11,12,13,14]

low_cards = [(color,kind) for color in colors for kind in low_kind]
high_cards = [(color,kind) for color in colors for kind in high_kind]

low_hands = [list(hand) for hand in combinations(low_cards, 5)]
high_hands = [list(hand) for hand in combinations(high_cards, 5)]

# how many hands of certain val they have (1 is straight flush ...)
lows = [0] * 9 # [20, 288, 1728, 484, 5100, 16128, 36288, 193536, 123420]
highs = [0] * 9 # [0, 48, 288, 0, 0, 768, 1728, 1536, 0]
for hand in low_hands:
    lows[ReckognizeCombo(hand) - 1] += 1
for hand in high_hands:
    highs[ReckognizeCombo(hand) - 1] += 1

lows_better = 0
for i in range(9):
    lows_better += lows[i] * sum(highs[(i+1):9])
    print(lows[i], sum(highs[(i+1):9]))

# print(len(low_hands))
# print(len(high_hands))
print(lows_better / (len(low_hands) * len(high_hands)) * 100, "%")