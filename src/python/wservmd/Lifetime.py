# Lifetime.py
# Created by Zarni Aung on 8/30/24.

import time

THOUSAND = 1000

class Lifetime:
    def __init__(self, lifespan):
        self.started = time.time() * THOUSAND
        self.ls = lifespan
        
    @property 
    def lifespan(self):
        return self.ls
    
    def expired(self) -> bool:
        now = time.time() * THOUSAND
        if now > (self.lifespan + self.started): 
            return True
        return False