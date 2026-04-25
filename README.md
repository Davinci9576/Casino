# 🎰 Casino Poker Engine (C++)

## 🚀 Overview

A modular Texas Hold'em poker engine implemented in C++, designed with scalability, maintainability, and clean architecture in mind.

This project goes beyond a simple console game—it demonstrates structured system design, multi-file organization, and advanced game logic implementation.

---

## 🧠 Core Features

* ♠️ Full Texas Hold'em game flow
* 🃏 7-card hand evaluation system
* 🧮 Ranking logic (pairs, straights, flushes, full house, etc.)
* 🎲 Randomized deck generation and shuffling
* 👥 Multi-player support
* 💰 Pot and betting system (in progress)
* 💾 File handling integration planned (persistent game state)

---

## 🧱 Architecture (Multi-file Design)

This project is structured using a modular, multi-file approach:

* `main.cpp` → Entry point and game loop
* `deck.cpp / deck.h` → Deck creation and shuffling
* `player.cpp / player.h` → Player logic and state
* `hand_evaluator.cpp / hand_evaluator.h` → Core ranking algorithm
* `utils.cpp / utils.h` → Helper functions

This separation ensures:

* scalability
* readability
* easier debugging and extension

---

## ⚙️ Technologies & Concepts

* C++ (STL: vector, map, algorithm)
* Object-oriented design
* Dynamic memory management
* File I/O (`fstream`) *(planned integration)*
* Algorithmic problem solving

---

## ▶️ How to Run

### Compile

```bash
g++ *.cpp -o poker
```
### Execute

```bash
./poker

## 📈 Future Improvements

* 🌐 Online leaderboard using Web API
* 🤖 AI-based opponent logic
* 🎨 GUI version (Qt / SDL)
* 🔐 Persistent player data (bankroll system)
* 🧪 Unit testing for hand evaluation

---

## 💼 Why This Project Matters

This project demonstrates:

* ability to design non-trivial systems
* understanding of game logic and edge cases
* clean code organization across multiple files
* readiness for real-world C++ development environments

---

## 📌 Author

Developed by a motivated engineering student focused on building scalable systems and mastering low-level programming.

---
