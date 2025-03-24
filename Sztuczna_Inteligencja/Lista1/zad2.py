# How?
# we have dp[] size n with dp[i] equal max score of 'division' of the text up to ith letter
# if we want to find val of dp[i] (we have all dp[j] for j<i)
# we check every word text[j:i] for j<i
# and if word is valid and dp[j] > -1 (no letter gaps)
# we check if this score is bigger than current one at dp[i]
# we also remember start of the word for every position to retrive the words after we finish

def add_spaces(text, words):
    # val at ith pos in dp is the max possible 'score' for first i letters
    n = len(text)
    dp = [-1] * (n+1)
    dp[0] = 0
    # for restoring the words
    prev = [-1] * (n+1)
    result = ""

    for i in range(1, n+1):
        for j in range(i):
            word = text[j:i]
            if word in words and dp[j] != -1:
                score = dp[j] + len(word) ** 2
                if score > dp[i]:
                    dp[i] = score
                    prev[i] = j
    
    i = n
    #print("&",text)
    while i > 0:
        #print(i,text[prev[i]:i])
        result = text[prev[i]:i] + " " + result
        # if prev[i] == -1:
        #     print(f"-1 from {i}")
        i = prev[i]
    #print("#",result.strip())
    
    return result.strip()

def solve(input, output, words_file):
    with open(input,'r',encoding="utf-8") as f:
        lines = [line.strip() for line in f.readlines()]
    
    words = set()
    with open(words_file,'r',encoding="utf-8") as f:
        words.update([line.strip() for line in f.readlines()])

    result = []
    for line in lines:
        result.append(add_spaces(line,words) + '\n')

    with open(output,'w',encoding="utf-8") as f:
        for line in result:
            f.write(line)

if __name__ == "__main__":
    solve("zad2_input.txt", "zad2_output.txt", "words_for_ai1.txt")