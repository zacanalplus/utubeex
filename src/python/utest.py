#!/usr/bin/env python3

from userauth import appuser

if (__name__ == "__main__"):
    appusr = appuser("Smith", "0981620679", "Android", "v1.0", "Consumer")
    #appusr.debug_print()
    #print(vars(appusr))
    print(appusr.register())
    #print(appusr.to_dictionary())