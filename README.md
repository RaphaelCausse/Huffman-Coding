[![OS](https://img.shields.io/badge/os-linux-blue.svg)](https://shields.io/)
[![Status](https://img.shields.io/badge/status-completed-success.svg)](https://shields.io/)

# HUFFMAN CODING PROJECT

Implementation of Huffman coding algorithm in C.<br>
Compressing files and decompressing using the Huffman algorithm.
<br><br>

## INSTALLATION

**Clone** this repository:
```
git clone https://github.com/RaphaelCausse/Huffman_Coding.git
```
**Move** to the cloned folder :
```
cd Huffman_Coding
```
<br>

## COMPILATION

**Compile** the project using my Makefile :
```
make
```
<br>

## EXECUTION

To **compress** a file, run :
```
./bin/huffman -c <file> <encoded.hff>
```
To **decompress** a file (.hff), run :
```
./bin/huffman -d <encoded.hff> <decoded>
```
**_NOTE:_**<br>
`file`, `encoded.hff`, `decoded` are example files.
<br><br>

## FEATURES

**Help** message :
```
./bin/huffman -h
```
To **clean** the entire project directory, run :
```
make clean
```
To **visualize** the binary file, you can use "Hex Editor" extension on Visual Studio Code from Microsoft.
<br><br>

## TESTS

You **can test** the project with the files in the "tests" subdirectory.
<br><br>

## AUTHORS

Melvyn MUNOZ and Raphael CAUSSE, from CY TECH.<br>
11/2021, developped on Linux Ubuntu and Manjaro, Visual Studio Code.