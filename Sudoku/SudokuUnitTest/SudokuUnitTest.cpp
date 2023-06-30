#include "pch.h"
#include "CppUnitTest.h"
#include "../sudoku.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuUnitTest
{
	TEST_CLASS(SudokuUnitTest)
	{
	public:
		TEST_METHOD(TestFirstLine)
		{
			//测试终局生成时首行稳定性
			int source[] = { 5, 1, 2, 9, 8, 7, 4, 3, 6 };
			int line = 0;
			Permutate_Permutation(source, 1, 8, Permutation, line, 20 / 72 + 1);
			int result[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 9; i++)
				result[i] = Permutation[line - 1][i];
			for (int i = 0; i < 9; i++)
				Assert::AreEqual(result[i], source[i]);
		}
		TEST_METHOD(TestGenerateEndGame)
		{
			//测试终局函数
			bool res = Generate_EndGame("./test_output.txt", 10);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestGenerateNewGame1)
		{
			//测试自定义难度
			solution_path = "../../sudoku.txt";
			bool res = Generate_NewGame("../../end_game.txt", "./test_output.txt", 10, true, NORMAL, MIN_SPACE, MAX_SPACE, false);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestGenerateNewGame2)
		{
			//测试自定义空格数范围
			solution_path = "../../sudoku.txt";
			bool res = Generate_NewGame("../../end_game.txt", "./test_output.txt", 10, false, EASY, 40, 50, false);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestCheckX)
		{
			Assert::AreEqual(true, checkx(1));
		}
		TEST_METHOD(TestCheckY)
		{
			Assert::AreEqual(true, checky(1));
		}
		TEST_METHOD(TestJggfz1)
		{
			Assert::AreEqual(true, jggfz(1));
		}
		TEST_METHOD(TestJggfz2)
		{
			Assert::AreEqual(true, jggfz(2));
		}
		TEST_METHOD(TestJggfz3)
		{
			Assert::AreEqual(true, jggfz(3));
		}
		TEST_METHOD(TestJggfz4)
		{
			Assert::AreEqual(true, jggfz(4));
		}
		TEST_METHOD(TestJggfz5)
		{
			Assert::AreEqual(true, jggfz(5));
		}
		TEST_METHOD(TestJggfz6)
		{
			Assert::AreEqual(true, jggfz(6));
		}
		TEST_METHOD(TestJggfz7)
		{
			Assert::AreEqual(true, jggfz(7));
		}
		TEST_METHOD(TestJggfz8)
		{
			Assert::AreEqual(true, jggfz(8));
		}
		TEST_METHOD(TestJggfz9)
		{
			Assert::AreEqual(true, jggfz(9));
		}
		TEST_METHOD(TestDfs1)
		{
			// 先全部设置为0
			memset(a, 0, sizeof(a));
			memset(b, 0, sizeof(b));
			memset(bid, 0, sizeof(bid));
			bbid = 0;
			memset(c, 0, sizeof(c));
			memset(cid, 0, sizeof(cid));
			ccid = 0;
			alltheanswer = 0;
			wanttheanswer = 1;

			// 设置数独数组
			int tmp[9][9] = {
				{3, 1, 6, 2, 8, 5, 7, 9, 4},
				{2, 8, 7, 0, 3, 9, 6, 1, 5},
				{9, 5, 4, 1, 6, 7, 8, 0, 3},
				{8, 4, 9, 6, 7, 0, 0, 0, 2},
				{1, 6, 5, 0, 2, 3, 4, 7, 9},
				{7, 3, 2, 5, 9, 4, 1, 0, 8},
				{5, 2, 3, 7, 0, 8, 9, 4, 6},
				{4, 9, 1, 3, 0, 6, 2, 8, 7},
				{6, 7, 8, 9, 4, 2, 5, 3, 0}
			};
			for (int i = 1; i <= 9; i++){
				for (int j = 1; j <= 9; j++){
					a[i][j] = tmp[i - 1][j - 1];
				}
			}

			for (int i = 1; i < 10; i++) {
				for (int j = 1; j < 10; j++) {
					if (a[i][j] != 0)
						b[i]++;
					if (a[j][i] != 0)
						c[i]++;
				}
			}

			for (int i = 1; i <= 9; i++)
				bid[i] = i, cid[i] = i;
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9 - i; j++) {
					if (b[j] < b[j + 1])
						swap(b[j], b[j + 1]), swap(bid[j], bid[j + 1]);
					if (c[j] < c[j + 1])
						swap(c[j], c[j + 1]), swap(cid[j], cid[j + 1]);
				}
			}
			;
			Assert::AreEqual(true, dfs(bid[++bbid], cid[++ccid], solution_path));
		}

		TEST_METHOD(TestSolveSingleSudoku)
		{
			// 先全部设置为0
			memset(a, 0, sizeof(a));
			memset(b, 0, sizeof(b));
			memset(bid, 0, sizeof(bid));
			bbid = 0;
			memset(c, 0, sizeof(c));
			memset(cid, 0, sizeof(cid));
			ccid = 0;
			alltheanswer = 0;
			wanttheanswer = 1;

			// 设置数独数组
			int tmp[9][9] = {
				{3, 1, 6, 2, 8, 5, 7, 9, 4},
				{2, 8, 7, 0, 3, 9, 6, 1, 5},
				{9, 5, 4, 1, 6, 7, 8, 0, 3},
				{8, 4, 9, 6, 7, 0, 0, 0, 2},
				{1, 6, 5, 0, 2, 3, 4, 7, 9},
				{7, 3, 2, 5, 9, 4, 1, 0, 8},
				{5, 2, 3, 7, 0, 8, 9, 4, 6},
				{4, 9, 1, 3, 0, 6, 2, 8, 7},
				{6, 7, 8, 9, 4, 2, 5, 3, 0}
			};

			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					a[i][j] = tmp[i - 1][j - 1];
				}
			}

			for (int i = 1; i < 10; i++) {
				for (int j = 1; j < 10; j++) {
					if (a[i][j] != 0)
						b[i]++;
					if (a[j][i] != 0)
						c[i]++;
				}
			}

			for (int i = 1; i <= 9; i++)
				bid[i] = i, cid[i] = i;
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9 - i; j++) {
					if (b[j] < b[j + 1])
						swap(b[j], b[j + 1]), swap(bid[j], bid[j + 1]);
					if (c[j] < c[j + 1])
						swap(c[j], c[j + 1]), swap(cid[j], cid[j + 1]);
				}
			}
			Assert::AreEqual(true, solve_single_sudoku(solution_path, false));
		}

		TEST_METHOD(TestPlayGame)
		{
			// 先全部设置为0
			memset(a, 0, sizeof(a));
			memset(b, 0, sizeof(b));
			memset(bid, 0, sizeof(bid));
			bbid = 0;
			memset(c, 0, sizeof(c));
			memset(cid, 0, sizeof(cid));
			ccid = 0;
			alltheanswer = 0;
			wanttheanswer = 1;
			
			Assert::AreEqual(true, Play_Game(new_game_path, solution_path));
		}
	};
}
