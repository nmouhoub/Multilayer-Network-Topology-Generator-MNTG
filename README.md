# MNTG: A New Flexible Multilayer Network Topology Generator

This project is a multilayer network topology generator

## Requirements

You need to install all the following packages

* Igraph 0.7.1
* CMake 3.2 and newer
* C++17 capable compiler
* Doxygen for docs (*Graphviz for more graphs in docs, PlantUML for more UML diagrams*, PlantUML needs java)


## Running the program

For compiling the program run 

```
make prog
```

And to run simulation read the usage section.

## Usage 

Run the program with an input file that contains the network topology.


```
./prog parameters_file output_file input_file_1 input_file_2 ... input_file_k
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
* [Doxygen](https://github.com/kracejic/EmptyDoxygenCMake) - Used to generate documentation.

## Version

1.0

## Author

* **Noureddine Mouhoub** - (*GitHub:* [NoureddineMouhoub](https://github.com/nmouhoub))
