# mg_data.py
# Created by Zarni Aung on 8/20/24.

import datetime
from pymongo import MongoClient
from DBParameters import DBParameters

AddAuditTags = ["addedon", "addedby"]
UpdAuditTags = ["updatedon", "updatedby"]
DelAuditTags = ["deleted", "deletedon", "deletedby"]

INS_QRY = { AddAuditTags[0] : "", AddAuditTags[1] : "" }
UPD_QRY = { UpdAuditTags[0] : "", UpdAuditTags[1] : "" }
DEL_QRY = { DelAuditTags[0] : True, DelAuditTags[1] : "", DelAuditTags[2] : "" }

''' Mongo data collection base class '''
class MgCol:
    def __init__(self, dbName : str, colName : str):
        self.db_parameters = DBParameters("env.yaml")
        self.client = MongoClient(self.db_parameters.uri())
        self.dbName = dbName
        self.colName = colName
        self.db = self.client[dbName]
        self.col = self.db[colName]
        self.id = ""
        
    def find(self, keyQry : dict) -> bool:
        found_rec = self.col.find(keyQry)
        if(found_rec):
            for obj in found_rec:
                return True
        return False
    
    @property
    def obj_id(self):
        return self.id 
    
    def search(self, keyQry : dict, removeObjId = True, showAudit = False) -> list :
        recs = list()
        found_rec = self.col.find(keyQry)
        if(found_rec):
            for obj in found_rec:
                self.id = obj.get("_id")
                if(removeObjId): 
                    obj.pop("_id", None)
                if(not showAudit):
                    for tags in UpdAuditTags:
                        obj.pop(tags, None)
                    for tags in DelAuditTags:
                        obj.pop(tags, None)
                recs.append(obj)
        return recs
    
    def add(self, addedBy : str = "") -> bool :
        return self.add_delete_able(addedBy)
    
    def add_deletable(self, addedBy : str = "", can_delete : bool = False) -> bool :
        self.add_nokey(addedBy, can_delete)
        if(self.id):
            return True
        return False
    
    def add_nokey(self, addedBy : str = "", can_delete : bool = False) -> str :
        odict = self.to_dictionary()
        if(addedBy):
            INS_QRY[AddAuditTags[0]] = datetime.datetime.now()
            INS_QRY[AddAuditTags[1]] = addedBy
            odict.update(INS_QRY)
        if(can_delete):
            DEL_QRY[DelAuditTags[0]] = False
            DEL_QRY[DelAuditTags[1]] = ""
            DEL_QRY[DelAuditTags[2]] = ""
            odict.update(DEL_QRY)
        ins_ok = self.col.insert_one(odict)
        if(ins_ok):
            self.id = ins_ok.inserted_id
            return self.id
        return ""
    
    def update(self, keyQry : dict, updatedBy : str = "" ) -> bool:
        update_data = self.to_dictionary()
        if(updatedBy):
            UPD_QRY[UpdAuditTags[0]] = datetime.datetime.now()
            UPD_QRY[UpdAuditTags[1]] = updatedBy
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
                DEL_QRY[DelAuditTags[0]] = True
                DEL_QRY[DelAuditTags[1]] = datetime.datetime.now()
                DEL_QRY[DelAuditTags[2]] = deletedBy
            return self.add_update(keyQry, DEL_QRY)
        return False
        
    def to_dictionary(self) -> dict:
        pass
    
    