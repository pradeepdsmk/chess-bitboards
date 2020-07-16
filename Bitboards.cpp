// Bitboards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "pieces.h"
#include "MoveFinder.h"


#define BYTE_TO_BINARY_PATTERN " %c %c %c %c %c %c %c %c\n"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? 79 : 249), \
  (byte & 0x40 ? 79 : 249), \
  (byte & 0x20 ? 79 : 249), \
  (byte & 0x10 ? 79 : 249), \
  (byte & 0x08 ? 79 : 249), \
  (byte & 0x04 ? 79 : 249), \
  (byte & 0x02 ? 79 : 249), \
  (byte & 0x01 ? 79 : 249) 




void printBoard(const char* title, int64_t b) {
	std::cout << title << std::endl;
	for (int i = 0; i < 8; i++) {
		unsigned char row = (unsigned char)(((b << (8 * i)) & 0xff00000000000000) >> 56); // 56 = 64 - 8
		printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(row));
	}
	std::cout << std::endl;
}


void printMoveBoards(PieceTypes i) {
	for (int j = 0; j < 64; j++) {		
		char sq[3];
		int boardRow = j / 8;
		int boardCol = j % 8;
		snprintf(sq, sizeof(sq), "%c%d", boardCol + 97, 8 - boardRow);
		
		std::string title;
		title += "Moves for " + PieceNames[i] + " at " + sq;
		
		std::system("cls");
		printBoard(title.c_str(), PieceMoves[i][j]);

		Sleep(1000);
	}
}

int main()
{
	int64_t occupancy = 0;
	printBoard("empty board", occupancy);

	occupancy |= 0xffff00000000ffff;
	printBoard("startpos", occupancy);

	//int64_t n = 0x5088008850000000;
	//printBoard("knight attack at pos 18", n);

	//n <<= 1;
	//printBoard("knight attack at pos 17", n);
			
	//MoveFinder m;
	//m.printMovesList(PieceTypes::king);
	//m.printMovesList(PieceTypes::queen);
	//m.printMovesList(PieceTypes::bishop);
	//m.printMovesList(PieceTypes::knight);
	//m.printMovesList(PieceTypes::rook);
	//m.printMovesList(PieceTypes::whitePawn);
	//m.printMovesList(PieceTypes::blackPawn);	

	std::cout << "Press Enter to continue to moves display screen...";
	std::string input;
	std::getline(std::cin, input);

	/*for (int i = 0; i < 7; i++) {
		printMoveBoards(static_cast<PieceTypes> (i));
	}*/
	printMoveBoards(PieceTypes::queen);

}