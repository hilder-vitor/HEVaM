# HEVaM: Homomorphic Encryption for Vector And Matrix arithmetic

The code in the the branch acns2020 is the C++ implementation used to run 
the tests and obtain the pratical results presented in the paper
Efficient AGCD-based homomorphic encryption for matrix and vector arithmetic,
by [Hilder Vitor Lima Pereira](https://hilder-vitor.github.io/),
at the [18th International Conference on Applied Cryptography and Network Security (ACNS2020)](https://sites.google.com/di.uniroma1.it/acns2020/).

*Dependencies*

- GNU GMP (https://gmplib.org/)

- NTL (https://shoup.net/ntl/)

*Compiling*

Just run the command make.

*Running the tests*

Just run the bash script execute_tests.sh, which will run the tests and output the results in a directory named run_times.

Please, notice that running all the tests at once will take a lot of time, thus, you are encouraged to edit this script to select the tests you want.
