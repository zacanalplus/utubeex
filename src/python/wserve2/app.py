#!/usr/bin/env/python3

from flask import Flask, render_template, jsonify, request
from userauth import appuser
from cfgconfig import g_config
from rproperty import rproperty, gps_loc, contact
from usrtrans import usrtrans
from JSONConsts import JSONConsts


app = Flask('wserve2')
#logging.basicConfig(level=logging.INFO, filename = "./log/debug.log", filemode="w")

@app.route("/dummy", methods = ['GET'])
def debug_dummy():
	req_name = request.args.get("testjson")
	if(req_name):
		return jsonify({"id" : "_dummy_json", "name" : "Dummy Json object for test", "InnerObj" : {"inid" : "0x34df", "inname" : "Inner dummy Json Object"} })
	return JSONConsts.WEB_PARAMREQ

@app.route("/", methods = ['GET'])
def home():
    return render_template('land_home.html')

@app.route("/addproperty", methods = ['GET', 'POST'])
def addproperty():
	bname = ""
	apartno = ""
	addr1 = ""
	addr2 = ""
	district = ""
	province = ""
	zip = ""
	loc = gps_loc()
	buildtype = ""
	fullfur = ""
	pict = ""
	contactinf = contact("", "")
	jbody = request.get_json()
	#print(jbody)
	if(jbody):
		t = rproperty.t
		try:
			tokenid = jbody["tokenid"]
		except:
			return jsonify(JSONConsts.JSON_TKNREQR)
		try:
			bname = jbody[t["name"]]
			apartno = jbody[t["apartno"]]
			addr1 = jbody[t["addr1"]]
			addr2 = jbody[t["addr2"]]
			district = jbody[t["district"]]
			province = jbody[t["province"]]
			zip = jbody[t["zip"]]
			loc.lattitude = jbody[t["loc"]][gps_loc.t["gps"]][0]
			loc.longitude = jbody[t["loc"]][gps_loc.t["gps"]][1]
			buildtype = jbody[t["buildtype"]]
			fullfur = jbody[t["fullfur"]]
			pict = jbody[t["pict"]]
			contactinf.fname = jbody[t["contactinf"]][contact.t["fullName"]]
			contactinf.phnum = jbody[t["contactinf"]][contact.t["phnumber"]]
		except:
			return jsonify(JSONConsts.JSON_WRONGFMT)
		
		utrans = usrtrans(tokenid, "addproperty")
		
		if(appuser.search(tokenid) is None):
			return JSONConsts.JSON_TKNINVD
		if(utrans.token_expired()):
			return JSONConsts.JSON_TKNEXPR
#		if(not rres):
#			return JSONConsts.USERNOINTENT
		
		try:
			oprop = rproperty()
			oprop.name = bname
			oprop.apartno = apartno
			oprop.addr1 = addr1
			oprop.addr2 = addr2
			oprop.district = district
			oprop.province = province
			oprop.zip = zip
			oprop.loc = loc
			oprop.buildtype = buildtype
			oprop.fullfur = fullfur
			oprop.pict = pict
			oprop.poc = contactinf
			if(oprop.save(tokenid)):
				utrans.serve()
				return jsonify(JSONConsts.JSON_OK)
		except Exception as error:
			#return jsonify({"reason" : str(error)})
			return JSONConsts.EMPTY_JSON
	return jsonify(JSONConsts.JSON_REQUIRED)

@app.route("/findproperty", methods = ['GET', 'POST'])
def findproperty():
	bname = ""
	apartno = ""
	addr1 = ""
	addr2 = ""
	district = ""
	province = ""
	zip = ""
	loc = gps_loc()
	buildtype = ""
	fullfur = ""
	pict = ""
	contactinf = contact("", "")
	jbody = request.get_json()
	#print(jbody)
	if(jbody):
		t = rproperty.t
		
		try:
			tokenid = jbody["tokenid"]
		except:
			return jsonify(JSONConsts.JSON_TKNREQR)
		if t["name"] in jbody:
			bname = jbody[t["name"]]
		if t["apartno"] in jbody:
			apartno = jbody[t["apartno"]]
		if t["addr1"] in jbody:
			addr1 = jbody[t["addr1"]]
		if t["addr2"] in jbody:
			addr2 = jbody[t["addr2"]]
		if t["district"] in jbody:
			district = jbody[t["district"]]
		if t["province"] in jbody:
			province = jbody[t["province"]]
		if t["zip"] in jbody:
			zip = jbody[t["zip"]]
		if t["loc"] in jbody:
			loc.lattitude = jbody[t["loc"]][gps_loc.t["gps"]][0]
			loc.longitude = jbody[t["loc"]][gps_loc.t["gps"]][1]
		if t["buildtype"] in jbody:
			buildtype = jbody[t["buildtype"]]
		if t["fullfur"] in jbody:
			fullfur = jbody[t["fullfur"]]
		
		if t["contactinf"] in jbody:
			contactinf.fname = jbody[t["contactinf"]][contact.t["fullName"]]
			contactinf.phnum = jbody[t["contactinf"]][contact.t["phnumber"]]
		
		utrans = usrtrans(tokenid, "findproperty")
		if(appuser.search(tokenid) is None):
			return JSONConsts.JSON_TKNINVD
		if(utrans.token_expired()):
			return JSONConsts.JSON_TKNEXPR
		
		
		oprop = rproperty()
		if(bname):
			oprop.name = bname
			oprop.blank = False 
		if(apartno):
			oprop.apartno = apartno
			oprop.blank = False
		if(addr1):
			oprop.addr1 = addr1
			oprop.blank = False
		if(addr2):
			oprop.addr2 = addr2
			oprop.blank = False
		if(district):
			oprop.district = district
			oprop.blank = False
		if(province):
			oprop.province = province
			oprop.blank = False
		if(zip):
			oprop.zip = zip 
			oprop.blank = False
		if(not loc.blank):
			oprop.loc = loc
			oprop.blank = False
		if(buildtype):
			oprop.buildtype = buildtype
			oprop.blank = False
		if(fullfur):
			oprop.fullfur = fullfur
			oprop.blank = False
		if(contactinf):
			oprop.poc = contactinf
			oprop.blank = False
			
		if(oprop.blank):
			return jsonify(JSONConsts.JSON_WRONGFMT)
		respJson = dict()
		respJson.update({"data" : oprop.find()})
		utrans.serve()
		return jsonify(respJson)
		
	return jsonify(JSONConsts.JSON_REQUIRED)



if (__name__ == "__main__"):
	gcfg = g_config()
	app.run(host='0.0.0.0', port = gcfg.data_port)

	