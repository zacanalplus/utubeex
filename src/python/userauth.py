#!/usr/bin/env python3

from pymongo import MongoClient 
import datetime
from DBParameters import DBParameters
import uuid
from cfgconfig import g_config
import time 
from mg_data import mg_data

DB_NAME = 'crm_asia'
USR_COL_NAME = 'app_users'

EMPTY_JSON = {}

class appinf:        
    def __init__(self, nm, vr):
        self.name = nm
        self.ver = vr
        
    def __repr__(self):
        return repr(vars(self))
    
    def to_dictionary(self):
        return {
            "appname" : self.name,
            "ver" : self.ver
        }

class register_response:
    def __init__(self, nm, phno, tkid, regat, valtill):
        self.name = nm
        self.phonenumber = phno
        self.tokenid = tkid
        self.registeredat = regat
        self.validtill = valtill

class appuser(mg_data):
    def update_ids(self):
        self.uid = uuid.uuid4().hex
        self.oid = hash(self)
    
    def __init__(self, nm, phno, appnm, appver, uintent):
        super().__init__(DB_NAME, USR_COL_NAME)
        self.uid = ""
        self.oid = ""
        self.name = nm 
        self.phonenumber = phno
        self.app = appinf(appnm, appver)
        self.intent = uintent
        self.cfgparams = g_config()
        self.cfgparams.find_config(self.cfgparams.id)
        self.registerat = 0
        self.validtill = 0
    
    def __hash__(self):
        return hash((self.name, self.phonenumber)) 
        
    @property    
    def token_id(self):
        return self.uid
    
    @property
    def key_query(self):
        return { "tokenid" : self.token_id }
    
    def has_wintent(self) -> bool:
        return self.cfgparams.has_write_intent(self.intent)
    
    def find(self):
        qry = {
            "name" : self.name,
            'phonenumber' : self.phonenumber
        }
        o_found = super().search(qry)
        if(o_found):
            for obj in o_found:
                self.uid = obj["tokenid"]
                self.intent = obj["intent"]
                return True
        return False
    
    def pure_search(self, keyQry : dict) -> register_response:
        o_found = super().search(keyQry)
        if(o_found):
            for obj in o_found:
                rres = register_response(obj["name"], obj["phonenumber"], obj["tokenid"], obj["registeredat"], obj["validtill"])
                self.intent = obj["intent"]
                
                return rres
        return None

    
    def search(tkid : str) -> register_response:
        usr = appuser("", "", "", "", "")
        qry = {
            "tokenid" : tkid
        }
        return usr.pure_search(qry)
    
    def intent_ok(tkid : str) -> bool:
        usr = appuser("", "", "", "", "")
        qry = {
            "tokenid" : tkid
        }
        usr.pure_search(qry)
        return usr.has_wintent()
    
    def update(self, updatedby : str):
        return super().update(self.key_query, updatedBy = updatedby)
    
    def add(self, addedby : str):
        return super().add(addedBy = addedby)
        
    def to_dictionary(self):
        self.registerat = time.time() * 1000
        self.validtill = self.registerat + self.cfgparams.flive
        usr_dict = {
            "name" : self.name,
            "phonenumber" : self.phonenumber,
            "tokenid" : self.uid,
            "intent" : self.intent,
            "registeredat" : self.registerat,
            "validtill" : self.validtill
        }
        usr_dict.update(self.app.to_dictionary())
        return usr_dict
        
    def register(self):
        self.registerat = time.time() * 1000
        self.validtill = self.registerat + self.cfgparams.flive
        if(self.find()):
            if(self.update(self.name)):
                rreq = register_response(self.name, self.phonenumber, self.uid, self.registerat, self.validtill)
                return vars(rreq)
            return EMPTY_JSON
        else:
            self.update_ids()
            if(self.add(self.name)):
                rreq = register_response(self.name, self.phonenumber, self.uid, self.registerat, self.validtill)
                return vars(rreq)
            
            return EMPTY_JSON
        