#!/usr/bin/env python3

import datetime
from DBParameters import DBParameters
import uuid
import time
from mg_data import mg_data

DB_NAME = 'crm_asia'
DEF_FUNC_LIVE = 1_000_000
DEF_CFG_ID = 'b981620679a'
CFG_TBL_NAME = "appconfig"

class g_config(mg_data):
    def __init__(self):
        super().__init__(DB_NAME, CFG_TBL_NAME)
        self.id = DEF_CFG_ID
        self.flive = 0.0
        self.authport = 5005
        self.dataport = 8008
        self.wintents = ['API', 'Admin', 'Creator']
        self.updatedby = 'manual script'
        self.timezone = datetime.datetime.now(datetime.timezone.utc).astimezone().tzname()
    
    @property
    def cfgid(self):
        return self.id
    
    @property
    def auth_port(self):
        return self.authport
    
    @property 
    def data_port(self):
        return self.dataport
    
    @property 
    def key_query(self):
        return { "id" : self.id }
    
    @property
    def function_live(self):
        return self.flive
    
    @function_live.setter 
    def function_live(self, func_live):
        if(func_live < 0):
            self.flive = DEF_FUNC_LIVE
        else:
            self.flive = func_live
            
    def find(self):
        return super().find(self.key_query)
    
    def has_write_intent(self, intent : str) -> bool:
        if intent in self.wintents:
            return True 
        return False
        

    def find_config(self, cfg_id : str):
        qry = {
            "id" : cfg_id
        }
        found_record = super().search(qry)
        if found_record:
            for obj in found_record:
                self.id = obj["id"]
                self.flive = obj["flive"]
                self.authport = obj["authport"]
                self.dataport = obj["dataport"]
                for intent in obj["write intents"]:
                    self.wintents.append(intent)
                return True
        return False
    
    def update(self):
        return super().update(self.key_query, updatedBy = self.updatedby)
    
    def add(self):
        return super().add(addedBy = self.updatedby)

    def to_dictionary(self) -> dict :
        return {
            "id" : self.id,
            "flive" : self.flive,
            "authport" : self.authport,
            "dataport" : self.dataport,
            "write intents" : self.wintents,
            "timezone" : self.timezone
        }