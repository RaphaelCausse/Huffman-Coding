[![OS](https://img.shields.io/badge/os-linux-blue.svg)](https://shields.io/)
[![Status](https://img.shields.io/badge/status-completed-success.svg)](https://shields.io/)

# HUFFMAN CODING PROJECT

Implementation of Huffman coding algorithm in C.<br>
Compressing files and decompressing using the Huffman algorithm.

## INSTALLATION

Make sure you have installed **Git**. If not :
* Linux : https://youtu.be/PLQQ3tJwBJg<br>
* Windows : https://youtu.be/2j7fD92g-gE<br>

**Clone** this repository on your desktop :
```bash
$   cd Desktop
$   git clone https://github.com/RaphaelCausse/Huffman_Coding.git
```

## COMPILATION

**Move** to the cloned folder :
```bash
$   cd Huffman_Coding
```
**Compile** the project using my Makefile :
```bash
$   make install
```

## EXECUTION

To **compress** a file, run :
```bash
$   huffman -c <file> <encoded.hff>
```
To **decompress** a file (.hff), run :
```bash
$   huffman -d <encoded.hff> <decoded>
```
**_NOTE:_**<br>
`file`,`encoded.hff`,`decoded` are example files.

## FEATURES

To get **information and help**, run :
```bash
$   huffman --help
```
To **clean** the entire project directory, run :
```bash
$   make clean
```
To **visualize** the binary file, you can use "Hex Editor" extension on Visual Studio Code from Microsoft.

## TESTS

You **can test** the project with the files in the "tests" subdirectory.

## AUTHORS

Melvyn MUNOZ and Raphael CAUSSE, from CY TECH.<br>
11/2021, developped on Linux Ubuntu, Visual Studio Code.