#pragma once

class MoveFinder {
	void findKnightMoves(unsigned int arr[][8], unsigned int row, unsigned int col);
	void findBishopMoves(unsigned int arr[][8], unsigned int row, unsigned int col);
	void findRookMoves(unsigned int arr[][8], unsigned int row, unsigned int col);
	void findKingMoves(unsigned int arr[][8], unsigned int row, unsigned int col);
	void findWhitePawnMoves(unsigned int arr[][8], unsigned int row, unsigned int col);
	void findBlackPawnMoves(unsigned int arr[][8], unsigned int row, unsigned int col);
	std::string boardToInt64Str(unsigned int arr[][8]);
	void buildMovesList(PieceTypes piece, std::vector<std::string>& list);

public:
	void printMovesList(PieceTypes piece);
};
