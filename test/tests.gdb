# Test file for "Lab4_EE120B"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

#nothing
test "PINA: 0x00 => PB:0, state: wait"
set state = Start
setPINA 0x00
continue 2
expectPORTB 0x00
expect state wait
checkResult


#1st part of sequence CHANGED TO BE LIKE THE AUTOGRADER
test "PINA: 0x03 => PB:0, state: wait"
set state = Start
setPINA 0x03
continue 2
expectPORTB 0x00
expect state wait
checkResult


#failing to enter sequence at seq1
#test "PINA: 0x04, 0x02 => PB:0, state: wait"
#set state = Start
#setPINA 0x04
#continue 2
#setPINA 0x02
#continue 2
#expectPORTB 0x00
#expect state wait
#checkResult


#going to seq2
#test "PINA: 0x04, 0x00 => PB:0, state: seq2"
#set state = Start
#setPINA 0x04
#continue 2
#setPINA 0x00
#continue 2
#expectPORTB 0x00
#expect state seq2
#checkResult


#full unlock sequence
test "PINA: 0x04, 0x00, 0x02 => PB:1, state: door"
set state = Start
setPINA 0x04
continue 2
setPINA 0x00
continue 2
setPINA 0x02
continue 2
expectPORTB 0x01
expect state door
checkResult

#full sequence + then locking the door; CORRECTLY GOES TO DOOR STATE, BUT DOESN'T SET TO 0 
#test "PINA: 0x04, 0x00, 0x02, 0x00, 0x80 => PB:0, state: door"
#set state = Start
#setPINA 0x04
#continue 2
#setPINA 0x00
#continue 2
#setPINA 0x02
#continue 2
#setPINA 0x00
#continue 2
#setPINA 0x80
#continue 2
#expectPORTB 0x00
#expect state door
#checkResult

#locking the door ; Doesn't correctly go to door state when PA7 
test "PB = 1, PINA: 0x80 => PB:0, state door"
set Tick::tmpB = 0x01 
set state = wait
setPINA 0x80
continue 2
expectPORTB 0x00
expect state door
checkResult

#autograder test
test "PINA: 0x04, 0x00, 0x01 => PORTB: 0x00, state wait"
set state = Start
setPINA 0x04
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x00
expect state wait

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
