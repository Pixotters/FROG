
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
    

def main():
    go_name = "myGo"
    go_name = go_name[0].upper() + go_name[1:]
    creategameobject(dummy+".cpp", go_name )
    creategameobject(dummy+".hpp", go_name )    
 
main()
