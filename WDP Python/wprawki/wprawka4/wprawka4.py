a=0
m=0
for e in open("j.txt").readlines():
 if e!='\n':
  a+=int(e[0:len(e)-1])
 else:
  if a>m:
   m=a
a=0
print(m)