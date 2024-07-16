#!/usr/bin/env python3

# Simple API development with Python
from flask import Flask, Response, request, render_template, jsonify

app = Flask('myapiend')

@app.route("/", methods = ['GET'])
def home():
    return render_template('sample_home.html')

@app.route("/test", methods = ['GET'])
def test_dir():
    '''This function return Json object and shows how to get paramter from web request. '''
    req_name = request.args.get("name")
    if(req_name):
        return jsonify({"ID" : "75546578", "Name" : req_name, "Inner_Object" :{"InID" : 8465382, "InName" : "Inner Json Object"} })


@app.route("/simple", methods = ['GET'])
def simple_page():
    '''This function return simple HTML code as response page'''
    return Response("<html><head></head> <body> <p> This is simple <i>HTML</i> page. </p> </body> </html>")



if(__name__ == "__main__"):
    app.run(port = 8888, debug = True)
    
# do not put route in here