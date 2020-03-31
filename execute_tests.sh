#!/bin/bash

# create directory run_times if it does not exist yet
[ -d run_times ] || mkdir run_times

for he_type in 'noisyx0'
do

	for TEST in 'test_nfa' 'test_vectors' 'test_matrices'
	do
		echo $he_type
		echo $TEST
		for lambda in 80 100
		do
			echo "lambda = $lambda"
			sed -i'.bkp' "s/long lambda = [0-9]*; \/\/ security level/long lambda = $lambda; \/\/ security level/" Main.cpp;
			make
			time ./a.out $TEST > "run_times/times-lambda$lambda-$TEST-$he_type.txt";
		done
	done

	TEST='test_naive_bayes_classifier'
	echo $TEST
	for lambda in 80 100
	do
		echo "lambda = $lambda"
		sed -i'.bkp' "s/long lambda = [0-9]*; \/\/ security level/long lambda = $lambda; \/\/ security level/" Main.cpp;
		make
		time ./a.out $TEST > "run_times/times-lambda$lambda-$TEST-$he_type.txt";
	done
done

