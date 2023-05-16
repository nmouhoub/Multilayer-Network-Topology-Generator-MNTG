# Multilayer Network Topology Generator (MNTG)

This project is a multilayer network topology generator called MNTG and written in C++.


## Requirements

You will need to have or install all the following packages:

* CMake 3.2 or newer
* C++17 capable compiler
* Doxygen for docs
* (optional) Graphviz for more graphs in docs
* (optional) PlantUML for more UML diagrams (PlantUML needs Java)

## Building the program

For building the program, just type:

```
make mntg
```

## Usage 

Run the program with an input file that contains the network topology.

```
./mntg parameters_file output_file input_file_1 input_file_2 ... input_file_k

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

## Licence

GNU LGPL version 3.

## Version

1.0

## Author

* **Noureddine Mouhoub** - (*GitHub:* [NoureddineMouhoub](https://github.com/nmouhoub))