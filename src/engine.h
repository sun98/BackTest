/*
 * File: engine.h
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:42:53 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:42:53 pm
 * -----
 */

#ifndef _ENGINE_H
#define _ENGINE_H

#include <vector>
#include <iostream>
#include <array>

#include "data.h"
#include "data_feed.h"
#include "strategy.h"
#include "order.h"
#include "data_feed.h"

static const int txDays = 252;
static const double riskFreeRate = 0.0285;

struct DailyProfit
{
    std::string date;
    double profit;
};
typedef struct DailyProfit Profit_s;
typedef std::array<double, 2> d2array;

class BacktestEngine
{
private:
    DataFeed *dataFeed;
    Strategy *strategy;
    double cumProfit = 0.0;
    std::vector<Profit_s> profits;
    std::vector<d2array> predictions;
    double calculateIC(const std::vector<d2array> &predictions);
    double calculateSharpe(const std::vector<Profit_s> &profits);

public:
    BacktestEngine()
    {
        std::cout << "backtest engine initialized\n";
    }
    void setDataFeed(DataFeed *feed);
    void setStrategy(Strategy *strategy);
    void executeOrder(const Order_s &order);
    void runBacktest();
    void showResult();
};

#endif