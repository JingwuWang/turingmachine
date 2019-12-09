; This example program checks if the input string is a binary palindrome.
; Input: a string of 0's and 1's, eg '1001001'

; the finite set of states
#Q = {0,right_half,left_together,copy,left2,check,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {0,1}

; the complete set of tape symbols
#G = {0,1,_,T,r,u,e,F,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the number of tapes
#N = 2 

; the transition functions

; State 0: begin
0 0_ 0_ r* right_half
0 1_ 1_ r* right_half
0 __ __ ll left_together

; State right_half: tape2 go right to the half of tape1 goes
right_half 0_ 0a rr 0
right_half 1_ 1a rr 0
right_half *_ *a *r reject

; State left_together: move to the left side both
left_together __ __ rr copy
left_together 0a 0a ll left_together
left_together 1a 1a ll left_together
left_together 0_ 0_ l* left_together
left_together 1_ 1_ l* left_together

; State copy: copy the left half of tape1 to tape2
copy 0a _0 rr copy
copy 1a _1 rr copy
copy 0_ 0_ *l left2
copy 1_ 1_ *l left2

; State left2: tape2 goes to the 
; left side 
left2 00 00 *l left2
left2 01 01 *l left2
left2 10 10 *l left2
left2 11 11 *l left2
left2 0_ 0_ *r check
left2 1_ 1_ *r check

; State check: check whetherequal
check 00 __ rr check
check 11 __ rr check
check __ __ ** accept
check ** ** ** reject

accept __ T_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

reject ** ** rr reject
reject __ ** ll reject1
reject1 ** __ ll reject1
reject1 __ F_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject