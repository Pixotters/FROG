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
    print "Usage : add the name of your GameObject as argument"

def printwrongname():
    print "C++ classes names can contain only letters, numbers and underscores."

def checkname(name):
    return ( name[0].isalpha() or name[0] == '_') \
and name[1:].replace('_', '').isalnum()

def main():
    if len(sys.argv) != 2:
        printusage()
    else:
        if checkname(sys.argv[1]):
            go_name = sys.argv[1]
            go_name = go_name[0].upper() + go_name[1:]
            creategameobject(dummy+".cpp", go_name )
            creategameobject(dummy+".hpp", go_name )    
        else:
            printwrongname()
 
main()
