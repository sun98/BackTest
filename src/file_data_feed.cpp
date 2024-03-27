/*
 * File: file_data_feed.cpp
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:39:33 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:39:33 pm
 * -----
 */

#include <iostream>

#include "file_data_feed.h"

FileDataFeed::FileDataFeed(const std::string &filename) : filename(filename), currentIndex(0)
{
    std::cout << "file data feed initialized\n";
}

bool FileDataFeed::connect()
{
    file.open(filename);
    if (!file.is_open())
    {
        return false;
    }
    initData();
    return true;
}

bool FileDataFeed::disconnect()
{
    if (file.is_open())
    {
        file.close();
    }
    return true;
}

bool FileDataFeed::hasNextBar() const
{
    return currentIndex < data.size();
}

DailyBar FileDataFeed::getNextBar()
{
    if (hasNextBar())
    {
        return data[currentIndex++];
    }
    return DailyBar();
}

void FileDataFeed::initData()
{
    std::string line;
    std::getline(file, line); // skip csv header
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string field;
        DailyBar bar;
        // TODO remove symbol hack
        bar.symbol = "AAPL";
        std::getline(ss, field, ',');
        bar.date = field;
        std::getline(ss, field, ',');
        bar.open = std::stod(field);
        std::getline(ss, field, ',');
        bar.high = std::stod(field);
        std::getline(ss, field, ',');
        bar.low = std::stod(field);
        std::getline(ss, field, ',');
        bar.close = std::stod(field);
        std::getline(ss, field, ',');
        bar.adj_close = std::stod(field);
        std::getline(ss, field, ',');
        bar.volume = std::stoull(field);
        data.emplace_back(bar);
    }
}