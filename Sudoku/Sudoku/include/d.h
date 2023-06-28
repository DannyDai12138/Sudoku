// Copyright 2023 Dai Tingjun,Yang Boyu
#pragma once
#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const int N = 9;
const int EMPTY = 0;

bool isValid(vector<vector<int>>* board, int row, int col, int num);
bool generateSudoku(vector<vector<int>>* board, int row, int col);
void printSudoku(const vector<vector<int>>& board);
bool solveSudoku(vector<vector<int>>* board, \
    int row, int col, \
    int* solutionCount);
bool hasMultipleSolutions(vector<vector<int>>* board);
void digHoles(vector<vector<int>>* board, \
    int difficulty, \
    bool require_one_solution, \
    int numHoles);
void printBoard(const vector<vector<int>>& board, bool f);
void printSolutions(const vector<vector<vector<int>>>& solutions, bool f);
void solve(vector<vector<int>>* board, \
    vector<vector<int>>* solutions, \
    int row, int col);
void solveSudoku(vector<vector<int>>* board, bool f);
int main(int argc, char* argv[]);
int Testfinalcount();
int Testgamecount();

#endif  // SUDOKU_H
