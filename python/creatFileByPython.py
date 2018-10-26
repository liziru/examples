#! /usr/bin/python
#encoding:utf-8

import os
import random

def getRandomChar():
    seed="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    sa=[]
    for i in xrange(10):
        sa.append(random.choice(seed))
    #print sa
    salt=''.join(sa)
    return salt

def createFile(name):
    path="/home/lee/testshell/"
    if os.path.exists(path) != True:
        os.mkdir(path)

    filename=path+name
    #print filename
    with open(filename,"wb") as f:                     #create file
        pass
        
    if os.path.exists(filename):
        print "%s have been created" %filename                  #print the result
    else:
        print "create file failed,Please check it."



def main():
    for i in range(10):
        filename=getRandomChar()+"_oldboy.html"
        createFile(filename)


if __name__=="__main__":
    main()
    