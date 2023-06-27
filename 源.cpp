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

// �����(row, col)λ���Ϸ�������num�Ƿ�Ϸ�
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
	// ���ͬһ���Ƿ�����ͬ����
	for (int i = 0; i < N; i++) {
		if (board[i][col] == num) {
			return false;
		}
	}

	// ���ͬһ���Ƿ�����ͬ����
	for (int j = 0; j < N; j++) {
		if (board[row][j] == num) {
			return false;
		}
	}

	// ���ͬһ���Ź����Ƿ�����ͬ����
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

// �ݹ�����������վ�
bool generateSudoku(vector<vector<int>>& board, int row, int col) {
	// ��ֹ�������Ѿ����������һ�У������վ����ɳɹ�
	if (row == N) {
		return true;
	}

	// ����Ѿ����˵�ǰ�е����һ�У���ת����һ�еĵ�һ��
	if (col == N) {
		return generateSudoku(board, row + 1, 0);
	}

	// �����ǰλ���Ѿ������֣���������һ��
	if (board[row][col] != EMPTY) {
		return generateSudoku(board, row, col + 1);
	}

	// �����������

	random_device rd;
	mt19937 rng(rd());

	vector<int> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	shuffle(nums.begin(), nums.end(), rng);  // ����������ֵ�˳��

	for (int num : nums) {
		if (isValid(board, row, col, num)) {
			board[row][col] = num;

			if (generateSudoku(board, row, col + 1)) {
				return true;
			}

			// ����
			board[row][col] = EMPTY;
		}
	}

	return false;
}

// ��ӡ������Ϸ
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

// �ڿ�ָ������������
void digHoles(vector<vector<int>>& board, int difficulty, bool require_one_solution, int numHoles) {
	// �����Ѷȼ���ȷ���ڿյ�����
	if (!numHoles) {//ûָ������������Ĭ����0
		if (difficulty == 1) {
			numHoles = 10; // ���Ѷȣ��ڿ�10������
		}
		else if (difficulty == 2) {
			numHoles = 25; // �е��Ѷȣ��ڿ�25������
		}
		else if (difficulty == 3) {
			numHoles = 40; // �����Ѷȣ��ڿ�40������
		}
	}
	cout << "�ڿ�����:" << numHoles << endl;


	while (numHoles > 0) {
		int row = rand() % N;
		int col = rand() % N;

		if (board[row][col] != EMPTY) {
			int temp = board[row][col];
			board[row][col] = EMPTY;

			// ����ڿպ�������Ƿ���Ψһ�⣬�����Ψһ����ع��ڿղ���
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
		solutions.push_back(board);  // �ҵ�һ�ֽ⣬����洢���⼯��
		return;
	}

	if (col == N) {
		solve(board, solutions, row + 1, 0);  // ת����һ�еĵ�һ��
		return;
	}

	if (board[row][col] != EMPTY) {
		solve(board, solutions, row, col + 1);  // ��ǰλ���Ѿ������֣�������һ��
		return;
	}

	for (int num = 1; num <= 9; num++) {
		if (isValid(board, row, col, num)) {
			board[row][col] = num;

			solve(board, solutions, row, col + 1);

			board[row][col] = EMPTY;  // ����
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
	// ��ʼ����������
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
						throw string("ת��ʧ��\n"); // ת��ʧ��
					}
					else {
						if (final_count < 1 || final_count>1000000) {
							throw string("-c�Ĳ�����Χ��Ҫ�����ڡ�1-1000000��\n");
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
					cout << "������Ϸ�Ľ⣺" << endl;
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
						throw string("ת��ʧ��\n"); // ת��ʧ��
					}
					else {
						if (game_count < 1 || game_count>10000) {
							throw string("-n�Ĳ�����Χ��Ҫ�����ڡ�1-10000��\n");
						}
					}
				}
			}
			else if (strcmp(argv[i], "-m") == 0) {
				if (i + 1 < argc) {
					if (game_count == 0)throw string("-m��������-n����ͬʱʹ�ã����飡\n");
					char* value = argv[i + 1];
					// do something with value
					char* t = nullptr;
					diff = stoi(value);
					if (*t != '\0') {
						throw string("ת��ʧ��\n"); // ת��ʧ��
					}
					else {
						if (diff < 1 || diff>3) {
							throw string("-m�Ĳ�����Χ��Ҫ�����ڡ�1-3��\n");
						}
					}
				}
			}
			else if (strcmp(argv[i], "-r") == 0) {
				if (i + 1 < argc) {
					if (game_count == 0)throw string("-r��������-n����ͬʱʹ�ã����飡\n");
					char* value = argv[i + 1];
					string span = value;

					int pos = span.find('~');
					if (pos < 0)throw string("��������ȷ��������Χ����\"20~55\"");
					else {
						lholes = stoi(span.substr(0, pos));
						rholes = stoi(span.substr(pos + 1, span.length()));
						//cout << "l:" << lholes << " r:" << rholes << endl;
						if (lholes > rholes)throw string("���������ӦС���ұߣ�\n");
						if (lholes < 20 || rholes>55)throw("�ڿյ�������ΧӦ�����ڡ�20-55����\n");
						holes = rand() % (rholes - lholes + 1) + lholes;
						cout << "holes:" << holes << endl;
					}
				}
			}
			else if (strcmp(argv[i], "-u") == 0) {
				if (game_count == 0)throw string("-u��������-n����ͬʱʹ�ã����飡\n");
				flag = true;
			}
		}
	}
	catch (string str) {
		std::cout << "Exception:" << str << endl;
		return -1;
	};




	// �������������
	srand(time(0));

	if (final_count) {//����ָ����������������
		// ��ӡ�����վ�
		cout << "�����վ֣�" << endl;
		for (int i = 0; i < final_count; i++) {
			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					board[r][c] = 0;
				}
			}
			// ���������վ�
			generateSudoku(board, 0, 0);
			printSudoku(board);
			cout << "-------------------" << endl;
		}
	}
	if (game_count) {//����ָ������������
		// ��ӡ������Ϸ
		cout << "������Ϸ(�ո���ʾΪ$)��" << endl;
		for (int i = 0; i < game_count; i++) {
			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					board[r][c] = 0;
				}
			}
			// ���������վ�
			generateSudoku(board, 0, 0);
			digHoles(board, diff, flag, holes);
			printSudoku(board);
			cout << "-------------------" << endl << endl;
		}
	}


	//// �ڿ�ָ������������
	//int difficulty;
	//cout << "��������Ϸ�Ѷ�(1-3)��";
	//cin >> difficulty;
	//digHoles(board, difficulty, true);

	//// ��ӡ������Ϸ
	//cout << "������Ϸ(�ո���ʾΪ$)��" << endl;
	//printSudoku(board);
	//cout << "������Ϸ�Ľ⣺" << endl;
	//solveSudoku(board);

	return 0;
}

