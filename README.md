# 📈 C++ In-Memory Trading Engine (Order Book + PnL System)

A lightweight **limit order book + position/PnL engine** implemented in C++17.  
Designed for learning **low-level trading system design, data structures, and execution logic**.

---

# 🚀 Features

## 📦 Order Book Engine
- BUY / SELL limit orders
- Price-time priority (FIFO per price level)
- Partial fills supported
- Fast order lookup using `unordered_map`

## 🔁 Supported Commands
- `NEW id side price qty`
- `CANCEL id`
- `MODIFY id newPrice newQty`
- `PRINT` (order book state)

---

## 💰 PnL Engine
Tracks trading performance:

- `netQty` → current position (long/short)
- `avgPrice` → weighted entry price
- `realizedPnL` → profit/loss from closed trades
- `unrealizedPnL` → mark-to-market PnL

### Additional Commands
- `PRICE x` → updates market price
- `PRINT_PNL` → displays PnL state

---

# 🧠 Core Design

## 🏗 Order Book Structure
```cpp
map<double, list<Order>> buyBook;
map<double, list<Order>> sellBook;
unordered_map<int, iterator> orderIndex;
