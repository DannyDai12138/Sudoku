#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include <fstream>

using namespace std;

const int N = 9;
const int EMPTY = 0;

// 检查在(row, col)位置上放置数字num是否合法
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
	// 检查同一列是否有相同数字
	for (int i = 0; i < N; i++) {
		if (board[i][col] == num) {
			return false;
		}
	}

	// 检查同一行是否有相同数字
	for (int j = 0; j < N; j++) {
		if (board[row][j] == num) {
			return false;
		}
	}

	// 检查同一个九宫格是否有相同数字
	int startRow = 3 * (row / 3);
	int startCol = 3 * (col / 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[startRow + i][startCol + j] == num) {
				return false;
			}
		}
	}

	return true;
}

// 递归地生成数独终局
bool generateSudoku(vector<vector<int>>& board, int row, int col) {
	// 终止条件：已经生成完最后一行，数独终局生成成功
	if (row == N) {
		return true;
	}

	// 如果已经到了当前行的最后一列，则转到下一行的第一列
	if (col == N) {
		return generateSudoku(board, row + 1, 0);
	}

	// 如果当前位置已经有数字，则跳到下一列
	if (board[row][col] != EMPTY) {
		return generateSudoku(board, row, col + 1);
	}

	// 尝试填充数字

	random_device rd;
	mt19937 rng(rd());

	vector<int> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	shuffle(nums.begin(), nums.end(), rng);  // 随机打乱数字的顺序

	for (int num : nums) {
		if (isValid(board, row, col, num)) {
			board[row][col] = num;

			if (generateSudoku(board, row, col + 1)) {
				return true;
			}

			// 回溯
			board[row][col] = EMPTY;
		}
	}

	return false;
}

// 打印数独游戏
void printSudoku(const vector<vector<int>>& board) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == EMPTY) {
				std::cout << "$ ";
			}
			else {
				std::cout << board[i][j] << " ";
			}
		}
		cout << endl;
	}
}


bool solveSudoku(vector<vector<int>>& board, int row, int col, int& solutionCount) {
	if (row == N) {
		solutionCount++;
		return true;
	}

	if (col == N) {
		return solveSudoku(board, row + 1, 0, solutionCount);
	}

	if (board[row][col] != EMPTY) {
		return solveSudoku(board, row, col + 1, solutionCount);
	}

	for (int num = 1; num <= 9; num++) {
		if (isValid(board, row, col, num)) {
			board[row][col] = num;

			if (solveSudoku(board, row, col + 1, solutionCount)) {
				if (solutionCount > 1) {
					return true;
				}
			}

			board[row][col] = EMPTY;
		}
	}

	return false;
}

bool hasMultipleSolutions(vector<vector<int>>& board) {
	vector<vector<int>> tempBoard = board;
	int solutionCount = 0;
	solveSudoku(tempBoard, 0, 0, solutionCount);
	return solutionCount > 1;
}

// 挖空指定数量的数字
void digHoles(vector<vector<int>>& board, int difficulty, bool require_one_solution, int numHoles) {
	// 根据难度级别确定挖空的数量
	if (!numHoles) {//没指定洞的数量，默认是0
		if (difficulty == 1) {
			numHoles = 10; // 简单难度，挖空10个数字
		}
		else if (difficulty == 2) {
			numHoles = 25; // 中等难度，挖空25个数字
		}
		else if (difficulty == 3) {
			numHoles = 40; // 困难难度，挖空40个数字
		}
	}
	cout << "挖空数量:" << numHoles << endl;


	while (numHoles > 0) {
		int row = rand() % N;
		int col = rand() % N;

		if (board[row][col] != EMPTY) {
			int temp = board[row][col];
			board[row][col] = EMPTY;

			// 检查挖空后的数独是否有唯一解，如果不唯一，则回滚挖空操作
			if (require_one_solution && hasMultipleSolutions(board)) {
				board[row][col] = temp;
			}
			else {
				numHoles--;
			}
		}
	}
}

void printBoard(const vector<vector<int>>& board) {
	for (const auto& row : board) {
		for (int num : row) {
			cout << num << " ";
		}
		cout << endl;
	}
}

void printSolutions(const vector<vector<vector<int>>>& solutions) {
	for (const auto& solution : solutions) {
		printBoard(solution);
		cout << "-------------------" << endl;
	}
}

void solve(vector<vector<int>>& board, vector<vector<vector<int>>>& solutions, int row, int col) {
	if (row == N) {
		solutions.push_back(board);  // 找到一种解，将其存储到解集中
		return;
	}

	if (col == N) {
		solve(board, solutions, row + 1, 0);  // 转到下一行的第一列
		return;
	}

	if (board[row][col] != EMPTY) {
		solve(board, solutions, row, col + 1);  // 当前位置已经有数字，跳到下一列
		return;
	}

	for (int num = 1; num <= 9; num++) {
		if (isValid(board, row, col, num)) {
			board[row][col] = num;

			solve(board, solutions, row, col + 1);

			board[row][col] = EMPTY;  // 回溯
		}
	}
}

void solveSudoku(vector<vector<int>>& board) {
	vector<vector<vector<int>>> solutions;
	solve(board, solutions, 0, 0);
	printSolutions(solutions);
}


int path = 0, diff = 1, lholes, rholes, flag = false, holes;
unsigned long int final_count, game_count;

int main(int argc, char* argv[]) {
	// 初始化数独棋盘
	vector<vector<int>> board(N, vector<int>(N, EMPTY));

	try {
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-c") == 0) {
				if (i + 1 < argc) {
					char* value = argv[i + 1];
					// do something with value
					char* t = nullptr;
					final_count = strtol(value, &t, 10);
					if (*t != '\0') {
						throw string("转换失败\n"); // 转换失败
					}
					else {
						if (final_count < 1 || final_count>1000000) {
							throw string("-c的参数范围需要限制在【1-1000000】\n");
						}
					}
				}
			}
			else if (strcmp(argv[i], "-s") == 0) {
				if (i + 1 < argc) {
					char* value = argv[i + 1];
					// do something with value
					std::ifstream file(value);
					if (!file.is_open()) {
						throw string("Failed to open file:%s " + string(value));
					}

					char c;
					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							c = file.get();
							//cout << c << "|";
							if (c == ' ' || c == '\n') {
								j--;
								continue;
							}
							else if (c == '$') {
								board[i][j] = EMPTY;
							}
							else {
								board[i][j] = static_cast<int>(c) - 48;
							}
						}
					}

					file.close();
					cout << "数独游戏的解：" << endl;
					solveSudoku(board);
					return 0;
				}
			}
			else if (strcmp(argv[i], "-n") == 0) {
				if (i + 1 < argc) {
					char* value = argv[i + 1];
					// do something with value
					char* t = nullptr;
					game_count = strtol(value, &t, 10);
					if (*t != '\0') {
						throw string("转换失败\n"); // 转换失败
					}
					else {
						if (game_count < 1 || game_count>10000) {
							throw string("-n的参数范围需要限制在【1-10000】\n");
						}
					}
				}
			}
			else if (strcmp(argv[i], "-m") == 0) {
				if (i + 1 < argc) {
					if (game_count == 0)throw string("-m参数需与-n参数同时使用！请检查！\n");
					char* value = argv[i + 1];
					// do something with value
					char* t = nullptr;
					diff = stoi(value);
					if (*t != '\0') {
						throw string("转换失败\n"); // 转换失败
					}
					else {
						if (diff < 1 || diff>3) {
							throw string("-m的参数范围需要限制在【1-3】\n");
						}
					}
				}
			}
			else if (strcmp(argv[i], "-r") == 0) {
				if (i + 1 < argc) {
					if (game_count == 0)throw string("-r参数需与-n参数同时使用！请检查！\n");
					char* value = argv[i + 1];
					string span = value;

					int pos = span.find('~');
					if (pos < 0)throw string("请输入正确的数量范围，如\"20~55\"");
					else {
						lholes = stoi(span.substr(0, pos));
						rholes = stoi(span.substr(pos + 1, span.length()));
						//cout << "l:" << lholes << " r:" << rholes << endl;
						if (lholes > rholes)throw string("波浪线左边应小于右边！\n");
						if (lholes < 20 || rholes>55)throw("挖空的数量范围应限制在【20-55】！\n");
						holes = rand() % (rholes - lholes + 1) + lholes;
						cout << "holes:" << holes << endl;
					}
				}
			}
			else if (strcmp(argv[i], "-u") == 0) {
				if (game_count == 0)throw string("-u参数需与-n参数同时使用！请检查！\n");
				flag = true;
			}
		}
	}
	catch (string str) {
		std::cout << "Exception:" << str << endl;
		return -1;
	};




	// 设置随机数种子
	srand(time(0));

	if (final_count) {//生成指定个数的数独终盘
		// 打印数独终局
		cout << "数独终局：" << endl;
		for (int i = 0; i < final_count; i++) {
			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					board[r][c] = 0;
				}
			}
			// 生成数独终局
			generateSudoku(board, 0, 0);
			printSudoku(board);
			cout << "-------------------" << endl;
		}
	}
	if (game_count) {//生成指定个数的数独
		// 打印数独游戏
		cout << "数独游戏(空格显示为$)：" << endl;
		for (int i = 0; i < game_count; i++) {
			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					board[r][c] = 0;
				}
			}
			// 生成数独终局
			generateSudoku(board, 0, 0);
			digHoles(board, diff, flag, holes);
			printSudoku(board);
			cout << "-------------------" << endl << endl;
		}
	}


	//// 挖空指定数量的数字
	//int difficulty;
	//cout << "请输入游戏难度(1-3)：";
	//cin >> difficulty;
	//digHoles(board, difficulty, true);

	//// 打印数独游戏
	//cout << "数独游戏(空格显示为$)：" << endl;
	//printSudoku(board);
	//cout << "数独游戏的解：" << endl;
	//solveSudoku(board);

	return 0;
}

