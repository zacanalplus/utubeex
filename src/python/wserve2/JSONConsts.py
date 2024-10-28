# JSONConsts.py
# Created by Zarni Aung on 8/23/24.

class JSONConsts:
    def __init__(self):
        pass
        
    EMPTY_JSON = {}
    JSON_OK = { "status code" : 0, "status" : "OK" }
    WEB_PARAMREQ = {"error code" : 450, "error message" : "Parameter required, please check URL"}
    JSON_REQUIRED = { "error code" : 510, "error message" : "JSON parameter required" }
    JSON_WRONGFMT = { "error code" : 511, "error message" : "JSON format is wrong, please check API specification" }
    JSON_TKNEXPR = {"error code" : 512, "error message" : 'Token expired, please register to renew token'}
    JSON_TKNREQR = {"error code" : 513, "error message" : "Token ID is mandatory" }
    JSON_TKNINVD = {"error code" : 514, "error message" : "Invalid Token ID, please register again" }
    
    RESEARCH_ERR = {"error code" : 515, "error message" : "Unable to update property data, please search again and select to update" }
    JSONNOSUCHID = {"error code" : 516, "error message" : "Object with no such ID found, please search again and select to update"}
    USERNOINTENT = {"error code" : 517, "error message" : "User does not have intent to add/update data"}