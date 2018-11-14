#pragma once

//#define DLLEXPORT __declspec(dllexport)

extern "C"
{
	__declspec(dllexport) int choose_move(long dark, long light, int player);
}