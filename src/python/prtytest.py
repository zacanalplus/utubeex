#!/usr/bin/env python3

from rproperty import rproperty, gps_loc
from usrtrans import usrtrans

#hs1 = rproperty()
#hs1.name = "Ideo Mobile"
#hs1.addr1 = "1120/1401"
#hs1.addr2 = "Sukhumvit road"
#hs1.district = "Samrong"
#hs1.province = "Samrong Nua"
#hs1.zip = 13340
#hs1.loc = gps_loc()
#hs1.buildtype = "Condo"
#hs1.fullfur = "Fully furnished"
#hs1.poc.fname = "Mr.Goh"
#hs1.poc.phnum = "0851536762"
#
#print("New condo apartment added", end = ' ')
#print(hs1.save())
#jsontest= { 
#   "addr1" : "135/156", 
#   "addr2" : "Rama IX road", 
#   #"zip" : 10310, 
#   "testfield" : "testdata",
#   "GPS location" : { "gps" : [123.123, 92.92] },
#   "Contact info" : { "Contact full name" : "Mr.Saman", "Contact number" : "0972518772" }
#}
#print(rproperty.qry_by_json(jsontest))

#utrans = usrtrans('59ae7b9f7c1048caa18dd7d5550e3554', 'rproperty.find')
#if(utrans.token_expired()):
#   print('Token expired, please register to renew token')
#else:
#   if(utrans.save()):
#       print('User transaction registered!')
hs2 = rproperty()
#hs2.name = "Imperial World"
#print(hs2.get_query())
#print(hs2.find())
#print(hs2.search(jsontest))
#if(utrans.token_expired()):
#   print('Token expired, please register to renew token')
#else:
#   if(utrans.serve()):
#       print('User transaction completed!')
#hs2.loc = gps_loc(123.123, 92.92) 
#print(hs2.select())
#print(hs2.key_query())

hs2.iid = '66c766f0b9e43c0876e3bb5d'
print(hs2.select())
print(hs2.key_query())
#hs2.zip = 11301
#print(hs2.update("Manual"))