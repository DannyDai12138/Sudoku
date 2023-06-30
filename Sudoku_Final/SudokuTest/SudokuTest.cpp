#include "pch.h"
#include "CppUnitTest.h"
#include "../sudoku_final/include/sudoku_final.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuTests
{
    TEST_CLASS(SudokuGeneratorSolverTests)
    {
    public:

        TEST_METHOD(TestIsValid)
        {
            // Create a valid Sudoku board
            vector<vector<int>> board = {
                {3, 1, 6, 2, 8, 5, 7, 9, 4},
                {2, 0, 7, 0, 3, 9, 0, 1, 5},
                {9, 5, 4, 1, 6, 7, 8, 0, 3},
                {8, 4, 9, 6, 7, 0, 0, 0, 2},
                {1, 6, 5, 0, 2, 3, 4, 7, 9},
                {7, 3, 2, 5, 9, 4, 1, 0, 8},
                {5, 2, 3, 7, 0, 8, 9, 4, 6},
                {4, 9, 1, 3, 0, 6, 0, 8, 7},
                {6, 7, 8, 9, 4, 2, 5, 3, 0}
            };

            // Test cols and rows
            Assert::IsTrue(isValid(&board, 8, 8, 1));
            Assert::IsFalse(isValid(&board, 8, 8, 2));

            // Test 3x3
            Assert::IsTrue(isValid(&board, 1, 1, 8));
            Assert::IsFalse(isValid(&board, 1, 1, 6));
        }

        TEST_METHOD(TestGenerateSudoku)
        {
            vector<vector<int>> board(N, vector<int>(N, EMPTY));

            // Generate a Sudoku board
            generateSudoku(&board, 0, 0);

            // Check if the board is valid
            int solutionCount = 0;
            Assert::IsTrue(solveSudoku(&board, 0, 0, &solutionCount));
            Assert::AreEqual(1, solutionCount);
        }

        TEST_METHOD(TestDigHoles)
        {
            vector<vector<int>> board(N, vector<int>(N, EMPTY));

            // Generate a Sudoku board
            generateSudoku(&board, 0, 0);

            // Dig holes in the board
            digHoles(&board, 1, true, 20);

            // Check if the number of empty cells matches the expected count
            int emptyCount = 0;
            for (const auto& row : board) {
                for (int num : row) {
                    if (num == EMPTY) {
                        emptyCount++;
                    }
                }
            }
            Assert::AreEqual(20, emptyCount);
        }

        TEST_METHOD(TestDifficulty1)
        {
            vector<vector<int>> board(N, vector<int>(N, EMPTY));

            // Generate a Sudoku board
            generateSudoku(&board, 0, 0);

            // Dig holes in the board
            digHoles(&board, 1, true, 0);

            // Check if the number of empty cells matches the expected count
            int emptyCount = 0;
            for (const auto& row : board) {
                for (int num : row) {
                    if (num == EMPTY) {
                        emptyCount++;
                    }
                }
            }
            Assert::AreEqual(10, emptyCount);
        }

        TEST_METHOD(TestDifficulty2)
        {
            vector<vector<int>> board(N, vector<int>(N, EMPTY));

            // Generate a Sudoku board
            generateSudoku(&board, 0, 0);

            // Dig holes in the board
            digHoles(&board, 2, true, 0);

            // Check if the number of empty cells matches the expected count
            int emptyCount = 0;
            for (const auto& row : board) {
                for (int num : row) {
                    if (num == EMPTY) {
                        emptyCount++;
                    }
                }
            }
            Assert::AreEqual(25, emptyCount);
        }

        TEST_METHOD(TestDifficulty3)
        {
            vector<vector<int>> board(N, vector<int>(N, EMPTY));

            // Generate a Sudoku board
            generateSudoku(&board, 0, 0);

            // Dig holes in the board
            digHoles(&board, 3, true, 0);

            // Check if the number of empty cells matches the expected count
            int emptyCount = 0;
            for (const auto& row : board) {
                for (int num : row) {
                    if (num == EMPTY) {
                        emptyCount++;
                    }
                }
            }
            Assert::AreEqual(40, emptyCount);
        }

        TEST_METHOD(TestSolveSudoku)
        {
            vector<vector<int>> board(N, vector<int>(N, EMPTY));

            // Create a valid Sudoku board
            board = {
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

            // Solve the Sudoku board
            int solutionCount = 0;
            Assert::IsFalse(solveSudoku(&board, 0, 0, &solutionCount));
            Assert::AreEqual(1, solutionCount);
        }

        TEST_METHOD(TestMain1)
        {
            const char* argv[] = { "Sudoku.exe", "-s", "Test.txt" };
            int argc = sizeof(argv) / sizeof(argv[0]);

            // 设置预期输出
            std::string expectedOutput = "数独游戏的解成功写入文件【sudoku.txt】。\n";

            // 保存cout的输出
            std::stringstream output;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(output.rdbuf());

            // 调用要测试的方法
            main(argc, const_cast<char**>(argv));  // 假设你的main函数命名为ProgramMain

            // 恢复cout的输出并获取实际输出
            std::cout.rdbuf(oldCoutBuffer);
            std::string actualOutput = output.str();

            // 验证输出是否符合预期
            Assert::AreEqual(expectedOutput, actualOutput);
        }

        TEST_METHOD(TestMain2)
        {
            const char* argv[] = { "Sudoku.exe", "-n", "1", "-r", "20" };
            int argc = sizeof(argv) / sizeof(argv[0]);

            // 设置预期输出
            std::string expectedOutput = "Exception:请输入正确的数量范围，如\"20~55\"\n";

            // 保存cout的输出
            std::stringstream output;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(output.rdbuf());

            // 调用要测试的方法
            main(argc, const_cast<char**>(argv));  // 假设你的main函数命名为ProgramMain

            // 恢复cout的输出并获取实际输出
            std::cout.rdbuf(oldCoutBuffer);
            std::string actualOutput = output.str();

            // 验证输出是否符合预期
            Assert::AreEqual(expectedOutput, actualOutput);
        }

        TEST_METHOD(TestMain3)
        {
            const char* argv[] = { "Sudoku.exe", "-u" };
            int argc = sizeof(argv) / sizeof(argv[0]);

            // 设置预期输出
            std::string expectedOutput = "Exception:-u参数需与-n参数同时使用！请检查！\n";

            // 保存cout的输出
            std::stringstream output;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(output.rdbuf());

            // 调用要测试的方法
            main(argc, const_cast<char**>(argv));  // 假设你的main函数命名为ProgramMain

            // 恢复cout的输出并获取实际输出
            std::cout.rdbuf(oldCoutBuffer);
            std::string actualOutput = output.str();

            // 验证输出是否符合预期
            Assert::AreEqual(expectedOutput, actualOutput);
        }

        TEST_METHOD(TestMain4)
        {
            const char* argv[] = { "Sudoku.exe", "-n", "90" };
            int argc = sizeof(argv) / sizeof(argv[0]);

            // 调用要测试的方法
            main(argc, const_cast<char**>(argv));  // 假设你的main函数命名为ProgramMain

            // 验证输出是否符合预期
            Assert::AreEqual(90, Testgamecount());
        }

        TEST_METHOD(TestMain5)
        {
            const char* argv[] = { "Sudoku.exe", "-c", "200" };
            int argc = sizeof(argv) / sizeof(argv[0]);

            // 调用要测试的方法
            main(argc, const_cast<char**>(argv));  // 假设你的main函数命名为ProgramMain

            // 验证输出是否符合预期
            Assert::AreEqual(200, Testfinalcount());
        }

        TEST_METHOD(TestMain6)
        {
            const char* argv[] = { "Sudoku.exe", "-n", "1", "-r", "30~40" };
            int argc = sizeof(argv) / sizeof(argv[0]);

            // 调用要测试的方法
            main(argc, const_cast<char**>(argv));  // 假设你的main函数命名为ProgramMain

            // 验证输出是否符合预期
            Assert::AreEqual(30, Testlholes());
            Assert::AreEqual(40, Testrholes());
        }

        TEST_METHOD(TestMain7)
        {
            const char* argv[] = { "Sudoku.exe", "-n", "1", "-u" };
            int argc = sizeof(argv) / sizeof(argv[0]);

            // 调用要测试的方法
            main(argc, const_cast<char**>(argv));  // 假设你的main函数命名为ProgramMain

            // 验证输出是否符合预期
            Assert::IsTrue(Testflag());
        }
    };
}