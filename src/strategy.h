/*
 * File: strategy.h
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:36:09 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:36:09 pm
 * -----
 */

#ifndef _STRATEGY_H
#define _STRATEGY_H

#include <string>
#include <functional>

#include "data.h"
#include "order.h"

class Strategy
{
public:
    using ExecuteOrderCallback = std::function<void(const Order_s &)>; // the order execution callback of engine
    virtual void initialize(const ExecuteOrderCallback &callback) = 0;
    virtual int onBar(const DailyBar &bar, double *pred) = 0; // handle daily bar
    virtual void executeOrder(const Order_s &order) = 0;
    virtual void getCurMoneyAndStock(double *money, double *stock) = 0;

protected:
    double curStock, curMoney;
    ExecuteOrderCallback orderCallback;
};

#endif