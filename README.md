# Reversi AI DLL

Heuristic reversi AI implemented as a Windows native DLL

## Features

- Simple API
- Callable from C# easily
- Moderate AI Strength

## Dependencies

You may need Microsoft Visual C++ Redistributable.

- VCRUNTIME140.dll
- api-ms-win-crt-runtime-l1-1-0.dll
- KERNEL32.dll

## API

The DLL has simple API.
For instance, a board state is given, an API function returns a move you should to choose next.

### Bit Board

Bit Board is expression of a reversi board.
By Bit Board, a board state is expressed by a pair of 64-bit unsigned integer.
They each have bit flags where each players' disks are placed.
For example, an initial board of reversi is expressed like `0x0000_0008_1000_0000` and `0x0000_0010_0800_0000`.

### Functions

#### `int full_search(unsigned long long self, unsigned long long opponent)`

Returns the best move that `self` player should do by doing full search.

This can be used if the game is in its final stages.
`self` and `opponent` are Bit Board.
The returned value is a bit number expressing disk position.
The bit number is 0 to 63.

#### `int full_search_parallel(unsigned long long self, unsigned long long opponent)`

The multithreaded version of `full_search`.

It's faster than the non-multithreaded version in most cases if the CPU is good enough for parallel calculation.

#### `int heuristic_search(unsigned long long self, unsigned long long opponent, int depth)`

Returns an approximately good move that `self` player should do by doing partial search.

`self` and `opponent` are Bit Board.
`depth` is anticipation steps same as depth of recursion.
It must be positive.
The returned value is a bit number expressing disk position.
The bit number is 0 to 63.
Search time depends on depth of recursion.

#### `int heuristic_search_parallel(unsigned long long self, unsigned long long opponent, int depth)`

The multithreaded version of `heuristic_search`.

It's faster than the non-multithreaded version in most cases if the CPU is good enough for parallel calculation.

#### `int choose_move(unsigned long long self, unsigned long long opponent)`

Returns a move that `self` player should act.

This function is a wrapper of `full_search` and `heuristic_search`.
It switches between them considering search time.
`self` and `opponent` are Bit Board.
The returned value is a bit number expressing disk position.
The bit number is 0 to 63.
Search time will be less than a few seconds usually.

#### `int choose_move(unsigned long long self, unsigned long long opponent)`

The multithreaded version of `choose_move`.

Thanks to speeding up by parallel calculation, this function tries to search deeper than the non-multithreaded version.
Moreover, it switches to full search earlier.
Use this multithreaded version instead to make AI stronger.

#### `int position_to_index(int i, int j)`

Returns a bit number from horizontal index and vertical index.

`i` and `j` are 0 to 7.
The bit number is 0 to 63.

#### `int index_to_position_i(int n)`

Returns horizontal index from a bit number.

The bit number is 0 to 63.
The index is 0 to 7.

#### `int index_to_position_j(int n)`

Returns vertical index from a bit number.

The bit number is 0 to 63.
The index is 0 to 7.

[See all (Header file)](ReversiAiDll/ReversiAiDll.h)

## Use with Unity

1. Import DLL into Unity `Plugins` folder inside of `Assets`
2. Configure platform settings in Inspector view
3. Write codes that call DLL functions

### Sample code

Import functions from the DLL.

```cs
[DllImport("ReversiAiDll")]
private static extern int heuristic_search(ulong a, ulong b, int d);

[DllImport("ReversiAiDll")]
private static extern int full_search(ulong a, ulong b);

[DllImport("ReversiAiDll")]
private static extern int position_to_index(int i, int j);

[DllImport("ReversiAiDll")]
private static extern int index_to_position_i(int n);

[DllImport("ReversiAiDll")]
private static extern int index_to_position_j(int n);
```

Don't forget to add a using directive.

```cs
using System.Runtime.InteropServices;
```

## Console application

This solution includes a Windows console application to test the AI.

### Usage

`ReversiConsole.exe [dark|light]`

The positional argument is your side.
That is dark by default.

![console reversi](Console.png)

# License

[Apache License 2.0](LICENSE)
