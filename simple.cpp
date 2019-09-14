/*
 * simple.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: joris
 */
#include <iostream>
#include "simple.hpp"

int board[] = {0, 0, 0, 0, 0, 0, 65, 65, 65, 65, 65, 65};
int prevBoard[] = {0, 0, 0, 0, 0, 0, 65, 65, 65, 65, 65, 65};

void doMove(int piece) {
	for (int i = 0; i < 12; i++) prevBoard[i] = board[i];
	board[piece] +=	steps[piece];
}

void returnMove() {
	for (int i = 0; i < 12; i++) board[i] = prevBoard[i];
}

bool isFinished(int piece) {
	if (piece < PAWN2) {
		return board[piece] > 63;
	} else {
		return board[piece] < 2;
	}
}

int getTaken(int piece) {
	if (piece < PAWN2) {
		for (int p2 = 6; p2 < 12; p2++) {
			for (int i = 0; i < 6; i++) {
				if (board[i] == board[p2] + steps[p2]) return i;
			}
		}
	} else {
		for (int p1 = 0; p1 < 6; p1++) {
			for (int i = 6; i < 12; i++) {
				if (board[i] == board[p1] + steps[p1]) return i;
			}
		}
	}
	return -1;
}

float standingOnOtherPiece(int piece) {
	if (piece < PAWN2) {
		//Op eigen stuk staan verliezen we ons stuk
		for (int i = 0; i < 6; i++) {
			if (i != piece && board[piece] == board[i]) return scoreonfinish[piece + 6];
		}
		//Op ander stuk staan slaan we dat stuk
		for (int i = 6; i < 12; i++) {
			if (board[piece] == board[i]) return scoreonfinish[i - 6];
		}
	} else {
		//Op eigen stuk staan verliezen we ons stuk
		for (int i = 6; i < 12; i++) {
			if (i != piece && board[piece] == board[i]) return scoreonfinish[piece - 6];
		}
		//Op ander stuk staan slaan we dat stuk
		for (int i = 0; i < 6; i++) {
			if (board[piece] == board[i]) return scoreonfinish[i + 6];
		}
	}
	return 0;
}



//alleen speler 1 heeft hier evaluatie
float evaluateMove(int piece) {
	float score = 0;
	doMove(piece);
	if (isFinished(piece)) return scoreonfinish[piece];
	else {
		score += standingOnOtherPiece(piece);
		score -= scoreonfinish[getTaken(piece)];
	}
	return score;
}

void returnboard() {
	for (int i = 0; i < 12; i++) {
		std::cout << board[i] << "  ";
	}
	std::cout << std::endl;
}

/*Doe een zet totdat ---> Ik einde bereik
 * 					----> Totdat ik geslagen word, zet terug
 * 					---->
 */

void multipv() {
	board[KING1] = 26;
	board[PAWN2] = 33;
	for (int i = 0; i < 12; i++) {
		std::cout << piecename[i] << "scores: " << evaluateMove(i) << std::endl;
		returnMove();
	}
}

int findBestMove(int player, int depth) {
	board[KING1] = 26;
	board[PAWN2] = 33;
	//max
	int bestmove = 0;
	if (player == 0) {
		int bestscore = evaluateMove(0);
		returnMove();
		for (int i = 1; i < 6; i++) {
			if (i > -1) {
				if (evaluateMove(i) > bestscore) {
					bestmove = i;
					bestscore = evaluateMove(i);
					returnMove();
				}
			}
		}
		return bestmove;
	//min
	} else {
		int bestscore = evaluateMove(6);
		returnMove();
		for (int i = 6; i < 12; i++) {
			if (i > -1) {
				if (evaluateMove(i) > bestscore) {
					bestmove = i;
					bestscore = evaluateMove(i);
					returnMove();
				}
			}
		}
		return bestmove;
	}
}



////////


//Brute Force
/*
 * Je doet een zet met queen1
 * Elke tegenspeler stuk doet een zet en hou de score bij voor elk stuk
 * De beste score voor de tegenspeler wordt genomen als stuk om verder te doen
 */
void bruteforce() {

}
