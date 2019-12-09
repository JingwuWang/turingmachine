; This example program checks if the input string is a binary palindrome.
; Input: a string of 0's and 1's, eg '1001001'

; the finite set of states
#Q = {0,cp1,cp2,back1,back2,add1,add2,accept,accept0,accept2,accept3,accept4,halt_accept,reject,reject0,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {0}

; the complete set of tape symbols
#G = {0,1,_,T,r,u,e,F,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 3 

; the transition functions

; State 0: begin
0 *** *00 *** cp1

; State cp1: check if tape 1st is equal to tape 2nd
cp1 00* 00* rr* cp1
cp1 _0* _0* l** reject
cp1 0_* 0_* *l* back1
cp1 __* __* ll* accept

; State cp2: check if tape 1st is equal to tape 3rd
cp2 0*0 0*0 r*r cp2
cp2 _*0 _*0 l** reject
cp2 0*_ 0*_ **l back3
cp2 _*_ _*_ l*l accept

; State back1: init
back1 000 000 lll back1
back1 0*0 0*0 l*l back1
back1 00* 00* ll* back1
back1 *00 *00 *ll back1
back1 **0 **0 **l back1
back1 0** 0** l** back1
back1 *0* *0* *l* back1
back1 ___ ___ rrr add1

; State back2: init
back2 000 000 lll back2
back2 0*0 0*0 l*l back2
back2 00* 00* ll* back2
back2 *00 *00 *ll back2
back2 **0 **0 **l back2
back2 0** 0** l** back2
back2 *0* *0* *l* back2
back2 ___ ___ rrr cp2

; State back3: init
back3 000 000 lll back3
back3 0*0 0*0 l*l back3
back3 00* 00* ll* back3
back3 *00 *00 *ll back3
back3 **0 **0 **l back3
back3 0** 0** l** back3
back3 *0* *0* *l* back3
back3 ___ ___ rrr add2

; State back4: init
back4 000 000 lll back4
back4 0*0 0*0 l*l back4
back4 00* 00* ll* back4
back4 *00 *00 *ll back4
back4 **0 **0 **l back4
back4 0** 0** l** back4
back4 *0* *0* *l* back4
back4 ___ ___ rrr cp1

; State add1: add tape 2nd to tape 3rd
add1 **0 **0 **r add1
add1 *0_ **0 *rr add1
add1 *__ *__ *ll back2

; State add2: add tape 3rd to tape 2nd
add2 *0* *0* *r* add2
add2 *_0 *0* *rr add2
add2 *__ *__ *ll back4

accept *** *** rrr accept
accept __* __* **r accept
accept _*_ _*_ *r* accept
accept *__ *__ r** accept
accept ___ ___ lll accept0
accept0 *** ___ lll accept0
accept0 ___ *** *** accept1
accept1 ___ T__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

reject *** *** rrr reject
reject __* __* **r reject
reject _*_ _*_ *r* reject
reject *__ *__ r** reject
reject ___ ___ lll reject0
reject0 *** ___ lll reject0
reject0 ___ *** *** reject1
reject1 ___ F__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject