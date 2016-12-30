# EMORY_CS450

System programming / CS450 in Emory University

All program written in C.

Taught by Prof. Ken Mandelburg

#WARNING:

#DO NOT COPY THE CODE AND SUBMIT AS YOUR OWN WORK!  CONSULT YOUR HONOR CODE#

#Proj 1: Goldbach [using bitarray]

Command line gives an int as upper limit. Finds primes up to the limit and store in bitarray. Then input an int and find goldbach decompositions [in = prime1 + prime2;prime1<=prime2]. Gives number of solutions and largest prime1.


#Proj 2: myar

implement ar in linux; myar [option] [arfile] {file1,file2...}

option:

q: quickly append all

A: append all files in the same dir modified last hour / not in original ar

x: extract

d: delete

t/v: print a summary of the file. t for short version; v as vt in ar gives verbose version.

#Proj 3:word count/sort using folk/pipe subroutine

Folk several process and use pipe to communicate:

  a. take in a text from STDIN, find words, output to pipe b1 and b2 alternatively. Alphabet(A-Z,a-z) only, cap 30 char per word, each word a new line
  
  b1./b2. take input from pipe from a. use /bin/sort to sort and output to pipe connecting to c.
  
  c. merge and count each word from b1/b2. Output to STDOUT

#Proj 4:finding perfect number, multi-process, using shared memory/message queue/signal

  manage.c  :create a shared memory segment, manage all compute instance, kill them properly when required. Only one instance of manage allowed.
  
  compute.c :compute consecutive integers from given number if it is perfect. check shared memory and skip checked. store result in shared memory. multiple instance (up to 20) allowed.
  
  report.c  :report the status and perfect number found. if use -k switch, kill manage and manage kill all computes.


