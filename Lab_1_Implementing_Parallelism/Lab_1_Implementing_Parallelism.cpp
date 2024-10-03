// GPU_621_NSA_LAB_1.cpp : Gleison Vieira Dutra 119237220

#include <iostream>
#include <stdlib.h>  
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <iomanip>
#include <mutex>
#include "GPU_621_NSA_LAB_1.h"

using namespace std::chrono;
using namespace std;

int main()
{
    int arraySize = 100000000; //one hundred million
    int randomLowerValue = 1;
    int randomUpperValue = 1000;
    long long SFinalResult = 0;

    myObj sequentialRes{};
    myObj threadCount2Res;
    myObj threadCount4Res{};
    myObj threadCount8Res{};


    //Because of the length of the array, will initialize it in the heap instead of stack. 
    int* NumbersToAdd = (int*)malloc(arraySize * sizeof(int));

    randomGen(NumbersToAdd, arraySize, randomUpperValue, randomLowerValue);

    sSum(sequentialRes, NumbersToAdd, arraySize);
    t2Sum(threadCount2Res, NumbersToAdd);
    t4Sum(threadCount4Res, NumbersToAdd);
    t8Sum(threadCount8Res, NumbersToAdd);

    // Now to print all values on screen
    cout << "Final Results: \n\n";

    cout << "Sommation result in each stage:\n";
    cout << "Sequential     = " << sequentialRes.FinalResult << " \n";
    cout << "With 2 threads = " << threadCount2Res.FinalResult << " \n";
    cout << "With 4 threads = " << threadCount4Res.FinalResult << " \n";
    cout << "With 8 threads = " << threadCount8Res.FinalResult << " \n";


    cout << "\n Results comparison: \n";

    cout << "-----------------------------------------------------------------\n";
    cout << "| Execution Type |   Time uS     |     Time mS    |  Time S     |\n";
    cout << "-----------------------------------------------------------------\n";

    // Sequential results
    cout << "| Sequential     |  " << std::setw(7) << sequentialRes.microS.count() << " uS   |  "
        << std::fixed << std::setprecision(2) << std::setw(8) << sequentialRes.durationMs << " mS   |  "
        << std::fixed << std::setprecision(2) << std::setw(6) << sequentialRes.durationS << " S   |\n";

    // 2 Thread results
    cout << "| 2 Threads      |  " << std::setw(7) << threadCount2Res.microS.count() << " uS   |  "
        << std::fixed << std::setprecision(2) << std::setw(8) << threadCount2Res.durationMs << " mS   |  "
        << std::fixed << std::setprecision(2) << std::setw(6) << threadCount2Res.durationS << " S   |\n";

    // 4 Thread results
    cout << "| 4 Threads      |  " << std::setw(7) << threadCount4Res.microS.count() << " uS   |  "
        << std::fixed << std::setprecision(2) << std::setw(8) << threadCount4Res.durationMs << " mS   |  "
        << std::fixed << std::setprecision(2) << std::setw(6) << threadCount4Res.durationS << " S   |\n";

    // 8 Thread results
    cout << "| 8 Threads      |  " << std::setw(7) << threadCount8Res.microS.count() << " uS   |  "
        << std::fixed << std::setprecision(2) << std::setw(8) << threadCount8Res.durationMs << " mS   |  "
        << std::fixed << std::setprecision(2) << std::setw(6) << threadCount8Res.durationS << " S   |\n";

    cout << "-----------------------------------------------------------------\n";

    // Calculate the percentage improvement
    double t2ImprovementPercentage = ((sequentialRes.microS.count() - threadCount2Res.microS.count()) / static_cast<double>(sequentialRes.microS.count())) * 100;
    double t4ImprovementPercentage = ((sequentialRes.microS.count() - threadCount4Res.microS.count()) / static_cast<double>(sequentialRes.microS.count())) * 100;
    double t8ImprovementPercentage = ((sequentialRes.microS.count() - threadCount8Res.microS.count()) / static_cast<double>(sequentialRes.microS.count())) * 100;

    cout << "\nImprovement using 2 Threads: " << t2ImprovementPercentage << "%\n";
    cout << "Improvement using 4 Threads: " << t4ImprovementPercentage << "%\n";
    cout << "Improvement using 8 Threads: " << t8ImprovementPercentage << "%\n";

}

void static AddPortion(const int arr[], int start, int end, std::atomic<long long>& TFinalResult)
{
    std::mutex result_mutex;
    long long localResult = 0;
    for (int i = start; i < end; i++) {
        localResult += arr[i];
    }
    std::lock_guard<std::mutex> guard(result_mutex);
    TFinalResult += localResult;
}

void static sSum(myObj& sequentialRes, const int NumbersToAdd[], int sz) {

    auto sStart = high_resolution_clock::now();

    AddPortion(NumbersToAdd, 0, sz, sequentialRes.FinalResult);

    auto sStop = high_resolution_clock::now();


    // Let's calculate the time it took for the sequential function to add up all values
    sequentialRes.microS = duration_cast<microseconds>(sStop - sStart);
    sequentialRes.durationMs = static_cast<double>(sequentialRes.microS.count()) / 1000.00;
    sequentialRes.durationS = static_cast<double>(sequentialRes.microS.count()) / 1000000.00;
}

void static t2Sum(myObj& threadCount2Res, const int NumbersToAdd[]) {
    // Now let's do the same operations, using 2 threads instead
    auto T2Start = high_resolution_clock::now();

    // creating multiple threads to handle each portion of the array 
    std::thread t1(AddPortion, NumbersToAdd, 0, 50000000, std::ref(threadCount2Res.FinalResult));
    std::thread t2(AddPortion, NumbersToAdd, 50000000, 100000000, std::ref(threadCount2Res.FinalResult));

    t1.join();
    t2.join();

    auto T2Stop = high_resolution_clock::now();

    // Let's calculate the time it took for the parallel function to add up all values
    threadCount2Res.microS = duration_cast<microseconds>(T2Stop - T2Start);
    threadCount2Res.durationMs = static_cast<double>(threadCount2Res.microS.count()) / 1000.00;
    threadCount2Res.durationS = static_cast<double>(threadCount2Res.microS.count()) / 1000000.00;
}

void static t4Sum(myObj& threadCount4Res, const int NumbersToAdd[]) {
    // Now let's do the same operations, using 4 threads instead
    auto T4Start = high_resolution_clock::now();

    // creating multiple threads to handle each portion of the array 
    std::thread t1(AddPortion, NumbersToAdd, 0, 25000000, std::ref(threadCount4Res.FinalResult));
    std::thread t2(AddPortion, NumbersToAdd, 25000000, 50000000, std::ref(threadCount4Res.FinalResult));
    std::thread t3(AddPortion, NumbersToAdd, 50000000, 75000000, std::ref(threadCount4Res.FinalResult));
    std::thread t4(AddPortion, NumbersToAdd, 75000000, 100000000, std::ref(threadCount4Res.FinalResult));

    // Joining threads to ensure they complete before moving on
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    auto T4Stop = high_resolution_clock::now();

    // Let's calculate the time it took for the parallel function to add up all values
    threadCount4Res.microS = duration_cast<microseconds>(T4Stop - T4Start);
    threadCount4Res.durationMs = static_cast<double>(threadCount4Res.microS.count()) / 1000.00;
    threadCount4Res.durationS = static_cast<double>(threadCount4Res.microS.count()) / 1000000.00;
}

void static t8Sum(myObj& threadCount8Res, const int NumbersToAdd[]) {
    // Now let's do the same operations, using 8 threads instead
    auto T8Start = high_resolution_clock::now();

    // creating multiple threads to handle each portion of the array 
    std::thread th1_8(AddPortion, NumbersToAdd, 0, 12500000, std::ref(threadCount8Res.FinalResult));
    std::thread th2_8(AddPortion, NumbersToAdd, 12500000, 25000000, std::ref(threadCount8Res.FinalResult));
    std::thread th3_8(AddPortion, NumbersToAdd, 25000000, 37500000, std::ref(threadCount8Res.FinalResult));
    std::thread th4_8(AddPortion, NumbersToAdd, 37500000, 50000000, std::ref(threadCount8Res.FinalResult));
    std::thread th5_8(AddPortion, NumbersToAdd, 50000000, 62500000, std::ref(threadCount8Res.FinalResult));
    std::thread th6_8(AddPortion, NumbersToAdd, 62500000, 75000000, std::ref(threadCount8Res.FinalResult));
    std::thread th7_8(AddPortion, NumbersToAdd, 75000000, 87500000, std::ref(threadCount8Res.FinalResult));
    std::thread th8_8(AddPortion, NumbersToAdd, 87500000, 100000000, std::ref(threadCount8Res.FinalResult));

    // Joining threads to ensure they complete before moving on
    th1_8.join();
    th2_8.join();
    th3_8.join();
    th4_8.join();
    th5_8.join();
    th6_8.join();
    th7_8.join();
    th8_8.join();

    auto T8Stop = high_resolution_clock::now();

    // Let's calculate the time it took for the parallel function to add up all values
    threadCount8Res.microS = duration_cast<microseconds>(T8Stop - T8Start);
    threadCount8Res.durationMs = static_cast<double>(threadCount8Res.microS.count()) / 1000.00;
    threadCount8Res.durationS = static_cast<double>(threadCount8Res.microS.count()) / 1000000.00;
}

void static randomGen(int* myArr, int sz, int up, int low) {

    //Seed random number generator with current time so it generates different sequence of numbers every time it runs
    srand(static_cast<unsigned int>(time(0)));

    // loop over the array and give a value to each index
    for (int i = 0; i < sz; i++) {

        myArr[i] = rand() % up + low;
    }
}