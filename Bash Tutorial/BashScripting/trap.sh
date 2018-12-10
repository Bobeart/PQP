#/bin/bash
# bash trap command
trap bashtrap INT
# bash clear screen command
clear;
# bash trap function is executed whe CTRL-C is pressed:
# bash prints message => Executing bash trap subroutine!
bashtrap(){
	echo  "CTRL+C Detected !...executing bash trap!"
}
# for loop from 1/10 to 10/10
for a in `seq 1 10`; do
	echo "$a/10 to Exit."
	sleep 1;
done
echo "EXit Bash Trap Example!!!"
