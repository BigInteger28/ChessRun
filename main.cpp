/*
 * main.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: joris
 */
#include <iostream>
#include <thread>

#include "simple.hpp"
using namespace std;

int main() {
	//init();
	/*for (int i = 0; i < 12; i++) {
		cout << "|" << i << "|: " << positions[i] << endl;
	}
	*/

	/*
	int depth = 50;
	thread t1 {calculateMove, QUEEN1, PAWN2, depth};
	t1.join();
	thread t2 {calculateMove, QUEEN1, BISHOP2, depth};
	t2.join();
	thread t3 {calculateMove, QUEEN1, HORSE2, depth};
	t3.join();
	thread t4 {calculateMove, QUEEN1, TOWER2, depth};
	t4.join();
	thread t5 {calculateMove, QUEEN1, QUEEN2, depth};
	t5.join();
	thread t6 {calculateMove, QUEEN1, KING2, depth};
	t6.join();
	*/
	piecePos(WHITE_KING, 26);
	piecePos(BLACK_PAWN, 33);
	int depth = 1;

	multipv();
	engineMove(WHITE, depth);
}


