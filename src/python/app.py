#!/usr/bin/env/python3

from flask import Flask, render_template, jsonify, request
from userauth import appuser, EMPTY_JSON
from cfgconfig import g_config

JSON_REQUIRED = { "error code" : 510, "error_message" : "JSON parameter required" }
JSON_WRONGFMT = { "error code" : 511, "error_message" : "JSON format is wrong, please check API specification" }


app = Flask('wserve1')
#logging.basicConfig(level=logging.INFO, filename = "./log/debug.log", filemode="w")

@app.route("/dummy", methods = ['GET'])
def debug_dummy():
	req_name = request.args.get("testjson")
	if(req_name):
		return jsonify({"id" : "_dummy_json", "name" : "Dummy Json object for test", "InnerObj" : {"inid" : "0x34df", "inname" : "Inner dummy Json Object"} })

@app.route("/", methods = ['GET'])
def home():
    return render_template('land_home.html')

@app.route("/registeruser", methods = ['GET', 'POST'])
def register_user():
	uname = ""
	uphno = ""
	uappnm = ""
	uappvr = ""
	uintent = ""
	jbody = request.get_json()
	#print(jbody)
	if(jbody):
		try:
			uname = jbody["name"]
			uphno = jbody["phonenumber"]
			uappnm = jbody["app"]["appName"]
			uappvr = jbody["app"]["ver"]
			uintent = jbody["intent"]
		
		except:
			return jsonify(JSON_WRONGFMT)
		
		try:
			ausr = appuser(uname, uphno, uappnm, uappvr, uintent)
			return jsonify(ausr.register())
		except:
			return EMPTY_JSON
	return jsonify(JSON_REQUIRED)
	

if (__name__ == "__main__"):
	gcfg = g_config()
	app.run(host='0.0.0.0', port = gcfg.auth_port)

	