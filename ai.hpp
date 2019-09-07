/*
 * game.hpp
 *
 *  Created on: Sep 6, 2019
 *      Author: joris
 */

#ifndef AI_HPP_
#define AI_HPP_

#include <string>

enum pieces {
	PAWN1, BISHOP1, HORSE1, TOWER1, QUEEN1, KING1, PAWN2, BISHOP2, HORSE2, TOWER2, QUEEN2, KING2
};

const std::string piecename[] {"Player 1 Pawn ", "Player 1 Bishop ", "Player 1 Horse ", "Player 1 Tower ", "Player 1 Queen ", "Player 1 King ", "Player 2 Pawn ", "Player 2 Bishop ", "Player 2 Horse ", "Player 2 Rook ", "Player 2 Queen ", "Player 2 King "};


const int movevalue[] {		1, 2, 1, //PAWN1
						0, 0, 0, //BISHOP1
						7, -3, 6, //HORSE1
						0, 0, 0, //TOWER1
						9, 2, -3, //QUEEN1
						0, 0, 0,//KING1
						-1, -2, -1, //PAWN2
						0, 0, 0, //BISHOP2
						-7, 3, -6, //HORSE2
						0, 0, 0, //TOWER2
						-9, -2, 3, //QUEEN2
						0, 0, 0};//KING2

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

void doMove(int piece);
void calculateMove(int ownpiece, int enemypiece, int depth);

#endif /* AI_HPP_ */
