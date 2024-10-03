#pragma once
// GPU_621_NSA_LAB_1.cpp : Gleison Vieira Dutra 119237220
#pragma once


class myObj {
public:
    std::chrono::microseconds microS;
    double durationMs;
    double durationS;
    std::atomic<long long> FinalResult;
};

void static AddPortion(const int arr[], int start, int end, std::atomic<long long>& TFinalResult);

void static sSum(myObj& sequentialRes, const int NumbersToAdd[], int sz);

void static t2Sum(myObj& threadCount2Res, const int NumbersToAdd[]);

void static t4Sum(myObj& threadCount4Res, const int NumbersToAdd[]);

void static t8Sum(myObj& threadCount8Res, const int NumbersToAdd[]);

void static randomGen(int* myArr, int sz, int up, int low);