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

test "PINA: 0x00 => PORTC: 7, state: Wait"
set state = Start
setPINA 0x00
continue 2
expectPORTC 7
expect state Wait
checkResult


#increment once 
test "PINA: 0x01 => PORTC: 8, state: incHold"
set state = Start
setPINA 0x01
continue 2
expectPORTC 8
expect state incHold
checkResult


#increment once AGAIN FOR AUTOGRADER 
test "AUTOGRADER TEST: PINA: 0x01 => PORTC: 8, state: incHold"
set state = incHold
setPINA 0x01
continue 2
expectPORTC 8
expect state incHold
checkResult





#increment twice 
test "PINA: 0x01 (PA0), 0x00 (!PA0), 0x01(PA0) => PORTC: 9, state: incHold"
set state = Start
setPINA 0x01
continue 2
setPINA 0x00 
continue 2
setPINA 0x01
continue 2
expectPORTC 9
expect state incHold
checkResult


#max value check 
test "PORTC = 9, PINA: => PORTC: 9, state: Wait"
set Tick::tmpC = 9
set state = Wait  
setPINA 0x01
continue 2
setPINA 0x00 
continue 2
expectPORTC 9
expect state Wait
checkResult


#reset check 
test "PINA: 0x03 => PORTC: 0, state: reset"
set state = Start
setPINA 0x03
continue 2
expectPORTC 0
expect state reset
checkResult


#0 check 
test "PORTC = 1, PINA: 0x02, 0x00, 0x02  => PORTC: 0, state: decHold"
set Tick::tmpC = 1
set state = Wait
setPINA 0x02
continue 2
setPINA 0x00
continue 2
setPINA 0x02
continue 2

expectPORTC 0
expect state decHold
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
