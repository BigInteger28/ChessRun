/*
 * main.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: joris
 */
#include <iostream>
#include <thread>

#include "ai.hpp"
using namespace std;

/*int positions[12];

void init() {
	for (int i = 0; i < 12; i++) {
		positions[i] = 0;
	}
}*/

int main() {
	//init();
	/*for (int i = 0; i < 12; i++) {
		cout << "|" << i << "|: " << positions[i] << endl;
	}
	*/
	thread t1 {calculateMove, QUEEN1, HORSE2, 20};
	thread t2 {calculateMove, QUEEN1, PAWN2, 20};

	t1.join();
	t2.join();
}


