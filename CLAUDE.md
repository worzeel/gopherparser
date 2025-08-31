# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a lightweight C utility that parses Gopher protocol gophermap files and converts them to JSON format. The Gopher protocol is a vintage internet protocol from the early 1990s that predates the World Wide Web. This parser handles the standard gophermap menu format used by Gopher servers.

## Development Commands

**Build the project:**
```bash
make
```

**Clean build artifacts:**
```bash
make clean
```

**Test the parser with sample data:**
```bash
./gopherparser < test-gophermap
```

**Test with custom gophermap:**
```bash
./gopherparser < your-gophermap-file
```

## Project Structure

- **gopherparser.c**: Main implementation (111 lines). Single-file parser that reads from stdin and writes JSON to stdout.
- **test-gophermap**: Sample gophermap file containing various Gopher item types for testing
- **Makefile**: Minimal build configuration using standard C compiler
- **README.md**: User-facing documentation with usage examples
- **LICENSE**: MIT license

## Architecture Details

**Input Format**: Standard gophermap format with tab-separated fields:
```
[item_type][display_string][TAB][selector][TAB][host][TAB][port]
```

**Processing Flow**:
1. Read lines from stdin using `getline()`
2. Parse each line using `strtok()` with tab/newline delimiters
3. Extract item type (first character), display string, selector, host, port
4. Output structured JSON objects in an array format

**Output Format**: JSON array of objects with fields:
- `itemType`: Single character (!, 1, i, 0, etc.)
- `displayString`: Human-readable menu text
- `selector`: Resource path/identifier  
- `host`: Server hostname
- `port`: Server port number

## Memory Management

The code uses careful dynamic memory allocation:
- `realloc()` for resizing string buffers as needed
- `strncpy()` for safe string copying with length limits
- Proper cleanup with `free()` after processing each line
- All allocated memory is freed before program exit

## Common Gopher Item Types

- `0`: Plain text file
- `1`: Directory/submenu
- `i`: Informational text (non-selectable)
- `!`: Error message
- `3`: Error indicator

## Development Notes

- Single-threaded, processes one line at a time
- Handles malformed input gracefully
- No external dependencies beyond standard C library
- Compiles with any standard C compiler (cc, gcc, clang)