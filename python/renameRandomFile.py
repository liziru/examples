#! /usr/bin/python
#encoding:utf-8

import os
import random
import sys

def main():
    path="/tmp/testshell"

    for root,dir,file in os.walk(path):
        pass
        for name in file:
            if name.split("_")[1] == "oldboy.html":
                newname=name.split("_")[0]+"oldgirl.html"
                os.rename(path+name,path+newname)
                if os.path.exists(path+newname):
                    print  "%s have been change name to %s" %(oldfilename,newfilename)
                else:
                    print "%s changed name failed." %(oldfilename)

if __name__=="__main__":
    main()