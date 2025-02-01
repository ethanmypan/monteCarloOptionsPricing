Monte Carlo Options Pricing

Overview

This project implements a Monte Carlo simulation to estimate the price of European call and put options using multi-threaded parallel processing in C++.

Features

Implements European call and put option pricing

Uses Monte Carlo simulation with normally distributed random noise

Supports multi-threading for faster computations

Computes standard error (SE) estimation for accuracy

Optimized for high-performance computation

How It Works

The Monte Carlo method simulates different possible future stock prices by:

Generating random stock price movements using a normal distribution.

Computing option payoffs based on whether it is a call or put option.

Taking the discounted average of all simulated payoffs to estimate the option price.

Calculating the standard error for the simulation.

Formula Used

Stock Price Simulation

S_T = S_0 \times e^{(r - 0.5 \times \sigma^2) T + \sigma \times \sqrt{T} \times Z}

where:

 = stock price at time T

 = initial stock price

 = risk-free interest rate

 = volatility

 = time to maturity

 = standard normal random variable

Call Option Payoff

\max(S_T - K, 0)

Put Option Payoff

\max(K - S_T, 0)

Usage

Compiling the Code

To compile and run the Monte Carlo Options Pricing program:

# Compile the program
g++ -o monteCarlo monteCarlo.cpp -std=c++11 -pthread -O3

# Run the program
./monteCarlo

Modifying Simulation Parameters

Inside main(), update the following parameters:

double initialStockPrice = 239.36;   // Initial stock price
double strikePrice = 242.50;         // Strike price
double riskFreeRate = 0.0417;        // Risk-free rate
double volatility = 0.3052;          // Volatility
double timeToMaturity = 0.063;       // Time to maturity (years)
long simulationCount = 10000000;     // Number of Monte Carlo simulations

Performance Optimization

Uses multi-threading to distribute simulations across CPU cores.

Applies exp(-rT) discounting for accuracy.

Implements vectorized storage for efficient memory usage.

Example Output

European Call Option Price: 4.35 ± error: 0.05
European Put Option Price: 3.12 ± error: 0.04
Execution Time: 2.35 seconds

Dependencies

C++11 or later

g++ Compiler (for Linux/macOS)

pthread library (for multi-threading support)


Sources

https://www.youtube.com/watch?v=7ESK5SaP-bc

https://www.youtube.com/watch?v=l9ta2nLXoao

https://www.youtube.com/watch?v=pR32aii3shk&t=1557s

https://www.youtube.com/watch?v=1eD8M3fYwoA

https://www.youtube.com/watch?v=w_BjFmbwbYA&t=35s

Wikipedia: Monte Carlo Method

Investopedia: Option Pricing Models
