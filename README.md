# Elevator Simulation

A multithreaded C++ program that simulates the operation of elevators moving concurrently. This project demonstrates core concepts of **concurrency**, **thread synchronization**, and **real-time system behavior** using modern C++.

---

## 🧠 Project Overview

The Elevator Simulation models how elevators respond to floor requests while running in parallel. Each elevator operates on its own thread, and shared resources are protected using mutexes to prevent race conditions.

This project was built to showcase:
- Multithreading fundamentals
- Thread-safe programming
- Real-time state updates in a console-based system

---

## ✨ Features

- 🚀 Concurrent elevator movement using `std::thread`
- 🔒 Thread-safe synchronization with `std::mutex`
- 🧭 Request handling and dispatching logic
- 📟 Real-time console output showing elevator states
- ⚙️ Configurable simulation parameters
