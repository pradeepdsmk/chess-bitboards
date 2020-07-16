#include <iostream>
#include <string>
#include <vector>

#include "pieces.h"
#include "MoveFinder.h"

static const char HEX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

void MoveFinder::findKnightMoves(unsigned int arr[][8], unsigned int row, unsigned int col) {
	unsigned int r2u = row - 2;
	unsigned int r1u = row - 1;
	unsigned int r1d = row + 1;
	unsigned int r2d = row + 2;

	unsigned int c2l = col - 2;
	unsigned int c1l = col - 1;
	unsigned int c1r = col + 1;
	unsigned int c2r = col + 2;

	if ((r2u < 8) && (c1l < 8)) {
		arr[r2u][c1l] = 1;
	}
	if ((r2u < 8) && (c1r < 8)) {
		arr[r2u][c1r] = 1;
	}
	if ((r1u < 8) && (c2l < 8)) {
		arr[r1u][c2l] = 1;
	}
	if ((r1u < 8) && (c2r < 8)) {
		arr[r1u][c2r] = 1;
	}
	if ((r1d < 8) && (c2l < 8)) {
		arr[r1d][c2l] = 1;
	}
	if ((r1d < 8) && (c2r < 8)) {
		arr[r1d][c2r] = 1;
	}
	if ((r2d < 8) && (c1l < 8)) {
		arr[r2d][c1l] = 1;
	}
	if ((r2d < 8) && (c1r < 8)) {
		arr[r2d][c1r] = 1;
	}
}

void MoveFinder::findBishopMoves(unsigned int arr[][8], unsigned int row, unsigned int col) {
	int i, j;
	for (i = row - 1, j = col - 1; (i >= 0) && (j >= 0); i--, j--) {
		arr[i][j] = 1;
	}
	for (i = row - 1, j = col + 1; (i >= 0) && (j < 8); i--, j++) {
		arr[i][j] = 1;
	}
	for (i = row + 1, j = col - 1; (i < 8) && (j >= 0); i++, j--) {
		arr[i][j] = 1;
	}
	for (i = row + 1, j = col + 1; (i < 8) && (j < 8); i++, j++) {
		arr[i][j] = 1;
	}
}

void MoveFinder::findRookMoves(unsigned int arr[][8], unsigned int row, unsigned int col) {
	int i;
	for (i = row - 1; i >= 0; i--) {
		arr[i][col] = 1;
	}
	for (i = col - 1; i >= 0; i--) {
		arr[row][i] = 1;
	}
	for (i = col + 1; i < 8; i++) {
		arr[row][i] = 1;
	}
	for (i = row + 1; i < 8; i++) {
		arr[i][col] = 1;
	}
}

void MoveFinder::findKingMoves(unsigned int arr[][8], unsigned int row, unsigned int col) {
	int up = row - 1, down = row + 1, left = col - 1, right = col + 1;
	if (up >= 0) {
		if (left >= 0) {
			arr[up][left] = 1;
		}
		arr[up][col] = 1;
		if (right < 8) {
			arr[up][right] = 1;
		}
	}

	if (left >= 0) {
		arr[row][left] = 1;
	}
	if (right < 8) {
		arr[row][right] = 1;
	}

	if (down < 8) {
		if (left >= 0) {
			arr[down][left] = 1;
		}
		arr[down][col] = 1;
		if (right < 8) {
			arr[down][right] = 1;
		}
	}
}

void MoveFinder::findWhitePawnMoves(unsigned int arr[][8], unsigned int row, unsigned int col) {
	if ((row <= 6) && (row > 0)) {
		arr[row - 1][col] = 1;
		if (row == 6) {
			arr[row - 2][col] = 1;
		}
	}
}

void MoveFinder::findBlackPawnMoves(unsigned int arr[][8], unsigned int row, unsigned int col) {
	if ((row <= 6) && (row > 0)) {
		arr[row + 1][col] = 1;
		if (row == 1) {
			arr[row + 2][col] = 1;
		}
	}
}

std::string MoveFinder::boardToInt64Str(unsigned int arr[][8]) {
	std::string str = "0x";
	for (unsigned int i = 0; i < 8; i++) {

		unsigned int firstNibble = (8 * arr[i][0])
			+ (4 * arr[i][1])
			+ (2 * arr[i][2])
			+ (1 * arr[i][3]);
		str += HEX[firstNibble];
		unsigned int secondNibble = (8 * arr[i][4])
			+ (4 * arr[i][5])
			+ (2 * arr[i][6])
			+ (1 * arr[i][7]);
		str += HEX[secondNibble];

	}
	return str;
}

void MoveFinder::buildMovesList(PieceTypes piece, std::vector<std::string>& list) {

	unsigned int row, col;

	list.clear();	

	//std::cout << std::endl << "all 64 moves of " << PieceNames[piece] << std::endl;
	for (row = 0; row < 8; row++) {
		for (col = 0; col < 8; col++) {

			unsigned int arr[8][8] = { 0 };

			switch (piece) {
			case PieceTypes::king:
				findKingMoves(arr, row, col);
				break;
			case PieceTypes::queen:
				findBishopMoves(arr, row, col);
				findRookMoves(arr, row, col);
				break;
			case PieceTypes::bishop:
				findBishopMoves(arr, row, col);
				break;
			case PieceTypes::knight:
				findKnightMoves(arr, row, col);
				break;
			case PieceTypes::rook:
				findRookMoves(arr, row, col);
				break;
			case PieceTypes::whitePawn:
				findWhitePawnMoves(arr, row, col);
				break;
			case PieceTypes::blackPawn:
				findBlackPawnMoves(arr, row, col);
				break;
			}

			//printMoves(arr);
			list.push_back(boardToInt64Str(arr));
		}
	}
	//std::cout << std::endl;

	

}

void MoveFinder::printMovesList(PieceTypes piece) {
	std::vector<std::string> list;
	buildMovesList(piece, list);

	std::cout << std::endl << "all 64 moves of " << PieceNames[piece] << std::endl;
	for (std::string str : list) {
		std::cout << str << "," << std::endl;
	}
	std::cout << std::endl;
}
