#include <iostream>
#include <map>
#include <list>
#include <unordered_map>
#include "../include/orderBook.h"

OrderBook::OrderBook() {}
OrderBook::~OrderBook() {}

void OrderBook::Trade(Side currentSide, Order &incomingOrder, PnlEngine &pnlEngine)
{ 
    if (currentSide == Side::BUY)
    {
        while (!OrderBook::sellBook.empty() && incomingOrder.getQuantity() > 0)
        {
            auto bestSellLevel = sellBook.begin();
            double bestSellPrice = bestSellLevel->first;

            if (incomingOrder.getPrice() < bestSellPrice)
                break;

            auto &sellList = bestSellLevel->second;
            Order &sellOrder = sellList.front();

            int tradeQty = std::min(incomingOrder.getQuantity(), sellOrder.getQuantity());

            

            // Update quantities
            incomingOrder.setQuantity(incomingOrder.getQuantity() - tradeQty);
            sellOrder.setQuantity(sellOrder.getQuantity() - tradeQty);

            // PnL call
            pnlEngine.FILL(Side::BUY, bestSellPrice, tradeQty);

       
            // Remove sell order if fully filled
            if (sellOrder.getQuantity() == 0)
            {
                
                auto id = sellOrder.getId();
                sellList.pop_front();
                orderIndex.erase(id);
            }
        }

        if (incomingOrder.getQuantity() > 0)
        {
            // Add remaining buy order to book
            buyBook[incomingOrder.getPrice()].push_back(incomingOrder);
            orderIndex[incomingOrder.getId()] = --buyBook[incomingOrder.getPrice()].end();
        
        }
    }
    else
    {

        while (!buyBook.empty() && incomingOrder.getQuantity() > 0)
        {
            auto bestBuyLevel = buyBook.begin();
            double bestBuyPrice = bestBuyLevel->first;

            if (incomingOrder.getPrice() > bestBuyPrice)
                break;

            auto &buyList = bestBuyLevel->second;
            Order &buyOrder = buyList.front();

            int tradeQty = std::min(incomingOrder.getQuantity(), buyOrder.getQuantity());
            // Update quantities
            incomingOrder.setQuantity(incomingOrder.getQuantity() - tradeQty);
            buyOrder.setQuantity(buyOrder.getQuantity() - tradeQty);

            // PnL call
           
            pnlEngine.FILL(Side::SELL, bestBuyPrice, tradeQty);

            // Remove buy order if fully filled
            if (buyOrder.getQuantity() == 0)
            { 
                auto id = buyOrder.getId();
                buyList.pop_front();
                orderIndex.erase(id);   
            }
        }

        if (incomingOrder.getQuantity() > 0)
        {
            // Add remaining sell order to book
            sellBook[incomingOrder.getPrice()].push_back(incomingOrder);
            orderIndex[incomingOrder.getId()] = --sellBook[incomingOrder.getPrice()].end();
        }
    }
}

void OrderBook::MODIFY(int orderId, int newPrice, int newQuantity, PnlEngine &pnlEngine)
{
    auto it = orderIndex.find(orderId);

    if (it == orderIndex.end())
    {
        std::cout << "Order ID not found\n";
        return;
    }

    Side side = it->second->getSide();

    auto listIt = it->second;

    // Remove from current book
    if (side == Side::BUY)
    {
        buyBook[listIt->getPrice()].erase(listIt); // remove order from buy list

        if (buyBook[listIt->getPrice()].empty())
        { // check if no element in list -> delete price
            buyBook.erase(listIt->getPrice());
        }
    }
    else
    {
        sellBook[listIt->getPrice()].erase(listIt); // remove order from sell list

        if (sellBook[listIt->getPrice()].empty())
        { // check if no element in list -> delete price
            sellBook.erase(listIt->getPrice());
        }
    }

    // Add modified order
    Order newOrder(orderId, side, newPrice, newQuantity);

    NEW(newOrder, pnlEngine);
}

void OrderBook::NEW(Order &order, PnlEngine &pnl)
{
    int orderId = order.getId();
    Side side = order.getSide();
    int price = order.getPrice();

    this->Trade(side, order, pnl);

    if (order.getQuantity() == 0) // trade fully filled, no need to add to book
        return;

   
}

void OrderBook::CANCEL(int orderId)
{
    auto it = orderIndex.find(orderId);

    if (it == orderIndex.end())
    {
        std::cout << "Order ID not found\n";
        return;
    }

    Side side = it->second->getSide();

    auto listIt = it->second;

    // Remove from current book
    if (side == Side::BUY)
    {
        buyBook[listIt->getPrice()].erase(listIt); // remove order from buy list

        if (buyBook[listIt->getPrice()].empty())
        { // check if no element in list -> delete price
            buyBook.erase(listIt->getPrice());
        }
    }
    else
    {
        sellBook[listIt->getPrice()].erase(listIt); // remove

         if (sellBook[listIt->getPrice()].empty())
        { // check if no element in list -> delete price
            sellBook.erase(listIt->getPrice());
        }
    }

    orderIndex.erase(it);
}

void OrderBook::PRINT()
{
    std::cout << "SELL:\n";
    for (auto &[price, orders] : sellBook)
    {
        for (auto &o : orders)
            std::cout << o.getId() << " " << price << " " << o.getQuantity() << "\n";
    }

    std::cout << "BUY:\n";
    for (auto &[price, orders] : buyBook)
    {
        for (auto &o : orders)
            std::cout << o.getId() << " " << price << " " << o.getQuantity() << "\n";
    }
}