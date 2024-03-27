/*
 * File: engine.cpp
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:37:58 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:37:58 pm
 * -----
 */
#include <iostream>
#include <cmath>

#include "engine.h"

void BacktestEngine::setDataFeed(DataFeed *feed)
{
    dataFeed = feed;
}

void BacktestEngine::setStrategy(Strategy *strat)
{
    strategy = strat;
}

void BacktestEngine::runBacktest()
{
    dataFeed->connect();
    Strategy::ExecuteOrderCallback executeOrderCallback = [&](const Order_s &order)
    {
        executeOrder(order);
    };
    strategy->initialize(executeOrderCallback);
    while (dataFeed->hasNextBar())
    {
        DailyBar &&bar = std::move(dataFeed->getNextBar());
        double pred;
        int res = strategy->onBar(bar, &pred);
        if (res == 0)
        {
            predictions.emplace_back(d2array{pred, bar.close});
        }
    }
    dataFeed->disconnect();
}

void BacktestEngine::executeOrder(const Order_s &order)
{
    double curMoney, curStock;
    strategy->getCurMoneyAndStock(&curMoney, &curStock);
    cumProfit = curMoney + curStock * order.price;
    profits.emplace_back(Profit_s{order.date, cumProfit});
}

double BacktestEngine::calculateIC(const std::vector<d2array> &predictions)
{
    int n = predictions.size();

    double sumPred = 0.0;
    double sumObs = 0.0;
    double sumPredObs = 0.0;
    double sumPredSquared = 0.0;
    double sumObsSquared = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double pred = predictions[i][0];
        double obs = predictions[i][1];
        sumPred += pred;
        sumObs += obs;
        sumPredObs += pred * obs;
        sumPredSquared += pred * pred;
        sumObsSquared += obs * obs;
    }

    double numerator = n * sumPredObs - sumPred * sumObs;
    double denominator = std::sqrt((n * sumPredSquared - sumPred * sumPred) * (n * sumObsSquared - sumObs * sumObs));

    double ic = numerator / denominator;

    return ic;
}
double BacktestEngine::calculateSharpe(const std::vector<Profit_s> &profits)
{
    if (profits.size() < 3)
    {
        return 0;
    }
    std::vector<double> returns;
    double sum = 0;
    for (int i = 1; i < profits.size(); i++)
    {
        double t = log(profits[i].profit / profits[i - 1].profit);
        sum += t;
        returns.push_back(t);
    }
    double mean = sum / returns.size();
    double accum = 0.0;
    std::for_each(std::begin(returns), std::end(returns), [&](const double d)
                  { accum += (d - mean) * (d - mean); });
    double stdev = sqrt(accum / (returns.size() - 1));
    return sqrt(txDays) * (mean - riskFreeRate / txDays) / stdev;
}

void BacktestEngine::showResult()
{
    double initMoney = profits[0].profit;
    std::cout << ">>> init money=" << initMoney << std::endl;

    // show final profit
    std::cout << ">>> final profit=" << cumProfit - initMoney << std::endl;
    std::cout << ">>> final profit rate=" << (cumProfit - initMoney) / initMoney << std::endl;

    // show profit curve
    std::cout << "\n>>> sample profit curve:\n";
    std::cout << "date\t\tprofit\n";
    for (int i = 0; i < profits.size(); i++)
    {
        if (i % (profits.size() / 10) == 0 || i == profits.size() - 1)
        {
            std::cout << profits[i].date << "\t" << profits[i].profit - initMoney << std::endl;
        }
    }

    // show IC
    std::cout << "\n>>> IC=" << calculateIC(predictions) << std::endl;

    // show sharpe
    std::cout << "\n>>> sharpe=" << calculateSharpe(profits) << std::endl;
}