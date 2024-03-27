/*
 * File: mean_regression.cpp
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:41:13 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:41:13 pm
 * -----
 */

#include <iostream>

#include "order.h"
#include "mean_regression.h"

void MeanRegression::initialize(const ExecuteOrderCallback &callback)
{
    orderCallback = callback;
    meanValue = 0;
    curStock = 0;
    curMoney = initMoney;
    std::cout << "strategy initialized" << std::endl;
}

int MeanRegression::onBar(const DailyBar &bar, double *pred)
{
    int ret;

    Order_s order = {
        .symbol = bar.symbol,
        .date = bar.date,
        .price = bar.close,
    };
    if (prices.size() > 0)
    {
        double curMean = meanValue / prices.size();
        int numStocks;
        *pred = curMean;
        if (curMoney > bar.close && bar.close < curMean)
        {
            order.action = OrderAction::ACTION_BUY;
            numStocks = int(curMoney / bar.close);
            curStock += numStocks;
            curMoney -= numStocks * bar.close;
        }
        else if (bar.close > curMean && curStock > 0)
        {
            order.action = OrderAction::ACTION_SELL;
            numStocks = curStock;
            curStock = 0;
            curMoney += numStocks * bar.close;
        }
        else
        {
            order.action = OrderAction::ACTION_KEEP;
        }
        executeOrder(order);
        ret = 0;
    }
    else
    {
        order.action = OrderAction::ACTION_KEEP;
        executeOrder(order);
        ret = -1;
    }
    meanValue += bar.close;
    prices.push_back(bar.close);
    if (prices.size() > windowSize)
    {
        meanValue -= prices.front();
        prices.pop_front();
    }
    return ret;
}

void MeanRegression::executeOrder(const Order_s &order)
{
    if (orderCallback)
    {
        orderCallback(order);
    }
}

void MeanRegression::getCurMoneyAndStock(double *money, double *stock)
{
    if (money == nullptr || stock == nullptr)
    {
        return;
    }
    *money = curMoney;
    *stock = curStock;
}