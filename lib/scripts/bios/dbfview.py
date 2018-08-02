from dbfpy import dbf
import sys

def main():
	d = dbf.Dbf()
	d.openFile(sys.argv[1], readOnly=1)
	d.reportOn()
	print 'sample records:'
	for i in range(len(d)):
		rec = d[i]
		for fldName in d.fieldNames():
			print '%s:\t %s'%(fldName, rec[fldName])
		print
	d.close()

if __name__ == "__main__":
	main()