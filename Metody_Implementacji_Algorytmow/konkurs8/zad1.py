
s = str(input())
w = 0

for letter in s:
    if int(letter) % 4 == 0:
        #print(letter)
        w = w+1

for i in range(1,len(s)):
    #print(10*int(s[i-1])+int(s[i]), int(10*int(s[i-1])+int(s[i]))%4)
    if int(10*int(s[i-1])+int(s[i])) % 4 == 0:     
        w = w+i

print(w)