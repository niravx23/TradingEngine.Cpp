#pragma once
#include "order.h"
#include "PnlEngine.h"
#include <list>
#include <map>
#include <unordered_map>

class OrderBook
{
private:
    std::unordered_map<int, std::list<Order>::iterator> orderIndex;
    std::map<double, std::list<Order>, std::greater<double>> buyBook;
    std::map<double, std::list<Order>> sellBook;

public:
    OrderBook();
    void Trade(Side currentSide, Order &incomingOrder, PnlEngine &pnlEngine);
    void MODIFY(int orderId, int newPrice, int newQuantity, PnlEngine &pnlEngine);
    void NEW(Order &order, PnlEngine &pnl);
    void CANCEL(int orderId);
    void PRINT();
    ~OrderBook();
};