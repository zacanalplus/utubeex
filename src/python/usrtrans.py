# usrtrans.py
# Created by Zarni Aung on 8/21/24.

import time
import datetime
from bson.objectid import ObjectId
from mg_data import mg_data
from userauth import appuser, register_response

DB_NAME = 'crm_asia'
TRCOL_NAME = 'apptrans'
CHANGE_AGENT = 'Workflow'

class usrtrans (mg_data):
    def __init__(self, tkid, funcName : str):
        super().__init__(DB_NAME, TRCOL_NAME)
        self.tokenid = tkid
        self.funname = funcName
        self.executedtsmp = time.time() * 1000
        self.served = False
        self.id = ""
    
    def token_expired(self) -> bool:
        rres = appuser.search(self.tokenid)
        if(self.executedtsmp > rres.registeredat and self.executedtsmp < rres.validtill):
            return False
        return True
    
    def serve(self):
        self.served = True
        return self.update()
        
    def save(self):
        self.id = super().add_nokey(CHANGE_AGENT)
        if(self.id):
            return True
        return False
    
    def update(self):
        kqry = self.key_query()
        if(kqry):
            super().update(kqry, updatedBy = CHANGE_AGENT)
            return True 
        return False
    
    @property
    def token_query(self):
        return {
            "tokenid" : self.tokenid
        }
    
    def token_ok(self) -> bool:
        if(self.tokenid):
            return self.find(self.token_query)
        return False
        
    def key_query(self):
        if(self.id):
            return { "_id" : ObjectId(self.id) }
        return ""
    
    def to_dictionary(self) -> dict:
        return {
            "tokenid" : self.tokenid,
            "function name" : self.funname,
            "executed timestamp" : self.executedtsmp,
            "executedon" : datetime.datetime.now(),
            "token expired" : self.token_expired(),
            "served" : self.served
        }