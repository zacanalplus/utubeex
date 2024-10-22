# entity.py
# Created by Zarni Aung on 8/21/24.

from mg_data import mg_data
from JSONConsts import JSONConsts
from bson.objectid import ObjectId

DB_NAME = 'crm_asia'
ENT_COL_NAME = 'restates'

class contact:
    t = dict(
        fullName = "Contact full name",
        phnumber = "Contact number"
    )
    
    def __init__(self, fullName, phno):
        self.blank = True
        if(fullName and phno):
            self.fname = fullName
            self.phnum = phno 
            self.blank = False
        
        
    def to_dictionary(self):
        return {
            contact.t["fullName"] : self.fname,
            contact.t["phnumber"] : self.phnum
        }

class gps_loc:
    t = dict(
        gps = "gps"
    )
    
    def __init__(self, latt = 0.0, long = 0.0):
        self.latt = latt
        self.long = long
        self.blank = True
        
    @property 
    def lattitude(self):
        return self.latt 
    
    @lattitude.setter 
    def lattitude(self, ltval):
        self.latt = ltval
        self.blank = False
        
    @property 
    def longitude(self):
        return self.long
    
    @longitude.setter 
    def longitude(self, lgval):
        self.long = lgval
        self.blank = False
        
    def to_dictionary(self):
        return {
            gps_loc.t["gps"] : (self.latt, self.long)
        }

# Real estate property class
class rproperty(mg_data):
    # The string descriptions dictionary for Object representation in JSON
    t = dict(
        name = "name",
        apartno = "floor, apartment no",
        addr1 = "address 1",
        addr2 = "address 2",
        district = "district",
        province = "province",
        zip = "zip",
        loc = "GPS location",
        buildtype = "building type",
        fullfur = "furnished",
        pict = "picture string",
        contactinf = "Contact info"
    )
            
            
    def __init__(self):
        super().__init__(DB_NAME, ENT_COL_NAME)
        self.name = ""
        self.addr1 = ""
        self.addr2 = ""
        self.apartno = ""
        self.district = ""
        self.province = ""
        self.zip = 0
        self.loc = gps_loc()
        self.buildtype = ""
        self.fullfur = ""
        self.pict = ""
        self.poc = contact("", "")
        # ID is populated from Collection's "ObjectId()"
        self.iid = ""
        self.blank = True
        
    @property 
    def prop_id(self):
        return self.iid
    
    def to_dictionary(self):
        return {
            rproperty.t["name"] : self.name,
            rproperty.t["apartno"] : self.apartno, 
            rproperty.t["addr1"] : self.addr1,
            rproperty.t["addr2"] : self.addr2,
            rproperty.t["district"] : self.district,
            rproperty.t["province"] : self.province,
            rproperty.t["zip"] : self.zip,
            rproperty.t["loc"] : self.loc.to_dictionary(),
            rproperty.t["buildtype"] : self.buildtype,
            rproperty.t["fullfur"] : self.fullfur,
            rproperty.t["pict"] : self.pict,
            rproperty.t["contactinf"] : self.poc.to_dictionary()
        }
        
    def save(self, addedBy : str = ""):
        self.iid = super().add_nokey(addedBy, True)
        if(self.iid):
            return True
        return False
    
    def key_query(self):
        if(self.iid):
            return { "_id" : ObjectId(self.iid) }
        return ""
    
    def update(self, updatedBy : str) -> dict:
        qry = self.key_query()
        if(qry):
            return super().update(qry, updatedBy)
        return JSONConsts.RESEARCH_ERR
    
    def get_query(self) -> dict:
        qry = dict()
        if(self.name):
            qry.update( { rproperty.t["name"] : self.name } )
        if(self.apartno):
            qry.update( { rproperty.t["apartno"] : self.apartno } )
        if(self.addr1):
            qry.update( {"$or" : [{ rproperty.t["addr1"] : self.addr1 }, { rproperty.t["addr2"] : self.addr1 }]} )
        if(self.addr2):
            qry.update( {"$or" : [{ rproperty.t["addr2"] : self.addr2 }, { rproperty.t["addr1"] : self.addr2 }]} )
        if(self.district):
            qry.update( { rproperty.t["district"] : self.district } )
        if(self.province):
            qry.update( { rproperty.t["province"] : self.province } )
        if(self.zip):
            qry.update( { rproperty.t["zip"] : self.zip } )
        if(not self.loc.blank):
            qry.update( { rproperty.t["loc"] : self.loc.to_dictionary() } )
        if(self.buildtype):
            qry.update( { rproperty.t["buildtype"] : self.buildtype } )
        if(self.fullfur):
            qry.update( { rproperty.t["fullfur"] : self.fullfur } )
        if(not self.poc.blank):
            qry.update({rproperty.t["contactinf"] : self.poc.to_dictionary() })
        qry.update({"deleted" : False})
        return qry
        
    def find(self) -> list:
        qry = self.get_query()
        if(qry):
            res_lst = super().search(qry)
            return res_lst
        return list()
    
    def qry_by_json(dictjson) -> dict:
        updqry = dict()
        for k in rproperty.t:
            v = rproperty.t[k] 
            if(v in dictjson):
                if(k == "loc"):
                    gloc = gps_loc()
                    gloc.lattitude = dictjson[v]["gps"][0]
                    gloc.longitude = dictjson[v]["gps"][1]
                    updqry.update({ v : gloc.to_dictionary() })
                elif(k == "contactinf"):
                    contct = contact(dictjson[v][contact.t["fullName"]], dictjson[v][contact.t["phnumber"]])
                    updqry.update({ v : contct.to_dictionary() })
                else:
                    updqry.update({ v : dictjson[v]})
                
        return updqry
    
    def to_query(self):
        qry = dict()
        if(self.name):
            qry.update( { rproperty.t["name"] : self.name } )
        if(self.apartno):
            qry.update( { rproperty.t["apartno"] : self.apartno } )
        if(self.addr1):
            qry.update( { rproperty.t["addr1"] : self.addr1 } )
        if(self.addr2):
            qry.update( { rproperty.t["addr2"] : self.addr2 } )
        if(self.district):
            qry.update( { rproperty.t["district"] : self.district } )
        if(self.province):
            qry.update( { rproperty.t["province"] : self.province } )
        if(self.zip):
            qry.update( { rproperty.t["zip"] : self.zip } )
        if(not self.loc.blank):
            qry.update( { rproperty.t["loc"] : self.loc.to_dictionary() } )
        if(self.buildtype):
            qry.update( { rproperty.t["buildtype"] : self.buildtype } )
        if(self.fullfur):
            qry.update( { rproperty.t["fullfur"] : self.fullfur } )
        if(not self.poc.blank):
            qry.update({rproperty.t["contactinf"] : self.poc.to_dictionary() })
        qry.update({"deleted" : False})
        return qry
    
        
    
    def search(self, djson) -> list:
        qry = rproperty.qry_by_json(djson)
        if(qry):
            res_lst = super().search(qry)
            return res_lst
        return list()
            
    def select(self) -> bool:
        t = rproperty.t
        objs = None
        if(self.iid):
            objs = super().search(self.key_query(), removeObjId = False)
        else:
            objs = super().search(self.get_query(), removeObjId = False)
        if(objs):
            sobj = objs[0]
            self.iid = super().obj_id
            self.name = sobj[t["name"]]
            self.apartno = sobj[t["apartno"]]
            self.addr1 = sobj[t["addr1"]]
            self.addr2 = sobj[t["addr2"]]
            self.district = sobj[t["district"]]
            self.province = sobj[t["province"]]
            self.zip = sobj[t["zip"]]
            gobj = sobj[t["loc"]][gps_loc.t["gps"]]
            self.loc = gps_loc(gobj[0], gobj[1])
            self.buildtype = sobj[t["buildtype"]]
            self.fullfur = sobj[t["fullfur"]]
            self.pict = sobj[t["pict"]]
            
            cobj = sobj[t["contactinf"]]
            self.poc = contact(cobj[contact.t["fullName"]], cobj[contact.t["phnumber"]])
            return self.to_query()
        return JSONConsts.JSONNOSUCHID