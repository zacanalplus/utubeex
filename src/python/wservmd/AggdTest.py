#!/usr/bin/env python3

from AggData import AggData 

myarr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
myarr2 = [{"name" : "AA"}, {"name" : "BB"},{"name" : "GG"}, {"name" : "DD"},{"name" : "EE"}, {"name" : "FF"}]

dpage = AggData[dict](4)
dpage.addwhole(myarr2)
dpage.append({"name" : "HH"})

for pg in dpage:
    print(pg)
    
dpage = AggData[int](5)
dpage.addwhole(myarr)

for pg in dpage:
    print(pg)
    #print(dpage.to_dictionary())
    
for pg in dpage:
    print(pg)