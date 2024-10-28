#!/usr/bin/env python3

from DataPage import DataPage

myint_array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

dpage = DataPage[int](4)
dpage.addwhole(myint_array)

for page in dpage:
    print(page)
    
my_dict_array = [
    { "id" : "001", "name" : "python"},
    { "id" : "002", "name" : "rust" },
    { "id" : "003", "name" : "c" },
    { "id" : "004", "name" : "c++" },
    { "id" : "005", "name" : "java" },
    { "id" : "006", "name" : "go" },
    { "id" : "007", "name" : "c#" },
    { "id" : "008", "name" : "vb" }
]

#dpage = DataPage[dict](3)
#dpage.addwhole(my_dict_array)
#dpage.append({ "id" : "009", "name" : "java script" })
#dpage.append({ "id" : "010", "name" : "perl" })
#

dpage.set_pagesize(5)
for page in dpage:
    print(page)