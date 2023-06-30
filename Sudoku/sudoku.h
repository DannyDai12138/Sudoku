#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H
#include "./SudokuUnitTest/pch.h"
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <ctime>
#include <random>
using namespace std;

#define MAX_SPACE 64
#define MIN_SPACE 20

#define EASY 1
#define NORMAL 2
#define HARD 3

const int Maxn = 1e6 + 10;
const int Maxm = 10;

static int Step[80][Maxm];
static int Permutation[Maxn][Maxm];

static string end_game_path = "./end_game.txt";
static string new_game_path = "./game.txt";
static string solution_path = "./sudoku.txt";

static int a[11][11];//存储数独游戏
static int b[11];//每行已知数最多
static int bid[11];//b的id
static int bbid;//bid第几个
static int c[11];//每列已知数最多
static int cid[11];//c的id
static int ccid;//cid第几个
static int alltheanswer;//所有解
static int wanttheanswer = 1;

bool Permutate_Temp(int source[], int start, int end, int target[6][3], int& line);
bool Permutate_Step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm]);
bool Permutate_Permutation(int source[], int start, int end, int target[Maxn][Maxm], int& line, int max_num);
bool Generate_EndGame(const string& path, int num);
bool checkx(int x);
bool checky(int y);
bool jggfz(int djgg);
bool dfs(int na, int nb, const string& output_path);
bool solve_single_sudoku(const string& output_path, bool need_output);
bool Play_Game(const string& input_path, const string& output_path);
bool Generate_NewGame(const string& input_path, const string& output_path, int num, bool set_difficulty, int difficulty, int min_space, int max_space, bool only_solution);

#endif //SUDOKU_SUDOKU_H
