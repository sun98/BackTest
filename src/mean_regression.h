/*
 * File: mean_regression.h
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:49:34 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:49:34 pm
 * -----
 */

#ifndef _MEAN_REGRESSION_H
#define _MEAN_REGRESSION_H

#include <deque>

#include "engine.h"
#include "strategy.h"

// mean regression strategy
class MeanRegression : public Strategy
{
private:
    double initMoney;
    const DailyBar *lastBar;
    std::deque<double> prices;
    int windowSize;
    double meanValue;
    int curStock;

public:
    MeanRegression(int size, double init) : windowSize(size), initMoney(init){};
    void initialize(const ExecuteOrderCallback &callback) override;
    int onBar(const DailyBar &bar, double *pred) override;
    void executeOrder(const Order_s &order) override;
    void getCurMoneyAndStock(double *money, double *stock) override;
};

#endif