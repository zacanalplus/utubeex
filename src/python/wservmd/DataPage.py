#!/usr/bin/env python3

from typing import TypeVar, Generic, List
import math

T = TypeVar("T")

class DataPage(Generic[T]):
    t = dict(
        data = "data",
        error = "error", 
        cpno = "current page no",
        tpage = "total pages",
        itotal = "item total",
        nitem = "item in page"
    )
    def __init__(self, nperpage = 1):
        self.data : List[T] = []
        # number of item per page
        self.nppage = nperpage if nperpage > 0 else 1
        self.curpage = 1
    
    def set_pagesize(self, psize : int):
        self.nppage = psize
    
    @property 
    def count(self):
        return len(self.data)
    
    def append(self, item : T):
        self.data.append(item)
        
    def pop(self) -> T :
        return self.data.pop()
    
    def addwhole(self, dlst : List[T]) -> bool:
        if (len(dlst) < 1):
            return False
        self.data.extend(dlst)
        return True
    
    @property 
    def total_pages(self):
        return int(math.ceil(self.count / self.nppage))
    
    def to_dictionary(self) -> dict:
        return { DataPage.t["data"] : self.data }
    
    @property
    def meta_data(self) -> dict:
        return {
            DataPage.t["cpno"] : self.curpage,
            DataPage.t["tpage"] : self.total_pages,
            DataPage.t["itotal"] : self.count,
            DataPage.t["nitem"] : self.nppage
        }
    
    def get_page(self, pageNo = 1) -> dict:
        if(pageNo < 1 or pageNo > self.total_pages):
            return { DataPage.t["error"] : "Page number is out of range, no data" } 
        pdata = self.meta_data
        self.curpage = pageNo
        startIdx = self.nppage * (pageNo - 1)
        endIdx = (self.nppage + startIdx) if (pageNo < self.total_pages) else self.count
        items = self.data[startIdx : endIdx]
        pdata.update({DataPage.t["data"] : items})
        pdata.update({ DataPage.t["nitem"] : len(items) })
        return pdata 
    
    def __iter__(self):
        self.curpage = 1
        return self 
    
    def __next__(self):
        if(self.total_pages >= self.curpage):
            pdata = self.get_page(self.curpage)
            self.curpage += 1
            return pdata 
        raise StopIteration