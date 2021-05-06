#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <bitset>
#include <cmath>


//�Ֆʂ̃r�b�g�{�[�h
typedef std::bitset<121> bitBoard;

typedef struct {
	int x;
	int y;
} spot;

//�΂̒u����Ƃ�����o��
bitBoard isPut(bitBoard &player, bitBoard &opp);

//�΂�u��
void doPut(int point, bitBoard &player, bitBoard &opp);

//�΂̒u����Ƃ����bitFlag�̗���index�ɕϊ�
std::vector<int> getFlag(bitBoard &canPut);

//11*11�Ֆʂ̂����L����9*9�̓]�u
inline void trans9in11(bitBoard &x);

//11*11�Ֆʂ̏㉺���]
inline void flip11(bitBoard &x);

//�Ֆʂ�90�x��]
void rotate90degClock(bitBoard &x);


//�ȉ�bitBoard�p�̎g�p�}�X�N

//�Ֆʂ̗L��������mask
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

// trans9in11�pmask
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

// trans9in11�pmask
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
// trans9in11�pmask
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
// trans9in11�pmask
static const bitBoard mask40 = bitBoard().set(16).set(64);
// trans9in11�pmask
static const bitBoard mask30 = bitBoard().set(27).set(63);

//flip11�pmask
static const bitBoard mask66("11111111111""11111111111""11111111111"
	"11111111111""11111111111"		"00000000000"
	"00000000000""00000000000""00000000000"
	"00000000000""00000000000");
//flip11�pmask
static const bitBoard mask33("11111111111""11111111111""00000000000"
	"00000000000""00000000000"		"00000000000"
	"11111111111""11111111111""00000000000"
	"00000000000""00000000000");
//flip11�pmask
static const bitBoard mask11("11111111111""00000000000""00000000000"
	"11111111111""00000000000"		"00000000000"
	"11111111111""00000000000""00000000000"
	"11111111111""00000000000");