# Multilayer Network Topology Generator (MNTG)

This project is a multilayer network topology generator called MNTG and written in C++.

## Requirements

You will need to have or install all the following software packages:

* C++17 capable compiler
* make 4.0 or newer
* [igraph](https://igraph.org/c/) 0.8.5 or newer
* (optional) [Doxygen](https://www.doxygen.nl/) for docs
* (optional) [Graphviz](https://graphviz.org/) for more graphs in docs
* (optional) [PlantUML](https://plantuml.com/) for more UML diagrams (PlantUML needs Java)

## Building the program

For building the program, just type the following command in the `random-generator` directory:

```
make mntg
```

## Usage 

Run the program with a parameters file and one or more input files that contains network topologies.

```
./mntg parameters_file output_file input_file_1 input_file_2 ... input_file_k

```

## Documentation
<!---
Use the following command to run the automated documentation for this project:

```
make doc
./doc
```

-->

Source code documentation is available in random-generator/doc/html/index.html

Documentation is available on the [Wiki](https://gitub.u-bordeaux.fr/hera/random-generator/-/wikis/home).

## Licence

GNU LGPL version 3.

## Version

1.0

## Author

* **Noureddine Mouhoub** - (*GitHub:* [NoureddineMouhoub](https://github.com/nmouhoub))
