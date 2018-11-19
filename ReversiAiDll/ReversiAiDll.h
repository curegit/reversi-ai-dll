#pragma once

// 外部にエクスポートされる関数を定義します
extern "C"
{
	// 
	__declspec(dllexport) int encode_position(int i, int j);

	// 
	__declspec(dllexport) int decode_position_i(int position);

	// 
	__declspec(dllexport) int decode_position_j(int position);
}
