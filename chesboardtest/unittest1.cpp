#include "stdafx.h"
#include "CppUnitTest.h"
#include "Chessboard.h"
#include <functional>
#include <stdexcpt.h>
#pragma once
#define _AFXDLL

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace chesboardtest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(DoubleMoveWhite)
		{
			// TODO: Your test code here
			ChessBoard::Board board;
			try
			{
				board.ChangeState(ChessBoard::InternalMove({ 0,1 }, { 0,2 }, ChessBoard::Standard));
			}
			catch (std::exception exc)
			{
				Assert::Fail();
			}
			Assert::IsTrue(board.fields[0][1].rank.type == ChessBoard::Empty&&board.fields[0][2].rank.type == ChessBoard::Pawn);
		}

		TEST_METHOD(PawnBeatingEmptyField)
		{
			//Assert::ExpectException<ChessBoard::INVALID_MOVE>()
			// TODO: Your test code here
			try
			{
				ChessBoard::Board board;
				board.ChangeState({ { 0,1 },{ 1,2 },ChessBoard::Standard });
			}
			catch (ChessBoard::INVALID_MOVE m)
			{
				Assert::IsTrue(true);
				return;
			}
		}

		TEST_METHOD(BlackMovingFirst)
		{

			// TODO: Your test code here
			ChessBoard::Board board;
			try
			{
				board.ChangeState(ChessBoard::InternalMove({ 0,6 }, { 0,5 }, ChessBoard::Standard));
			}
			catch (ChessBoard::WRONG_COLOR e)
			{
				Assert::IsTrue(true);
				return;
			}
			Assert::Fail();
		}
#define MOVE(x1,y1,x2,y2) board.ChangeState(ChessBoard::InternalMove({ x1,y1 }, { x2,y2 }, ChessBoard::Standard));
		TEST_METHOD(MoveAfterCheckmate)
		{
			ChessBoard::Board board;
			MOVE(5, 1, 5, 2);
			MOVE(0, 6, 0, 5);
			MOVE(6, 0, 3, 4);
			MOVE(0, 5, 0, 4);
			MOVE(4, 0, 7, 5);
			MOVE(1, 6, 1, 5);
			MOVE(7, 5, 4, 6);
			try
			{
				MOVE(1, 5, 1, 4);
			}
			catch (ChessBoard::KING_IN_DANGER exception)
			{
				Assert::IsFalse(exception.isWhite);
				return;
			}
			Assert::Fail();
		}

#define MAKE_MOVE(x1,y1,x2,y2)board.ChangeState( ChessBoard::InternalMove({x1-1,y1-1},{x2-1,y2-1},ChessBoard::Standard));
#define RANK(x,y) archetype.fields[x][y].rank

		TEST_METHOD(RochadeBothSides)
		{
			ChessBoard::Board board;
			ChessBoard::Board archetype;
			for (int x = 0; x < 8; x++)
				for (int y = 0; y < 8; y++)
					archetype.fields[x][y].rank.type = ChessBoard::Empty;
			RANK(0, 7) = RANK(5, 7) = { ChessBoard::Tower,false };
			RANK(0, 6) = RANK(1, 6) = RANK(2, 4) = RANK(3, 5) = RANK(4, 4) = RANK(5, 6) = RANK(6, 5) = RANK(7, 6) = { ChessBoard::Pawn,false };
			RANK(2, 7) = RANK(6, 6) = { ChessBoard::Bishop,false };
			RANK(3, 3) = RANK(4, 6) = { ChessBoard::Knight,false };
			RANK(3, 7) = { ChessBoard::Queen,false };
			RANK(6, 7) = { ChessBoard::King,false };
			RANK(0, 1) = RANK(1, 1) = RANK(2, 1) = RANK(3, 2) = RANK(4, 3) = RANK(5, 3) = RANK(6, 2) = RANK(7, 1) = { ChessBoard::Pawn,true };
			RANK(0, 0) = RANK(5, 0) = { ChessBoard::Tower,true };
			RANK(2, 2) = RANK(5, 2) = { ChessBoard::Knight,true };
			RANK(4, 2) = RANK(6, 1) = { ChessBoard::Bishop,true };
			RANK(6, 0) = { ChessBoard::King,true };
			RANK(3, 1) = { ChessBoard::Queen,true };
			MAKE_MOVE(5, 2, 5, 4);
			MAKE_MOVE(3, 7, 3, 5);
			MAKE_MOVE(2, 1, 3, 3);
			MAKE_MOVE(2, 8, 3, 6);
			MAKE_MOVE(7, 2, 7, 3);
			MAKE_MOVE(7, 7, 7, 6);
			MAKE_MOVE(4, 2, 4, 3);
			MAKE_MOVE(6, 8, 7, 7);
			MAKE_MOVE(3, 1, 5, 3);
			MAKE_MOVE(4, 7, 4, 6);
			MAKE_MOVE(4, 1, 4, 2);
			MAKE_MOVE(5, 7, 5, 5);
			MAKE_MOVE(6, 1, 7, 2);
			MAKE_MOVE(7, 8, 5, 7);
			MAKE_MOVE(6, 2, 6, 4);
			MAKE_MOVE(3, 6, 4, 4);
			MAKE_MOVE(7, 1, 6, 3);
			board.ChangeState(ChessBoard::InternalMove({ -1,-1 }, { 0,0 }, ChessBoard::RochadeRight));
			board.ChangeState(ChessBoard::InternalMove({ -1,-1 }, { 0,0 }, ChessBoard::RochadeRight));
			Assert::IsTrue(archetype == board);
		}
	};
}
/*
5254, 3735
2133, 2836
7273, 7776
4243, 6877
3153, 4746
4142, 5755
6172, 7857
6264, 3644
7163, 5878
5171, 5564
5364,
*/