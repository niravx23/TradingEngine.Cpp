#include <cassert>
#include <iostream>

#include "../include/orderBook.h"
#include "../include/PnlEngine.h"
#include "../include/order.h"

int main() {
    OrderBook ob;
    PnlEngine pnl;

    Order order1(1, Side::BUY, 100, 10);
    Order order2(2, Side::SELL, 40, 10);

    // TEST 1: Simple match
    ob.NEW(order1, pnl);
    ob.NEW(order2, pnl);

    
    assert(pnl.getRealizedPnL() == -600);

    std::cout << "Test 1 passed\n";
  
}