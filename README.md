# random-generator

This project is a random graph generator.

## Requirements

You need to install all the following packages

* Igraph 0.7.1
* CppUnit 1.14.0
* CMake 3.2 and newer
* C++14 capable compiler
* Doxygen for docs (*Graphviz for more graphs in docs, PlantUML for more UML diagrams*, PlantUML needs java)

you can just run the following command:

```
make install
```

## Running the program

For compiling the program run 

```
make prog
```

And to run simulation read the usage section.

## Usage 

There are several ways to launch the program:

* 1- Run the program with an input file that contains the network topology.


```
./prog -i Topologies/topo.txt
```
* 2- Run the program with multiple simulation parameters.


```
./prog -g ER -n 30 -m 0 -p 0.20 -a 2 -f 0.10 -s 3 -r 10
```

* 3- Run the program with multiple simulation parameters and export the network topology generated by the program.


```
./prog -g BA -n 50 -m 5 -p 1 -a 3 -f 0.20 -s 5 -r 1 -o Topologies/topo.txt
```

The meaning of each program option:

* g : generator type (BA: Barabasi-Albert, ER: Erdos_Renyi)
* n : number of routers of the network (non negative)
* m : number of links for Barabasi-Albert generator (non negative)
* p : connection probability for the graph generator (between 0. and 1.)
* a : number of protocols of the network (non negative)
* f : adaptation function probability for routers (between 0. and 1.)
* s : maximum stack of protocols (non negative)
* r : number of runs (non-zero and non negative)
* i : input_file topology (ex:Topologies/topo.txt)
* o : output file topology (ex: Topologies/topo.txt)
* h : help

## Unit Tests

Use the following command to run the automated unit tests for this project:

```
make test
./test
```

## Documentation

Use the following command to run the automated documentation for this project:

```
make doc
./doc
```
Documentation will be in Doc/doc/index.html


## Built With

* [Igraph](https://igraph.org/c/) - Used to generate graphs.
* [CppUnitTest](https://people.freedesktop.org/~mmohrhard/cppunit/index.html) - The unit testing framework used.
* [Doxygen](https://github.com/kracejic/EmptyDoxygenCMake) - Used to generate documentation.

## Version

1.0

## Author

* **Noureddine Mouhoub** - (*GitHub:* [NoureddineMouhoub](https://github.com/nmouhoub))