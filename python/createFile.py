#! /usr/bin/python
#encoding:utf-8

import os
import random

#encoding:utf-8

import random
import os

def get10char():                                        #create 10 random charactors
  seed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
  sa = []
  for i in xrange(10):
    sa.append(random.choice(seed))


  salt = ''.join(sa)

  return salt

def createfile(name):
  path="/tmp/shelltmp/"                                 #check whether the dir is exists,if not create it
  if os.path.exists(path) != True:
    os.mkdir(path)

  pathAndName=path+name
  with open(pathAndName,"wb") as f:                     #create file
    pass
  if os.path.exists(pathAndName):
    print "%s have been created" %name                  #print the result
  else:
    print "create file failed,Please check it."


def main():
  for i in xrange(10):                                  #loop 10 times to create 10 file
    filename=get10char()+"_oldboy.html"
    createfile(filename)


if __name__ == "__main__":
        main()

