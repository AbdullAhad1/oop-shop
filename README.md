<div align="center">

# BDStore-1971

**Terminal-Based C++ Shopping System**

<p>
  <img src="https://img.shields.io/badge/C++-98-blue?style=flat-square&logo=cplusplus" alt="C++98">
  <img src="https://img.shields.io/badge/Make-GNU-green?style=flat-square&logo=gnu" alt="Make">
  <img src="https://img.shields.io/badge/Status-Complete-success?style=flat-square" alt="Status">
</p>

<p>
  <a href="https://github.com/AbdullAhad1/oop-shop/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/AbdullAhad1/oop-shop?style=flat-square&color=orange" alt="Contributors">
  </a>
</p>

</div>

---

## UML Architecture

![BDStore-1971 UML Class Diagram](docs/uml-class-diagram.png?v=2)

*Full interactive version: [`docs/uml-handwritten.html`](docs/uml-handwritten.html) · Spec: [`docs/uml-diagram.md`](docs/uml-diagram.md)*

---

## Overview

BDStore-1971 is a terminal-based inventory and shopping application built in **C++98** as an Object-Oriented Programming group project. It demonstrates six core OOP principles through a functional CLI with ANSI-styled output, file persistence, and role-based access control.

**Key highlights:**
- Inheritance + Polymorphism for User roles (`Customer` / `Admin`)
- Encapsulation with controlled getters/setters
- Composition for Cart and Inventory management
- Custom exception handling extending `std::exception`
- File-based data persistence (`data/*.txt`)
- Terminal UI with colors, banners, and box drawing

---

## Team

| Member | GitHub | Module Ownership |
|--------|--------|------------------|
| **Ahad Abdul** | [@AbdullAhad1](https://github.com/AbdullAhad1) | UI Namespace, Main Orchestration, Integration |
| **Sayfaz Islam** | [@sayfazislam-hash](https://github.com/sayfazislam-hash) | User System, Authentication, Role Split |
| **Araf Chowdhury** | [@araf582004-blip](https://github.com/araf582004-blip) | Product, Inventory, Cart, Order Core |

---

## OOP Concepts Applied

| Principle | Where |
|-----------|-------|
| **Inheritance** | `Customer` and `Admin` inherit from abstract `User` |
| **Polymorphism** | `User*` base pointer dispatches `displayMenu()` and `getRole()` at runtime |
| **Encapsulation** | Private fields + public getters/setters in `Product`, `Cart`, `Inventory`, `Order` |
| **Abstraction** | `User` is abstract with pure virtual functions |
| **Composition** | `Cart` contains `CartItem`s; `Order` contains `CartItem`s; `Inventory` manages `Product`s |
| **Exception Handling** | `ShopException` extends `std::exception` for domain-specific errors |
| **File I/O** | Load/save products, users, and orders to `.txt` files |

---

## Features

| Portal | Actions |
|--------|---------|
| **Customer** | Browse catalog, add/remove cart items, checkout, view order history |
| **Admin** | Add / update / delete products, view all customer orders |

- ANSI-colored terminal UI with banners, separators, and product cards
- Persistent storage via flat text files (`data/`)
- Runtime role validation (no cross-portal login)

---

## Download & Run

### macOS

1. Open Terminal
2. Clone the repo and build

```bash
git clone https://github.com/AbdullAhad1/oop-shop.git
cd oop-shop
make
./build/shop
```

> **Note:** macOS Command Line Tools (`xcode-select --install`) provides `make` and `g++`.

---

### Windows

#### Option A — MSYS2 (recommended)

1. Install [MSYS2](https://www.msys2.org/)
2. Open the **UCRT64** terminal
3. Install GCC and Make

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
```

4. Clone, build, and run

```bash
git clone https://github.com/AbdullAhad1/oop-shop.git
cd oop-shop
make
./build/shop.exe
```

#### Option B — WSL (Windows Subsystem for Linux)

1. Open a WSL terminal (Ubuntu)
2. Clone and build exactly like macOS

```bash
git clone https://github.com/AbdullAhad1/oop-shop.git
cd oop-shop
make
./build/shop
```

#### Option C — Code::Blocks / Dev-C++

1. Create a new **Console Application** project
2. Add all `.cpp` files from `src/` and headers from `include/`
3. Build and run inside the IDE

---

**Default Credentials**

| Role | Username | Password |
|------|----------|----------|
| Admin | `admin` | `admin` |

Register new Customer or Admin accounts from the main portal menu.

---

## Project Structure

```
.
├── include/          # Header files (.hpp)
│   ├── User.hpp
│   ├── Customer.hpp
│   ├── Admin.hpp
│   ├── Product.hpp
│   ├── Cart.hpp
│   ├── Order.hpp
│   ├── Inventory.hpp
│   ├── ShopException.hpp
│   └── UI.hpp
├── src/               # Implementation files (.cpp)
│   ├── main.cpp
│   ├── User.cpp
│   ├── Customer.cpp
│   ├── Admin.cpp
│   ├── Product.cpp
│   ├── Cart.cpp
│   ├── Order.cpp
│   ├── Inventory.cpp
│   ├── ShopException.cpp
│   └── UI.cpp
├── data/              # Data persistence files
├── docs/              # UML diagrams and documentation
│   ├── uml-diagram.md     # Full class spec
│   ├── uml-diagram.png    # PNG render of the diagram
│   └── uml-handwritten.html  # Interactive handwritten UML
├── Makefile
└── README.md
```

---

## Class Summary

| Class | Stereotype | Role |
|-------|------------|------|
| `User` | Abstract | Base class for runtime polymorphism |
| `Customer` | Concrete | Customer portal user |
| `Admin` | Concrete | Admin portal user |
| `Product` | Entity | Sellable item with file I/O |
| `Inventory` | Controller | Product collection manager |
| `CartItem` | Struct | Lightweight item in cart/order |
| `Cart` | Controller | Customer shopping cart logic |
| `Order` | Entity | Finalized purchase record |
| `ShopException` | Exception | Custom error type |
| `UI` | Namespace | Terminal styling and input helpers |

---

## Contributors

<a href="https://github.com/AbdullAhad1/oop-shop/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=AbdullAhad1/oop-shop" alt="Contributors" />
</a>

---

<p align="center">
  <sub>Built for C++ OOP coursework at Dong-Eui University.</sub>
</p>
