
# Bugpuzzle

#
# 

### Abstract
This project finds solutions to the 3D Squares bug puzzle. The program uses a genetic algorithm with random mutation and is written in C++.

### Introduction
The 3D Squares bug puzzle contains a square board with nine pieces, in three rows of three. Each piece has either the head of a bug, or a corresponding tail end, on each of it's four sides. The puzzle is solved when every bug, excluding the pieces facing outside of the board, is made whole. Finding the solution involves rearranging and rotating pieces.

A genetic algorithm is being used here to apply the concept of evolutionary learning with genomes and fitness evaluation to find solutions to the puzzle. A population, usually with thousands of individuals with differing genomes, represents one generation. 

### Problem Definition
The 3D Squares bug puzzle is solved when every two adjacent piece sides align with the correct head/tail bug combination. Among the nine pieces, there are twelve bugs made whole when the puzzle is solved correctly, with twelve bug halves facing away from the board. A puzzle board, solved or not, can be represented by a set of nine integers, with each integer representing the location [0, 9) of each piece in row-major order. Similarly, the other set represents the orientation [0,3) of each bug, starting with zero being a northward facing orientation, and moving clockwise ending with three being a westward facing orientation. Using this board definition, a description of each piece with their four bug parts must be determined. This description can be found in "tile.h" as the static variable "bugs". Each piece is encoded in accordance with the attached board image.

The board definition can also be represented as a string of 54 chromosomes, with each chromosome being a boolean value. The first aforementioned set contains nine integers in the range [0, 9) which can be stored in four boolean bits. Therefore the first 36 chromosomes correspond to four chromosomes for each of the nine piece. The second set containing nine integers in the range [0, 4) can be stored in two boolean bits, so the last 18 chromosomes correspond to two chromosomes for each of the nine pieces. These 54 chromosomes, together being a genome, describe one particular board orientation. 

### Methods
The genetic algorithm cycles many times, with each cycle evolving a new generation of individuals. One individual, defined by one genome, represents a particular board orientation. The fitness of this indivdual is defined as how close this individual is to the goal state of being a solved puzzle board, and is evaluated using a fitness function. 

Each cycle of the algorithm is composed of two parts. The first is to generate new genomes for each individual, combining parent genomes using a crossover function. Genomes are also mutated, with each chromosome having a fixed chance of it's boolean value being flipped. Then, the fitness of each individual is calculated using the fitness function. Last, the most fit individuals of this generation are selected to become the parents of the next generation, which leads to the next cycle. The algorithm cycles until an individual reaches the goal state, or the maximum allowed number of generations is reached. 

For each population generation, a priority queue is used to store each board/genome. This allows for efficient selection of the most fit genomes of any population. Additionally, memory usage is reduced by extensive use of pointers, where copying values are avoided; instead, objects are passed by reference as much as possible.

The crossover functions used does not randomize crossover points. Instead, child genomes result from evenly splitting parent genomes. For example, using two parents, the child's first 27 chromosomes come from the first half of the first parent's genome, and the child's last 27 chromosomes come from the second half of the second parent's genome.

The fitness function evalues a board on a linear scale from 0 to 24, where 24 is the maximum number of matches and the goal state. The fitness of a board is calculated by summing each tile's matches, checking every adjacent tile for matching bug parts, while taking into account the orientation of the tile (facing North, East, South, or West in respect to the default configuration).

### Tweaking
Five variables in this algorithm can be played with.  
	PARENT_COUNT: the number of parents to use for the crossover function. Typically this is two, but one or even up to 54 can be used. The crossover function divides genes evenly between parents (there is no randomly selected cutoff lie as in other genetic algorithms).
	MUTATION_PERCENT: The percent chance of any one boolean chromosome to be flipped, or to be changed from 0 to 1 or vice versa.
	POPULATION_SIZE: The number of individuals generated for each population.
	BREEDING_SELECTION: The percent of top individuals to be selected for breeding the next generation, in the range [1, 100].
	TESTS: How many populations the program will generate. Supplying 1 will only run the algorithm once. Supplying, ie. 100, the algorithm will find up to 100 solutions. Give the MAX_GENS option, the algorithm is not guaranteed to find a solution for every population.
	MAX_GENS: The maximum number of generations to be allowed for a population to reach the goal state. If this number of generations is reached and no solution has been found, the algorithm returns with no solution.
	
Different combinations of these variables result in varying execution times and generation counts before the goal state is reached. Some combinations will leave the program running seemingly forever, although as long as there is a mutation chance, any combination can theoretically yield a solution. 

### Results
This program is able to find the unique solution to the puzzle in a few seconds, running on a debian virtual machine with an i7 processor and 3GB of memory. Some times, the algorithm will find a genome that matches all but one tile, such as with the genomes:
	7,1,2,5,6,3,9,4,8,|0,0,0,2,0,0,0,0,3, or
	1,2,9,6,3,8,7,4,5,|0,0,0,2,2,0,0,0,0,
	In this case, based off of the selective breeding, the algorithm will hover around this incorrect solution, unable to mutate to a different solution because such a huge genome change would drastically, albeit temporarily, decrease the fitness score.
	
The program can be compiled with the following command:

``` g++ stats.cpp -o stats.o ```
and then run with:
```	./stats.o ```
	One can see the command line options with the command "./stats.o o" and optionally supply them in a manner such as,
	"./stats.o 2 30 1000 1 5 400"
	Note, the program will accept either all or no parameters.

In general, using a parent count of 2 has been most successful. Populations less than 1000 in size tend to be too small to yield enough fit individuals, and mutation percents around 10 work well. Optimally, increasing mutation percent or increasing population size should be combined with more selective breeding, to decrease the chance of parents evolving away from the goal state.
	
One particularly effective combination of options is to use 2 parents, a mutation chance of 8%, a population size of 20,000, a breeding selection of 1%, and 30 maximum generations per test. This can be run with the following command:
```./stats.o 2 8 20000 1 10 30```
These parameters typically will produce a solution within a few seconds.

The program prints some relevent statistics, including average generations to find a solution and number of unique solutions. Using the option "g" at the end of the program inputs filters all output except unique genomes.

Chromosome solutions are printed in their integer form. An entire genome will be printed, ie the puzzle solution:
	5,2,9,4,3,8,7,1,6,|0,0,0,0,0,0,0,0,0,
This format corresponds to the aforementioned board definition, with two sets of nine integers, with the exception that bug IDs are 1-based with the range [1, 9]: bug IDs are incremented upon printing for convenience to match up with the IDs in the picture. The printed genome can be seen as the solution as they are the IDs in row-major order as in the picture solution, all with the default orientation.


### Conclusions and Discussion
Using the suggested program options, the solution will be found in about 10 generations. Otherwise, the algorithm will float for dozens or hundreds of generations around an incorrect solution. Therefore, an option was added to specify the maximum number of generations before ending evaluation of a population. Using this option and running multiple tests, the algorithm comes upon the solution much faster than by allowing a population to go through hundreds of generations -- after all, it takes only a few generations to solve 90% of the puzzle; hundreds of generations become redundant.

Using a larger population seems to be more successful. This allows the selective breeding to become more effective by having a more, better genomes for each generation.

A priority queue is used to find the best genomes in a population. This data structure is optimal for the algorithm, allowing O(logn) insertion and deletion operations, while eliminating the need to search through populations for the best genomes. In particular, the priority queue allows to algorithm to scale better with increased population sizes.
		

### References
The wikipedia page for genetic algorithms was consulted for reference:
	https://en.wikipedia.org/wiki/Genetic_algorithm
	



