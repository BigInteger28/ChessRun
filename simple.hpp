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
	PAWN1, HORSE1, BISHOP1, TOWER1, QUEEN1, KING1, PAWN2, HORSE2, BISHOP2, TOWER2, QUEEN2, KING2
};

const std::string piecename[] {"Player 1 Pawn ", "Player 1 Horse ", "Player 1 Bishop ", "Player 1 Tower ", "Player 1 Queen ", "Player 1 King ", "Player 2 Pawn ", "Player 2 Horse ", "Player 2 Bishop ", "Player 2 Rook ", "Player 2 Queen ", "Player 2 King "};

const int steps[] {			2, 3, 4, 5, 9, 7,
							-2, -3, -4, -5, -9, -7 };

const float scoreonfinish[] {	1, 1, 1, 1, 1, 2,
							-1, -1, -1, -1, -1, -2, 0 }; //laatste 0 is voor getTaken
void multipv();
int findBestMove(int, int);

#endif /* SIMPLE_HPP_ */
