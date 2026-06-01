# Online Shop & Inventory System

A CLI-based C++ shopping system demonstrating OOP principles: inheritance, polymorphism, encapsulation, abstraction, composition, and exception handling.

## Features

- **Customer**: Browse products, add/remove items from cart, checkout.
- **Admin**: Add/update/delete products, view all orders.
- **Runtime Polymorphism**: `User*` base pointer calls `displayMenu()` and `getRole()` from `Customer` or `Admin`.
- **Custom Exception**: `ShopException` class for domain errors.
- **File I/O**: Products, users, and orders persist to text files.

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
│   └── ShopException.hpp
├── src/              # Implementation files (.cpp)
│   ├── User.cpp
│   ├── Customer.cpp
│   ├── Admin.cpp
│   ├── Product.cpp
│   ├── Cart.cpp
│   ├── Order.cpp
│   ├── Inventory.cpp
│   └── main.cpp
├── data/             # Data persistence files
├── docs/             # UML diagram
├── Makefile
└── README.md
```

## Build & Run

```bash
make        # Compile
./build/shop  # Run
make clean  # Remove compiled files
```

## Default Credentials

- **Admin**: username: `admin`, password: `admin`
- After login, register new customers/admins from the main menu.

## OOP Concepts Applied

| Concept | Usage |
|---|---|
| Inheritance | `Customer`, `Admin` inherit from `User` |
| Polymorphism | `User* currentUser` calls `displayMenu()` and `getRole()` at runtime. `findProduct` returns `Product*` which is used polymorphically. |
| Encapsulation | Private members with getter/setter methods in `Product`, `Inventory`, `Cart` |
| Abstraction | `User` is an abstract class with pure virtual functions |
| Composition | `Cart` contains `CartItem`s; `Inventory` contains `Product`s; `Order` tracks items |
| Custom Exception | `ShopException` class extending `std::exception` |
| File I/O | Products, users, and orders saved/reloaded from `.txt` files |

## UML Class Diagram

See `docs/uml-diagram.md` for the full diagram.
