"""
Export cqm firebird data to dbf for BIOS system
Autor: Ruslan Keba <rukeba@gmail.com>
Date: 2007-10-16
Site: www.infitis.dp.ua
"""

import sys
from dbfpy.dbf import *
from dbfpy.dbfnew import *
import kinterbasdb as fb; fb.init(type_conv=200)
from shutil import copyfile


#FB_HOST = "172.17.24.23"
FB_HOST = "localhost"
FB_USER = "client"
FB_PASS = "cli1"
FB_DB   = "stash"

DBF_FILE = "otk.dbf"

def main():
	
	# get date
	print "\n\
  +------------------------------------------+\n\
  |                                          |\n\
  |       MKU -> BIOS                        |\n\
  |                                          |\n\
  +------------------------------------------+\n\
\n"
	
	print " DATE  (01-31): ",
	rw_date = int(sys.stdin.readline(10))
	
	print "MONTH (01-12): ",
	rw_month = int(sys.stdin.readline(10))
	
	print "GOD   (200?) : ",
	rw_year = int(sys.stdin.readline(10))
	
	print rw_year,"-",rw_month,"-",rw_date
	
	
	# create firebird connection
	con = fb.connect(dsn='%s:%s' % (FB_HOST, FB_DB), user=FB_USER, password=FB_PASS)
	cur = con.cursor()
	# query
	cur.execute("select number, rwdate, wei, pos, cert, a from vagons\
	             where a is not null and wei is not null and\
	             pos is not null and cert is not null and number is not null and\
	             rwdate='%4d-%2d-%2d'" % (rw_year, rw_month, rw_date))
	
	# create new dbf
	dn=dbf_new()	
	dn.add_field("N_VAG", 'C',8)
	dn.add_field("DATA",  'D',8)
	dn.add_field("KOL_R", 'N',8,2)
	dn.add_field("N_POZ", 'C',7)
	dn.add_field("N_UD",  'C',5)
	dn.add_field("AN_ZOL",'N',5,2)
	dn.write(DBF_FILE)
	
	d = Dbf()
	d.openFile(DBF_FILE, readOnly=0)
	#d.reportOn()
	print
	
	for row in cur:
		#print row
		# add a record
		
		rec=DbfRecord(d)
		rec['N_VAG'] = str(row[0])
		rec['DATA']  = row[1].timetuple()
		rec['KOL_R'] = float(row[2])
		rec['N_POZ'] = "% 7s" % str(row[3])
		rec['N_UD']  = "% 5s" % str(row[4])
		rec['AN_ZOL']=float(row[5])
		rec.store()
		
		#print row[0], row[1], row[2], row[3], row[4], row[5]
		print rec['N_VAG'], rec['DATA'], rec['KOL_R'], rec['N_POZ'], rec['N_UD'], rec['AN_ZOL']

	print "Records exported: ", d.recordCount()
	print
	d.close()
	
	# save to floppy
	print "Insert disk in floppy drive and press enter"
	sys.stdin.readline()
	
	copyfile(DBF_FILE, "c://%s" % DBF_FILE)
	
	print "Ready"
	
	time.sleep(3)
	
	

if __name__ == "__main__":
	main()