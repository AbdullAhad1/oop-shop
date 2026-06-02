<div align="center">

<h1>BDStore-1971</h1>
<p><b>CLI-Based C++ Shopping System</b></p>

<p>
  <img src="https://img.shields.io/badge/C++-98-blue?style=for-the-badge&logo=cplusplus" alt="C++98">
  <img src="https://img.shields.io/badge/Make-GNU-green?style=for-the-badge&logo=gnu" alt="Make">
  <img src="https://img.shields.io/badge/Status-Complete-success?style=for-the-badge" alt="Status">
</p>

<p>
  <a href="https://github.com/AbdullAhad1/oop-shop/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/AbdullAhad1/oop-shop?style=for-the-badge&color=orange" alt="Contributors">
  </a>
</p>

</div>

---

## Team

| Member | GitHub | Role |
|--------|--------|------|
| **Ahad Abdul** | [@AbdullAhad1](https://github.com/AbdullAhad1) | UI, Main Orchestration, Integration |
| **Sayfaz Islam** | [@sayfazislam-hash](https://github.com/sayfazislam-hash) | User System, Authentication, Customer/Admin Roles |
| **Araf Chowdhury** | [@araf582004-blip](https://github.com/araf582004-blip) | Product, Inventory, Cart, Order & Shop Core |

---

## Overview

BDStore-1971 is a terminal-based inventory and shopping application demonstrating six core Object-Oriented Programming principles:

- **Inheritance** — `Customer` and `Admin` extend abstract `User`
- **Polymorphism** — Runtime method dispatch via `User*` base pointers
- **Encapsulation** — Private fields with controlled getters/setters
- **Abstraction** — `User` as a pure-virtual interface class
- **Composition** — `Cart` contains `CartItem`s; `Inventory` manages `Product`s
- **Exception Handling** — Custom `ShopException` extending `std::exception`

---

## Features

| Portal | Actions |
|--------|---------|
| **Customer** | Browse products, add/remove cart items, checkout, view order history |
| **Admin** | Add/update/delete products, view all customer orders |

- Styled terminal UI with ANSI colors, box drawing, and banners
- File persistence for products, users, and orders (`data/*.txt`)
- Runtime role validation (customer login blocked from admin portal, and vice versa)

---

## Quick Start

```bash
# Compile
make

# Run
./build/shop

# Clean build files
make clean
```

**Default Credentials**

| Role | Username | Password |
|------|----------|----------|
| Admin | `admin` | `admin` |

Register new Customer/Admin accounts from the main portal menu.

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
├── src/              # Implementation files (.cpp)
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
├── data/             # Data persistence files
├── docs/             # UML diagram & contributor docs
├── Makefile
└── README.md
```

---

## OOP Concepts Applied

| Concept | Where |
|---------|-------|
| Inheritance | `Customer` & `Admin` inherit from `User` |
| Polymorphism | `User* currentUser` calls `displayMenu()` & `getRole()` at runtime |
| Encapsulation | Private members + getters/setters in `Product`, `Cart`, `Inventory` |
| Abstraction | `User` is abstract with pure virtual functions |
| Composition | `Cart` holds `CartItem`s; `Inventory` holds `Product`s; `Order` tracks items |
| Custom Exception | `ShopException` extends `std::exception` |
| File I/O | Load/save products, users, orders to `.txt` files |

---

## UML Class Diagram

See [`docs/uml-diagram.md`](docs/uml-diagram.md) for the full diagram.

---

## Contributors

<a href="https://github.com/AbdullAhad1/oop-shop/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=AbdullAhad1/oop-shop" alt="Contributors" />
</a>
