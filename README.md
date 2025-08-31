# Gopher Parser

A lightweight C utility that parses Gopher protocol gophermap files and converts them to JSON format.

## What is Gopher?

The Gopher protocol is a communications protocol designed for distributing, searching, and retrieving documents in Internet Protocol networks. Gophermaps are menu files that describe the structure and content of a Gopher server.

## Features

- Parses standard gophermap format with tab-separated fields
- Outputs clean JSON array of objects
- Handles all gopher item types (files, directories, search, etc.)
- Memory-efficient processing of large gophermaps

## Usage

```bash
# Build the parser
make

# Parse a gophermap file
./gopherparser < your-gophermap-file

# Test with included sample
./gopherparser < test-gophermap
```

## Gophermap Format

The parser expects standard gophermap format:
```
[item_type][display_string][TAB][selector][TAB][host][TAB][port]
```

## Output Format

The parser outputs a JSON array of objects with the following structure:
```json
[
  {
    "itemType": "1",
    "displayString": "Example Directory",
    "selector": "/example",
    "host": "gopher.example.com",
    "port": "70"
  }
]
```

## Building

Requires a C compiler (tested with cc/gcc). Simply run:
```bash
make
```

To clean build artifacts:
```bash
make clean
```
