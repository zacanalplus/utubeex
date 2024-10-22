# Blank.py
# Created by Zarni Aung on 8/30/24.

class Blank:
    def __init__(self):
        self.blank = False 
        
    def setblank(self):
        self.blank = True
        
    @property 
    def nodata(self):
        return self.blank