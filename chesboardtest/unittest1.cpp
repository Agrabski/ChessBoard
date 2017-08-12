#include "stdafx.h"
#include "CppUnitTest.h"
#include "C:\Users\adam_000\Desktop\chesss\MFCApplication1\MFCApplication1\Chessboard.h"
#include "C:\Users\adam_000\Desktop\chesss\MFCApplication1\MFCApplication1\Chessboard.cpp"
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
				board.ChangeState(ChessBoard::InternalMove({ 0,1 }, { 0,2 },ChessBoard::Standard));
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


	};
}