# SIC Assembler & Relocating Loader

A two-pass SIC (Simplified Instructional Computer) assembler and relocating loader implemented in C as part of a Systems Programming course at the University of North Florida (UNF).

## Overview

This project implements core concepts in systems programming including assembly language processing, symbol table management, object code generation, and program relocation.

## Features

### Two-Pass Assembler
- **Pass 1:** Parses assembly source code, builds a symbol table using linked lists, assigns memory addresses, and detects duplicate symbols
- **Pass 2:** Generates object code by translating instructions into machine code using opcode tables and produces H/T/M/E records

### Relocating Loader
- Reads object files produced by the assembler
- Applies relocation via modification records
- Loads programs into memory at addresses other than their origin

## How It Works

1. Input: SIC assembly source file
2. Pass 1 constructs the symbol table and calculates addresses
3. Pass 2 generates the object program with Header, Text, Modification, and End records
4. The relocating loader reads the object program and loads it at the correct memory address

## Usage

```bash
make
./loader <object_file>
```

## Technologies

- C
- Linked Lists (symbol table)
- Systems Programming
- SIC Architecture

## Project Structure

```
loader.h              - Header file with data structures and function prototypes
project5loader.c      - Relocating loader implementation
Makefile              - Build configuration
```
