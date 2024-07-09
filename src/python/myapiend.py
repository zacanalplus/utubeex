#!/usr/bin/env python3

from flask import Flask, request, jsonify, render_template, Response

app = Flask('my_api_endpoint')

@app.route('/', methods = ['GET', 'POST'])
def home():
    return render_template('sample_home.html')

@app.route('/test', methods = ['GET'])
def test_dir():
    req_val = request.args.get("name")
    if(req_val):
        return jsonify({"Name" : req_val, "Id" : 843321, "Inner Object" : {"Child Id" : "754356", "Name": "Office"}})
    req_val = request.args.get("simple")
    if(req_val):
        return Response("<html><head></head><title>Simple Web page</title><body><h1>Simple Page with HTML</h1><p>This is simple web page with just only <i>HTML</i> and your value is {}.</p></body></html>".format(req_val))
    return jsonify({"Name" : "Sample json object", "Id" : 1011310, "Inner Object" :{"Child ID": "5172363", "Name" : "Inside Object"}})

if(__name__ == "__main__"):
    app.run(port=8888, debug = True)
    
    