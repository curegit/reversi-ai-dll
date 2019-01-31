# Reversi AI DLL

This is heuristic reversi AI implemented as a Windows native DLL.
The DLL has simple API.
For instance, board state is given, a API function returns a move you should to choose next.
The AI have moderate strength.
The DLL can be used in Windows standalone projects of Unity.

## Run a console application

This solution includes a Windows console application to test the AI.

### Usage

`ReversiConsole.exe [dark|light]`

Your side is dark by default.

![console reversi](Console.png)

## Use with Unity

1. Import DLL into Unity `Plugins` folder inside of `Assets`
2. Configure platform settings in Inspector view
3. Write codes that call DLL functions

### Sample code



```cs
[DllImport("ReversiAiDll")]
private static extern int heuristic_search(ulong a, ulong b, int d);

[DllImport("ReversiAiDll")]
private static extern int full_search(ulong a, ulong b, int w);

[DllImport("ReversiAiDll")]
private static extern int position_to_index(int i, int j);

[DllImport("ReversiAiDll")]
private static extern int index_to_position_i(int n);

[DllImport("ReversiAiDll")]
private static extern int index_to_position_j(int n);
```
