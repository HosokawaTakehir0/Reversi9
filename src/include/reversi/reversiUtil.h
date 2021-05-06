#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <bitset>
#include <cmath>


//盤面のビットボード
typedef std::bitset<121> bitBoard;

typedef struct {
	int x;
	int y;
} spot;

//石の置けるところを出力
bitBoard isPut(bitBoard &player, bitBoard &opp);

//石を置く
void doPut(int point, bitBoard &player, bitBoard &opp);

//石の置けるところをbitFlagの立つindexに変換
std::vector<int> getFlag(bitBoard &canPut);

//11*11盤面のうち有効な9*9の転置
inline void trans9in11(bitBoard &x);

//11*11盤面の上下反転
inline void flip11(bitBoard &x);

//盤面の90度回転
void rotate90degClock(bitBoard &x);


//以下bitBoard用の使用マスク

//盤面の有効部分のmask
static const bitBoard maskValid(			"00000000000"
									"01111111110"
									"01111111110"
									"01111111110"
									"01111111110"
									"01111111110"
									"01111111110"
									"01111111110"
									"01111111110"
									"01111111110"
											"00000000000");

static const bitBoard mask64int(0xffffffff);

// trans9in11用mask
static const bitBoard mask50(			"00000000000"
								"00000000000"
								"00000000000"
								"00000000000"
								"00000000000"
										"00000000000"
								"01111000000"
								"01111000000"
								"01111000000"
								"01111000000"
										"00000000000");

// trans9in11用mask
static const bitBoard mask20(			"00000000000"
								"00000000000"
								"00000000000"
								"01100011000"
								"01100011000"
										"00010000000"
								"00000000000"
								"00000100000"
								"01100011000"
								"01100011000"
										"00000000000");
// trans9in11用mask
static const bitBoard mask10(							"00000000000"
								"00000000000"
								"01010010100"
											"00000000000"
											"01010010100"
														"00001000000"
								"00000100000"
								"01010010100"
											"00000000000"
											"01010010100"
														"00000000000");
// trans9in11用mask
static const bitBoard mask40 = bitBoard().set(16).set(64);
// trans9in11用mask
static const bitBoard mask30 = bitBoard().set(27).set(63);

//flip11用mask
static const bitBoard mask66("11111111111""11111111111""11111111111"
	"11111111111""11111111111"		"00000000000"
	"00000000000""00000000000""00000000000"
	"00000000000""00000000000");
//flip11用mask
static const bitBoard mask33("11111111111""11111111111""00000000000"
	"00000000000""00000000000"		"00000000000"
	"11111111111""11111111111""00000000000"
	"00000000000""00000000000");
//flip11用mask
static const bitBoard mask11("11111111111""00000000000""00000000000"
	"11111111111""00000000000"		"00000000000"
	"11111111111""00000000000""00000000000"
	"11111111111""00000000000");