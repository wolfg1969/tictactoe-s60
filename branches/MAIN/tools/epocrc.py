#!C:\Python24\python.exe
"""
eporrc.py
This script is to help Carbide.c++ Express compiling the localization resource files.
Usage: put it in $EPOCROOT/Epoc32/tools, then change the "Resource Compiler command"
from "perl -s epocrc.pl" to "epocrc.py" in project properties and change the "Defined
Symbols" from "LANGUAGE_SC" to "LANGUAGE_01 and LANGUAGE_31" in it's general options.
"""

from optparse import OptionParser
import os, os.path, getopt, subprocess, sys

def main():

    os.environ['EPOCROOT'] = os.path.splitdrive(os.environ['EPOCROOT'])[1]

    parser = OptionParser(add_help_option=False)
    
    parser.add_option("-D", action="append", dest="DefinedSymbols") 
    parser.add_option("-I", action="append", dest="IncludePaths") 
    parser.add_option("-v", action="store_true", dest="verbose")
    parser.add_option("-u", action="store_true", dest="unicode")
    parser.add_option("-o", action="store", dest="outputfile")
    parser.add_option("-h", action="store", dest="headerfile")
    parser.add_option("-M", action="store", dest="dummy")
    #parser.add_option("-t", action="store", dest="tmpdir")    
    #parser.add_option("-nocpp", action="store_true", dest="nocpp")
    #parser.add_option("-l", action="store_true", dest="localisation")
    
    (options, args) = parser.parse_args()
    
    cmd = ['perl', '-S', 'epocrc.pl']
    
    if parser.has_option('-v'):
        cmd.append('-v')  
        
    if parser.has_option('-u'):
        cmd.append('-u')
    if parser.has_option('-M'):
        cmd.append('-MD')

    command = " ".join(cmd)
    commandlist = []
    
    needLocalisation = True
    
    for arg in args:
        if arg.lower().find('aif') >= 0:
            needLocalisation = False
            break
    
    if parser.has_option('-D') and needLocalisation:
        if needLocalisation:
            for symbol in options.DefinedSymbols:
                c = command.split(" ")
                c.append('-D' + symbol)
                commandlist.append(" ".join(c))
    else:
        if not needLocalisation:
            cmd.append('-DLANGUAGE_SC')
        commandlist.append(" ".join(cmd))
    
    for command in commandlist:
        cmd = command.split(" ")

        if parser.has_option('-I'):
            for path in options.IncludePaths:
                if path == '-':
                    cmd.append('-I-')
                else:
                    cmd.append('-I"' + path + '"')
    
        if parser.has_option('-o'):
        
            root, ext = os.path.splitext(options.outputfile)           
            
            optlist, cmd_args = getopt.getopt(cmd[3:], 'vuMI:D:')
            
            for o, a in optlist:
                if o == '-D':
                    print a
                    ext = '.r' + a[-2:]
            filename = root + ext.lower()
            cmd.append('-o"' + filename +'"')
            
            if os.path.isfile(filename):
                os.unlink(filename)
        
        if parser.has_option('-h'):
            cmd.append('-h' + options.headerfile)
            
        for arg in args:
            cmd.append(arg) 
        
        print "Compile resource file for language LANGUAGE_%s" % (ext[2:]) 
        subprocess.call(" ".join(cmd))


if __name__ == "__main__":
    main()
