# mg_data.py
# Created by Zarni Aung on 8/20/24.

import datetime
import uuid
import time
from pymongo import MongoClient
from DBParameters import DBParameters

INS_QRY = { "addedon" : time.time(), "addedby" : "" }
UPD_QRY = { "updatedon" : datetime.datetime.now(), "updatedby" : "" }
DEL_QRY = { "deleted" : True, "deletedon" : datetime.datetime.now(), "deletedby" : "" }

class mg_data:
    def __init__(self, dbName : str, colName : str):
        self.db_parameters = DBParameters("env.yaml")
        self.client = MongoClient(self.db_parameters.uri())
        self.dbName = dbName
        self.colName = colName
        self.db = self.client[dbName]
        self.col = self.db[colName]
        
    def find(self, keyQry : dict) -> bool:
        found_rec = self.col.find(keyQry)
        if(found_rec):
            for obj in found_rec:
                return True
        return False
    
    def search(self, keyQry : dict, removeObjId = True) -> list :
        recs = list()
        found_rec = self.col.find(keyQry)
        if(found_rec):
            for obj in found_rec:
                if(removeObjId):
                    obj.pop("_id", None)
                recs.append(obj)
        return recs
    
    def add(self, addedBy : str = "") -> bool :
        return self.add_delete_able(addedBy)
    
    def add_delete_able(self, addedBy : str = "", can_delete : bool = False) -> bool :
        odict = self.to_dictionary()
        if(addedBy):
            INS_QRY["addedby"] = addedBy
            odict.update(INS_QRY)
        if(can_delete):
            odict.update({ "deleted" : False, "deletedon" : "", "deletedby" : "" })
        ins_ok = self.col.insert_one(odict)
        if(ins_ok):
            return True
        return False
    
    def add_nokey(self, addedBy : str = "", can_delete : bool = False) -> str :
        odict = self.to_dictionary()
        if(addedBy):
            INS_QRY["addedby"] = addedBy
            odict.update(INS_QRY)
        if(can_delete):
            odict.update({ "deleted" : False, "deletedon" : "", "deletedby" : "" })
        ins_ok = self.col.insert_one(odict)
        if(ins_ok):
            return ins_ok.inserted_id
        return ""
    
    def update(self, keyQry : dict, updatedBy : str = "" ) -> bool:
        update_data = self.to_dictionary()
        if(updatedBy):
            UPD_QRY["updatedby"] = updatedBy
            update_data.update(UPD_QRY)
        upd_ok = self.col.update_one(
            keyQry,
            { "$set" : update_data }
        )
        if(upd_ok):
            return True
        return False
    
    # This special add update function is for `delete` function
    # `delete` function does not literally delete but update "delete info"
    def add_update(self, keyQry : dict, dupd_data : dict) -> bool:
        upd_ok = self.col.update_one(
            keyQry,
            { "$set" : dupd_data }
        )
        if(upd_ok):
            return True
        return False
    
    def delete(self, keyQry : dict, deletedBy : str = "") -> bool:
        if(self.find(keyQry)):
            if(deletedBy):
                DEL_QRY["deletedby"] = deletedBy
            return self.add_update(keyQry, DEL_QRY)
        return False
        
    def to_dictionary(self) -> dict:
        pass
    
    