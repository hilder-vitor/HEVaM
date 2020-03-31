
#NTL_FLAGS=-I/home/username/ntl/include/ -L/home/username/ntl/lib -lntl
NTL_FLAGS=-lntl
GMP_FLAGS=-lgmp

all: Main naive_bayes_classifier

utils.o: utils.h utils.cpp
	g++ utils.h utils.cpp -c -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

HENoisyX0.o: HENoisyX0.h HENoisyX0.cpp utils.o
	g++ HENoisyX0.cpp HENoisyX0.h -c -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

AutomatonLn.o: AutomatonLn.h AutomatonLn.cpp
	g++ AutomatonLn.cpp AutomatonLn.h -c -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

EncryptedAutomatonLn.o:EncryptedAutomatonLn.h EncryptedAutomatonLn.cpp
	g++ EncryptedAutomatonLn.cpp EncryptedAutomatonLn.h -c -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

HomomorphicNaiveBayesClassifier.o: HomomorphicNaiveBayesClassifier.h HomomorphicNaiveBayesClassifier.cpp
	g++ HomomorphicNaiveBayesClassifier.cpp HomomorphicNaiveBayesClassifier.h -c -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

ProbabilitiesDataset.o: ProbabilitiesDataset.h ProbabilitiesDataset.cpp
	g++ ProbabilitiesDataset.cpp ProbabilitiesDataset.h -c -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

Main: Main.cpp HENoisyX0.o AutomatonLn.o EncryptedAutomatonLn.o HomomorphicNaiveBayesClassifier.o ProbabilitiesDataset.o utils.o
	g++ Main.cpp *.o -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

# Naive Bayes Classifier in clear
naive_bayes_classifier: naive_bayes_classifier.cpp
	g++ naive_bayes_classifier.cpp -o naive_bayes_classifier -g -O2 -std=c++11 -pthread -march=native $(NTL_FLAGS) $(GMP_FLAGS) -lm

clean:
	rm *.o *.gch a.out naive_bayes_classifier
