#!/usr/bin/env python3

import time
from cfgconfig import g_config

if (__name__ == "__main__"):
    print(f"Debug print current time in milliseconds {time.time() * 1000}")
    cfgdata = g_config()
    cfgdata.function_live = 3_000_000
    #print(cfgdata.to_dictionary())
    if(cfgdata.find()):
        if(cfgdata.update()):
            print("Function timeout value is updated. ")
        cfgdata.find_config(cfgdata.id)
        print("After Refresh from DB")
        print(cfgdata.to_dictionary())
    else:
        if(cfgdata.add()):
            print("Function timeout value is inserted for first time. ")