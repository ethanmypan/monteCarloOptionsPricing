#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <limits>
#include <thread>
#include <mutex>
#include <chrono>

#include <curl/curl.h>


using namespace std;
mutex mtx;
// Function to generate normally distributed random numbers
double generateRandomNoise(double mean, double stddev) {
    static mt19937 randomGenerator(random_device{}());
    normal_distribution<double> distribution(mean, stddev);
    return distribution(randomGenerator);
}

// Function to calculate the payoff of a eu call option
double calculateCallPayoff(double stockPrice, double strikePrice) {
    return max(stockPrice - strikePrice, 0.0);
}

// Function to calculate the payoff of a eu put option
double calculatePutPayoff(double stockPrice, double strikePrice) {
    return max(strikePrice - stockPrice, 0.0);
}

// Thread function to run Monte Carlo Simulation in parallel
void monteCarloWorker(double initialStockPrice, double strikePrice, double riskFreeRate, double volatility, double timeToMaturity, long simulationCount, bool isCallOption, vector<double>& payoffs) {
    // double localPayoff = 0.0;
    for (long i = 0; i < simulationCount; ++i) {
        double finalStockPrice = initialStockPrice * exp((riskFreeRate - 0.5 * volatility * volatility) * timeToMaturity + volatility * sqrt(timeToMaturity) * generateRandomNoise(0.0, 1.0));
        double payoff = isCallOption ? calculateCallPayoff(finalStockPrice, strikePrice) : calculatePutPayoff(finalStockPrice, strikePrice);
        payoffs[i] += payoff;
    }
    // lock_guard<mutex> lock(mtx);
    // totalPayoff += localPayoff;
}
pair<double, double> monteCarloOptionPricing(double initialStockPrice, double strikePrice, double riskFreeRate, double volatility, double timeToMaturity, long simulationCount, bool isCallOption) {
    int numThreads = thread::hardware_concurrency();
    if(numThreads == 0){
        numThreads = 1;
    }
    vector<thread> threads;
    vector<vector<double>> partialPayoffs(numThreads, vector<double>(simulationCount / numThreads, 0.0));
    long simulationsPerThread = simulationCount / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(monteCarloWorker, initialStockPrice, strikePrice, riskFreeRate, volatility, timeToMaturity, simulationsPerThread, isCallOption, ref(partialPayoffs[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    vector <double> allPayoffs;
    for (const auto& payoffs : partialPayoffs) {
        allPayoffs.insert(allPayoffs.end(), payoffs.begin(), payoffs.end());
}
    double totalPayoff = 0.0;
    for (const auto& payoff : allPayoffs) {
        totalPayoff += payoff;
    }
    double averagePayoff = totalPayoff / static_cast<double>(simulationCount);
    double discountedPrice = exp(-riskFreeRate * timeToMaturity) * averagePayoff;

    // se calculation
    double variance = 0.0;
    for (const auto& payoff : allPayoffs) {
        variance += pow(payoff - averagePayoff, 2);
    }
    variance /= static_cast<double>(simulationCount);
    double standardError = sqrt(variance / simulationCount);
    return {discountedPrice, standardError};
}

/*
// Monte Carlo Simulation for eu option pricing
double monteCarloOptionPricing(double initialStockPrice, double strikePrice, double riskFreeRate, double volatility, double timeToMaturity, int simulationCount, bool isCallOption) {
    double totalPayoff = 0.0;

    for (int i = 0; i < simulationCount; ++i) {
        // Generate a random price path
         double finalStockPrice = initialStockPrice * exp((riskFreeRate - 0.5 * volatility * volatility) * timeToMaturity + volatility * sqrt(timeToMaturity) * generateRandomNoise(0.0, 1.0));

        // Calculate the payoff for this path
        double payoff = isCallOption ? calculateCallPayoff(finalStockPrice, strikePrice) : calculatePutPayoff(finalStockPrice, strikePrice);

        // Accumulate the payoff
        totalPayoff += payoff;
    }

    // Calculate the average payoff and discount it to present value
    double averagePayoff = totalPayoff / static_cast<double>(simulationCount);
    return exp(-riskFreeRate * timeToMaturity) * averagePayoff;
}

*/
int main() {
    auto startTime = chrono::high_resolution_clock::now();
    // Option parameters
    // Option parameters

    double initialStockPrice = 239.36;   // Initial stock price
    double strikePrice = 242.50;         // Strike price
    double riskFreeRate = 0.0417;         // Risk-free rate
    double volatility = 0.3052;            // Volatility
    double timeToMaturity = 0.063;        // Time to maturity (in years)
    long simulationCount = 10000000;    // Number of Monte Carlo simulations
    
    auto [callPrice, callError] = monteCarloOptionPricing(initialStockPrice, strikePrice, riskFreeRate, volatility, timeToMaturity, simulationCount, true);
    auto [putPrice, putError] = monteCarloOptionPricing(initialStockPrice, strikePrice, riskFreeRate, volatility, timeToMaturity, simulationCount, false);


    // Calculate option prices
    // double callOptionPrice = monteCarloOptionPricing(initialStockPrice, strikePrice, riskFreeRate, volatility, timeToMaturity, simulationCount, true);
    // double putOptionPrice = monteCarloOptionPricing(initialStockPrice, strikePrice, riskFreeRate, volatility, timeToMaturity, simulationCount, false);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedTime = endTime - startTime;
    // Output the results
    cout << "European Call Option Price: " << callPrice << " +- error: " << callError<<endl;
    cout << "European Put Option Price: " << putPrice << " +- error: "<< putError<<endl;
    cout << "Execution Time: " << elapsedTime.count() << " seconds" << endl;

    return 0;
}