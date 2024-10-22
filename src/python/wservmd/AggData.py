# AggData.py
# Created by Zarni Aung on 8/30/24.


from typing import TypeVar, Generic, List
import math
from JSONConsts import JSONConsts

T = TypeVar('T')

class AggData(Generic[T]):
    t = dict(
        pgno = 'page no',
        tpg = "page total",
        tint = "item total",
        itpg = 'item in page',
        data = "data"
    )
    def __init__(self, nperpage = 1):
        self.items: List[T] = []
        self.nppage = nperpage if nperpage > 0 else 1
        self.curpage = 1
        
    @property 
    def count(self):
        return len(items)
    
    @property 
    def count(self):
        return len(self.items)
    
    def append(self, item: T):
        self.items.append(item)
        
    def pop(self) -> T:
        return self.items.pop()
    
    def empty(self) -> bool:
        return self.count == 0
    
    def addwhole(self, tlst : List[T]) -> bool:
        end = len(tlst)
        if(end < 1):
            return False
        self.items.extend(tlst)
        return True 
        
    
    @property 
    def capsule(self):
        return {
            AggData.t["pgno"] : self.curpage,
            AggData.t["tpg"] : self.total_pages,
            AggData.t["tint"] : self.count,
            AggData.t["itpg"] : self.nppage
        }
        
    @property
    def total_pages(self) -> int:
        return int(math.ceil(self.count / self.nppage))
        
    def to_dictionary(self) -> dict:
        return { AggData.t["data"] : self.items } 
    
    def get_page(self, pageNo = 1) -> dict:
        if(pageNo > self.total_pages or pageNo < 1):
            odict.update( { AggData.t["data"] : JSONConsts.PAGEOUTRNG } )
            return odict
        self.curpage = pageNo
        odict = self.capsule
        startIdx = self.nppage * ( pageNo - 1 )
        endIdx = ( self.nppage + startIdx ) if (pageNo < self.total_pages) else self.count 
        data = self.items[ startIdx : endIdx ]
        odict.update( { AggData.t["data"] : data } )
        odict.update( { AggData.t["itpg"] : len(data) } )
        return odict
    
    def __iter__(self):
        self.curpage = 1 
        return self
    
    def __next__(self):
        if(self.total_pages >= self.curpage):
            odata = self.get_page(self.curpage)
            self.curpage += 1
            return odata
        raise StopIteration
            