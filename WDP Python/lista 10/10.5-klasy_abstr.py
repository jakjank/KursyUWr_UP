def rel_rown(S):
    print(S)
    if len(S) == 1:
        return [[S]]
    
    tmp = list(S)
    t = rel_rown(set(tmp[1:]))
    
    tmp2 = []
    for podzial in t:
        for zbior in podzial:
            if len(podzial) > 1:
                tmp3 = [*podzial]
                tmp3.remove(zbior)
                zbior = zbior | set([tmp[0]])
                tmp3 = tmp3 + [zbior]
                tmp2.append(tmp3)
            else:
                podzial = [zbior | set([tmp[0]])]
                tmp2.append(podzial)
            

    return tmp2 + [[set([tmp[0]])] + x for x in t]
    
    
#[[set([tmp[0]]) | x] for k in t for x in k]

print(rel_rown(set([1,2,3])))
