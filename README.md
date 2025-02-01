# Monte Carlo Options Pricing

## Overview
This project implements a **Monte Carlo** simulation to estimate the price of European call and put options using multi-threaded parallel processing in C++.

## Features
- **European call and put option pricing**
- **Monte Carlo simulation** with normally distributed random noise
- **Multi-threading** support for faster computations
- **Standard error (SE)** calculation for accuracy
- **Optimized** for high-performance computation

## How It Works
The Monte Carlo method simulates different possible future stock prices by:
1. Generating random stock price movements using a normal distribution.
2. Computing option payoffs based on whether it is a call or put option.
3. Taking the discounted average of all simulated payoffs to estimate the option price.
4. Calculating the standard error for the simulation.

## Formula Used

### Stock Price Simulation
\[
S_T = S_0 \times e^{\left(r - 0.5 \times \sigma^2\right) T + \sigma \times \sqrt{T} \times Z}
\]
Where:
- \( S_T \) = stock price at time \( T \)
- \( S_0 \) = initial stock price
- \( r \) = risk-free interest rate
- \( \sigma \) = volatility
- \( T \) = time to maturity (in years)
- \( Z \) = standard normal random variable (\( Z \sim N(0,1) \))

### Call Option Payoff
\[
\max(S_T - K, 0)
\]

### Put Option Payoff
\[
\max(K - S_T, 0)
\]

## Usage

### Compiling the Code
To compile and run the Monte Carlo Options Pricing program:
```bash
g++ -o monteCarlo monteCarlo.cpp -std=c++11 -pthread -O3
./monteCarlo


## Modifying Simulation Parameters
Inside `main()`, update the following parameters:

```cpp
Copy
Edit
double initialStockPrice = 239.36; // Initial stock price
double strikePrice       = 242.50; // Strike price
double riskFreeRate      = 0.0417; // Risk-free rate
double volatility        = 0.3052; // Volatility
double timeToMaturity    = 0.063;  // Time to maturity (years)
long simulationCount     = 10000000; // Number of Monte Carlo simulations



Sources

https://www.youtube.com/watch?v=7ESK5SaP-bc

https://www.youtube.com/watch?v=l9ta2nLXoao

https://www.youtube.com/watch?v=pR32aii3shk&t=1557s

https://www.youtube.com/watch?v=1eD8M3fYwoA

https://www.youtube.com/watch?v=w_BjFmbwbYA&t=35s

Wikipedia: Monte Carlo Method

Investopedia: Option Pricing Models

