/*
 * ai.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: joris
 */
#include "ai.hpp"

#include <iostream>
using namespace std;



/*
 * Scores
 * Gaan naar leeg veld --> 0
 * Gaan naar vol veld --> +1 of -1 indien eigen stuk
 * Gaan naar eindveld --> +1
 *
 *
 * positie -1 = geslagen stuk
 * positie 0 = stuk in wachtrij
 */

int temp_position[] = {0, 0, 0, 0, 0, 0, 65, 65, 65, 65, 65, 65};
int temp_movenumber[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//int currentPlayer = 0;

/*void doMove(int piece) {
	temp_position[piece] +=	movevalue[(piece * 3) + temp_movenumber[piece]];
	temp_movenumber[piece] = (temp_movenumber[piece] + 1) % 3;
	//cout << "Move: " << temp_position[piece] << endl;
}*/

//stukken1[?] stukken2[?] depth
void calculateMove(int ownpiece, int enemypiece, int depth) {
	for (int tdepth = 0; tdepth < depth; tdepth++) {
		int score = 0;
		//Controlleer als ons stuk op hetzelfde staat als enemy ---> Ja dan is ons stuk gepakt
		for (int i = 0; i < 12; i++) {
			if (temp_position[ownpiece] > 0 && ownpiece != i && temp_position[ownpiece] == temp_position[i]) {
				temp_position[ownpiece] = -1;
				score = -1;
			}
		}
		//Als ons stuk niet geslagen is dan doe verder
		if (score != -1) {
			//Doe zet
			doMove(ownpiece);
			for (int i = 6; i < 12; i++) {
				if (temp_position[ownpiece] > 0 && temp_position[ownpiece]  == temp_position[i]) {
					temp_position[i] = -1;
					score = 1;
				}
			}
			if (temp_position[ownpiece] > 63) {

				score = 1;
				cout << piecename[ownpiece] << " " << piecename[enemypiece] << "   score: " << score << endl;
				break;
			}

			//Tegenstander doet zet
			if (temp_position[enemypiece] > 1) doMove(enemypiece);
			if (temp_position[enemypiece] < 2) {
				score = -1;
				/*for (int i = 0; i < 12; i++) {
					cout << temp_position[i] << "   ";
				}*/
				cout << piecename[ownpiece] << " LUNTE " << piecename[enemypiece] << "   score: " << score << endl;
				break;
			}
		}

		//cout << piecename[ownpiece] << "& " << piecename[enemypiece] << " score: " << score << endl;
	}
}

