#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "../include/CommandProcessor.h"

Side CommandProcessor::parseSide(const std::string &s)
{
    if (s == "BUY")
        return Side::BUY;
    if (s == "SELL")
        return Side::SELL;
    throw std::invalid_argument("Invalid side");
}

void CommandProcessor::process(const std::string &line, OrderBook &ob, PnlEngine &pnl)
{
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "NEW")
    {
        int id, qty;
        double price;
        std::string sideStr;

        iss >> id >> sideStr >> price >> qty;

        Order order(id, parseSide(sideStr), price, qty);
        ob.NEW(order, pnl);
    }
    else if (cmd == "CANCEL")
    {
        int id;
        iss >> id;

        ob.CANCEL(id);
    }
    else if (cmd == "MODIFY")
    {
        int id, qty;
        double price;

        iss >> id >> price >> qty;

        ob.MODIFY(id, price, qty, pnl); // internally cancel + add
    }
    else if (cmd == "PRINT")
    {
        ob.PRINT();
    }
    else if (cmd == "PRICE")
    {
        double price;
        iss >> price;
        pnl.PRICE(price);
    }
    else if (cmd == "PRINT_PNL")
    {
        pnl.printPnl();
    }
    else
    {
        std::cout << "Unknown command\n";
    }
}
