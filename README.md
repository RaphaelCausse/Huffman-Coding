[![OS](https://img.shields.io/badge/os-linux-blue.svg)](https://shields.io/)
[![Status](https://img.shields.io/badge/status-completed-success.svg)](https://shields.io/)

# HUFFMAN CODING PROJECT

Implementation of Huffman coding algorithm in C.

Compressing files and decompressing using the Huffman algorithm, priority queues and binary trees.
<br><br>

## INSTALLATION

**Clone** this repository:
```
git clone https://github.com/RaphaelCausse/Huffman-Coding.git
```
**Move** to the cloned directory :
```
cd Huffman-Coding
```
<br>

## COMPILATION

**Compile** the project using my Makefile :
```
make
```
<br>

## EXECUTION

**Compress** a file :
```
./bin/huffman -c <file> <encoded.hff>
```
**Decompress** a file (.hff), run :
```
./bin/huffman -d <encoded.hff> <decoded>
```
**_NOTE:_**<br>
`file`, `encoded.hff`, `decoded` are example files.
<br><br>

## FEATURES

Display **help** message :
```
./bin/huffman -h
```
**Clean** the entire project directory, run :
```
make clean
```
**Visualize** the binary file, you can use "Hex Editor" extension on Visual Studio Code from Microsoft.
<br><br>

## TESTS

You **can test** the project with the files in the "tests" subdirectory.
<br><br>

## AUTHORS

Melvyn MUNOZ and Raphael CAUSSE, from CY TECH.

11/2021, developped on Linux Ubuntu and Manjaro, Visual Studio Code.