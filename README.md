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

Configure the general parameters in a ".config" parameters file.

```
[net_model]: the network generation model "mono_random" or "multi_random".  
[load_graphs]: the number of loaded graphs, 0 otherwise.
[nb_protocols]: the number of protocols available in the generated network.
[seed_nb]: the seed number used in all random generations.
[nb_nodes_g_0, nb_nodes_g_1, ...] : the size of each generated graph when the graphs are generated and not loaded.
[nb_nodes_p_1, nb_nodes_p_2, ...] : the number of nodes according to the number of communicated protocols when the multi_random mode is used.

```

Configure the following parameters of adaptation functions.  

```
[retransmission_cost, conversion_cost, encapsulation_cost, decapsulation_cost]: the cost of each adaptation functions.
[p_retransmission, p_conversion, p_encapsulation, p_decapsulation]: the probability of availability of each adaptation function per node.

```

Configure the following parameters for the random graph generation.

```
[graph_model]: the graph generator model "barabasi_albert" or "erdos_renyi" or "watts_strogatz".
[m_attachement, p_attachement]: the parameters of barabasi_albert generator.
[p_connection]: the parameters of erdos_renyi generator.
[k_mean_degree, p_beta]: the parameters of watts_strogatz generator.

```

Run the program with a parameters file, an output_file and one or more input files that contains network graphs (if you want to load one or more graphs).

```
./mntg <parameters_file> <output_file> [<input_file_1> <input_file_2> ... <input_file_k>]

```

## Examples

Sample command line for generating a mono-random multilayer network:

```
./mntg examples/mono_random.config examples/mono_random.mntg
```

Sample command lines for generating a mono-random multilayer network with an input network graph:

```
./mntg examples/mono_random.config examples/mono_random.mntg examples/graph_90.net
```

```
./mntg examples/mono_random.config examples/mono_random.mntg examples/weighted_graph_90.net
```

Sample command line for generating a multi-random multilayer network:

```
./mntg examples/multi_random.config examples/multi_random.mntg
```

Sample command line for generating a multi-random multilayer network with two input network graphs:

```
./mntg examples/multi_random.config examples/multi_random.mntg examples/graph_90.net examples/graph_260.net
```

## Documentation
<!---
Use the following command to run the automated documentation for this project:

```
make doc
./doc
```

-->

Source code documentation is available in `random-generator/doc/html/index.html`.

Documentation is available on the [Wiki](https://gitub.u-bordeaux.fr/hera/random-generator/-/wikis/home).

## Licence

GNU LGPL version 3.

## Version

1.0

## Author

* **Noureddine Mouhoub** - (*GitHub:* [NoureddineMouhoub](https://github.com/nmouhoub))
