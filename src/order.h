/*
 * File: order.h
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 5:25:23 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 5:25:23 pm
 * -----
 */

#ifndef _ORDER_H
#define _ORDER_H

#include <string>

enum class OrderAction
{
    ACTION_BUY,
    ACTION_SELL,
    ACTION_KEEP,
};

struct Order
{
    std::string symbol;
    std::string date;
    OrderAction action;
    int quantity;
    double price;
};
typedef struct Order Order_s;

#endif
