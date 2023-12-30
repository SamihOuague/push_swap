# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/30 05:11:51 by  souaguen         #+#    #+#              #
#    Updated: 2023/12/30 08:52:42 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash
run_test () {
	x=0
	failed=0
	passed=0
	max=0
	min=10000
	avg=0
	while [[ $x -lt 100 ]]
	do
		ARG=$(python3 -c "import random; print(random.sample(range($1), $1))" | sed -E -e "s/,|\]|\[//g")
		PROG=$(./push_swap $ARG)
		if [[ "$PROG" ]]; then
			TEST=$(echo -e "$PROG" | ./checker_linux $ARG)
			if [[ "$TEST" == "$(echo -e "$PROG" | ./checker $ARG)" ]]; then
				passed=$(( $passed + 1 ))
			else
				failed=$(( $failed + 1 ))
			fi
		else
			TEST=$(echo -n "" | ./checker_linux $ARG)
			if [[ "$TEST" == "$(echo -n "" | ./checker $ARG)" ]]; then
	                        passed=$(( $passed + 1 ))
	                else
	                        failed=$(( $failed + 1 ))
	                fi
		fi
		clear	
		echo -e "\e[95m################ $1 NUMBERS TESTS ###################\e[39m"
		echo
		echo -n "["
		i=0
		while [[ $i -lt 100 ]]
		do
			if [[ $i -lt $x ]]; then
				echo -n "====="
			else
				echo -n "     "
			fi
			i=$(( $i + 10 ))
		done
		echo "]"
		echo
		echo -e "\e[32mPASSED : $passed/100\e[31m"
		echo -e "FAILED : $failed/100\e[39m"
		if [[ $(echo -n "$PROG" | wc -l) -lt $min ]]; then
			min=$(echo -n "$PROG" | wc -l)
		elif [[ $(echo "$PROG" | wc -l) -gt $max ]]; then
			max=$(echo "$PROG" | wc -l)
		fi
		avg=$(( $avg + $(echo -en "$PROG" | wc -l) ))
		echo "#BEST CASE => $min"
		echo "#WORST CASE => $max"
		echo "#AVERAGE CASE => $(( $avg / $(( $x + 1 )) ))"
		x=$(( $x + 1 ))
	done
}

run_test 3
read -p "Press any to continue ... "
run_test 5
read -p "Press any to continue ... "
run_test 100
read -p "Press any to continue ... "
run_test 500

read -p "Press any to continue ... " 
checker_test() {
	x=0
	passed=0
	failed=0
	while [[ $x -lt 100 ]]
	do
		ARG=$(python3 -c 'import random; print([("ra", "rz", "rb", "rra", "rrr", "sa", "sb", "zz", "ss", "pa", "pb", "rrb")[x % 12] for x in random.sample(range(12), 3)])' | sed -E -e "s/,|\]|\[|'//g" | tr " " "\n")
		NUMBER=$(python3 -c "import random; print(random.sample(range(5), 5))" | sed -E -e "s/,|\]|\[//g")
		
		TEST1=$(echo "$ARG" | ./checker $NUMBER)
		TEST2=$(echo "$ARG" | ./checker_linux $NUMBER)
		if [[ $TEST1 == $TEST2 ]]; then
			passed=$(( $passed + 1 ))
		else
			failed=$(( $failed + 1 ))
		fi
		clear	
		echo -e "\e[95m################ CHECKER ERROR & KO TESTS ###################\e[39m"
		echo
		echo -n "["
		i=0
		while [[ $i -lt 100 ]]
		do
			if [[ $i -lt $x ]]; then
				echo -n "====="
			else
				echo -n "     "
			fi
			i=$(( $i + 10 ))
		done
		echo "]"
		echo
		echo -e "\e[32mPASSED : $passed/100\e[31m"
		echo -e "FAILED : $failed/100\e[39m"
		x=$(( $x + 1 ))
	done
}
checker_test
