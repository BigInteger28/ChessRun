/*
 * simple.hpp
 *
 *  Created on: Sep 9, 2019
 *      Author: joris
 */

#ifndef SIMPLE_HPP_
#define SIMPLE_HPP_
#include <string>

/*	BOARD
 *
 * 	8	9	24	25	40	41	56	57
 * 	7	10	23	26	39	42	55	58
 * 	6	11	22	27	38	43	54	59
 * 	5	12	21	28	37	44	53	60
 * 	4	13	20	29	36	45	52	61
 * 	3	14	19	30	35	46	51	62
 * 	2	15	18	31	34	47	50	63
 * 	1 	16	17	32	33	48	49	64
 */

enum pieces {
	WHITE_PAWN, WHITE_HORSE, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
	BLACK_PAWN, BLACK_HORSE, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING, PIECES
};

enum player {
	WHITE, BLACK
};

const std::string piecename[] {	"WHITE Pawn ", "WHITE Horse ", "WHITE Bishop ", "WHITE Rook ", "WHITE Queen ", "WHITE King ",
								"BLACK Pawn ", "BLACK Horse ", "BLACK Bishop ", "BLACK Rook ", "BLACK Queen ", "BLACK King ",
								"NONE "};

const int steps[] {	2, 	3, 	4, 	5, 	9, 	7,
					-2, -3, -4, -5, -9, -7 };

const float scoreonfinish[] {	1,	1,	1,	1,	1,	2,
								-1,	-1,	-1,	-1,	-1,	-2,	0 }; //laatste 0 is voor getTaken

const float scorePieceActivity[] {	0.05,	0.05,	0.05,	0.05,	0.05,	0.05,
									-0.05,	-0.05,	-0.05,	-0.05,	-0.05, -0.05	};

const float WHITE_MATE = 1000;
const float BLACK_MATE = -1000;

void piecePos(int, int);
void setupBoard(int, int, int, int, int, int, int, int, int, int, int, int);
void multipv();
void engineMove(int, int);

#endif /* SIMPLE_HPP_ */
