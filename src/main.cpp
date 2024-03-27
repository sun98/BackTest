/*
 * File: main.c
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:35:08 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:35:08 pm
 * -----
 */

#include "engine.h"
#include "file_data_feed.h"
#include "mean_regression.h"

int main()
{
    double initMoney = 10000;
    int window_size = 90;

    BacktestEngine engine;
    FileDataFeed dataFeed("../data/AAPL.csv");
    MeanRegression strategy(window_size, initMoney);

    engine.setDataFeed(&dataFeed);
    engine.setStrategy(&strategy);

    engine.runBacktest();
    engine.showResult();

    return 0;
}