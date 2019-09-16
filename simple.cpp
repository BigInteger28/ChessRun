/*
 * simple.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: joris
 */
#include <iostream>
#include "simple.hpp"

int board[] = {0, 0, 0, 0, 0, 0, 65, 65, 65, 65, 65, 65};
int prevBoard[] = {0, 0, 0, 0, 0, 0, 65, 65, 65, 65, 65, 65}; //Neem gewoon een vector en elke halfzet is een board[] die je meegeeft
int legalmoves[12];
int amountLegalmoves = 0;
int legalBlackStart;

void piecePos(int piece, int pos) {
	board[piece] = pos;
}

void setupBoard(int wp, int wh, int wb, int wr, int wq, int wk, int bp, int bh, int bb, int br, int bq, int bk) {
	board[WHITE_PAWN] = wp, board[WHITE_HORSE] = wh, board[WHITE_BISHOP] = wb,
	board[WHITE_ROOK] = wr, board[WHITE_QUEEN] = wq, board[WHITE_KING] = wk,
	board[BLACK_PAWN] = bp, board[BLACK_HORSE] = bh, board[BLACK_BISHOP] = bb,
	board[BLACK_ROOK] = br, board[BLACK_QUEEN] = bq, board[BLACK_KING] = bk;
}

void findLegalMoves() {
	int size = 0;
	int current = 0;
	for (int i = WHITE_PAWN; i < BLACK_PAWN; i++) {
		if (board[i] != -1 && board[i] < 64) {
			size++;
			legalmoves[current] = i;
			current++;
		}
	}
	legalBlackStart = current;
	for (int i = BLACK_PAWN; i < PIECES; i++) {
		if (board[i] != -1 && board[i] > 1) {
			size++;
			legalmoves[current] = i;
			current++;
		}
	}
	amountLegalmoves = size;
}

void doMove(int piece) {
	for (int i = 0; i < 12; i++) prevBoard[i] = board[i];
	board[piece] += steps[piece];
}

void takebackMove() {
	for (int i = 0; i < 12; i++) board[i] = prevBoard[i];
}

bool whiteMate() {
	bool mate = true;
	for (int i = 0; i < amountLegalmoves; i++) {
		if (legalmoves[i] > WHITE_KING) mate = false;
	}
	return mate;
}

bool blackMate() {
	bool mate = true;
	for (int i = 0; i < amountLegalmoves; i++) {
		if (legalmoves[i] < BLACK_PAWN) mate = false;
	}
	return mate;
}

bool isFinished(int piece) {
	if (piece < BLACK_PAWN) {
		return board[piece] > 63;
	} else {
		return board[piece] < 2;
	}
}

int getTaken(int piece) {
	if (piece < BLACK_PAWN) {
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
	return 12;
}

float takenPieces(int piece) {
	float score = 0;
	for (int i = 0; i < 6; i++) {
		if (board[i] == -1) score--;
	}
	for (int j = 6; j < 12; j++) {
		if (board[j] == -1) score++;
	}
	return score;
}

float standingOnOtherPiece(int piece) {
	if (piece < BLACK_PAWN) {
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

float pieceActivity(int piece) {
	float score = 0;
	if (piece < BLACK_PAWN) {
		for (int i = 0; i < 6; i++) {
			if (board[i] > 0) score += scorePieceActivity[i];
			score += float(board[i]) / 64;
		}
	} else {
		for (int i = 6; i < 12; i++) {
			if (board[i] < 65) score += scorePieceActivity[i];
			score += (float(board[i]) - 65) / 64; //Moet += zijn omdat de score sowieso negatief wordt
		}
	}
	return score;
}

float evaluateMove(int piece) {
	float score = takenPieces(piece);
	doMove(piece);
	if (isFinished(piece)) return score += scoreonfinish[piece];
	if (whiteMate()) return WHITE_MATE; //Kijk naar depth om de vlugste mate te vinden. WHITE_MATE + current_depth
	if (blackMate()) return BLACK_MATE;
	else {
		score += standingOnOtherPiece(piece);
		score -= scoreonfinish[getTaken(piece)];
		score += pieceActivity(piece);
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
	findLegalMoves();
	for (int i = 0; i < amountLegalmoves; i++) {
		std::cout << piecename[legalmoves[i]] << "scores: " << evaluateMove(legalmoves[i]) << std::endl;
		takebackMove();
	}
}

int findBestMove(int player, int depth) {
	findLegalMoves();
	if (amountLegalmoves == 0) return 12; //Er zijn geen legale zetten meer mogelijk
	else {
		int bestmove;
		float bestscore;

		//max
		if (player == WHITE) {
			int current = 0;
			bestscore = evaluateMove(legalmoves[current]);
			bestmove = legalmoves[current];
			takebackMove();
			for (current = 1; legalmoves[current] < BLACK_PAWN; current++) {
				if (evaluateMove(legalmoves[current]) > bestscore) {
					takebackMove();
					bestmove = legalmoves[current];
					bestscore = evaluateMove(legalmoves[current]);
					takebackMove();
				}
			}
			return bestmove;
		}
		//min
		else {
			int current = legalBlackStart;
			bestscore = evaluateMove(legalmoves[current]);
			bestmove = legalmoves[current];
			takebackMove();
			for (current += 1; legalmoves[current] > WHITE_KING; current++) {
					if (evaluateMove(legalmoves[current]) < bestscore) {
						takebackMove();
						bestmove = legalmoves[current];
						bestscore = evaluateMove(legalmoves[current]);
						takebackMove();
					}
			}
			return bestmove;
		}
	}
}

void engineMove(int player, int depth) {
	std::cout << "*** " << std::endl;
	int best = findBestMove(player, depth);
	std::cout << "Bestmove is: " << piecename[best] << "for depth " << depth;
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
