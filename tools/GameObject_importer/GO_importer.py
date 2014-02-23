import sys

dummy = "Dummy"

def getfilelines(filename):
    fil = open(filename, 'r')
    lines = fil.readlines()
    fil.close()
    return lines


def convert(filename, lines, replacename):
    fil = open(filename.replace(dummy, replacename), 'w')
    for line in lines:
        line = line.replace(dummy, replacename) 
        line = line.replace(dummy.upper(), replacename.upper() )
        fil.write(line)
    fil.write("\n")
    fil.close()

def creategameobject(filename, replacename):
    lines = getfilelines(filename)
    convert(filename, lines, replacename)
    
def printusage():
    print "Usage : add arguments as your GameObjects' names"

def printwrongname(s):
    print s+""" is an invalid name : 
C++ classes names can contain only letters, numbers and underscores."""

def checkname(name):
    return ( name[0].isalpha() or name[0] == '_') \
and (len(name) == 1 or name[1:].replace('_', '').isalnum()  )

def main():
    if len(sys.argv) < 2:
        printusage()
    else:
        for s in sys.argv[1:]:
            if checkname(s):
                go_name = s
                go_name = go_name[0].upper() + go_name[1:]
                creategameobject(dummy+".cpp", go_name )
                creategameobject(dummy+".hpp", go_name )    
            else:
                printwrongname(s)
 
main()
