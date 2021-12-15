import sys, os, struct

def scriptdir():
    """Returns the folder the current script is running in"""
    pathname = os.path.dirname(sys.argv[0])        
    return os.path.abspath(pathname)

def is_64bit():
    return struct.calcsize('P') * 8 == 64