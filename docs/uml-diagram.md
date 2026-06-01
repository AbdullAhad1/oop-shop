# UML Class Diagram

```
+------------------+       +------------------+       +------------------+
|     <<abstract>> |       |    Customer      |       |     Admin        |
|       User       |<------|      (role=cust) |<------|      (role=admin)|
+------------------+       +------------------+       +------------------+
| - username       |       |                    |       |                    |
| - password       |       | + displayMenu()  |       | + displayMenu()  |
+------------------+       | + getRole()      |       | + getRole()      |
| + getUsername()  |       +------------------+       +------------------+
| + checkPassword()|
| + displayMenu()* |                                   +------------------+
| + getRole()*     |                                   |   ShopException  |
+------------------+                                   +------------------+
         ^                                             | - message        |
         |                                             |                  |
         |                                             | + what()*        |
         |                                             +------------------+
         |
   +-----+-----+
   |           |
   |           |
+------------+  +------------+
|  Customer  |  |   Admin    |
+------------+  +------------+

+---------------------------------------------------+
|                    Product                          |
+---------------------------------------------------+
| - productId                                       |
| - name                                            |
| - description                                     |
| - price                                           |
| - stockQuantity                                   |
+---------------------------------------------------+
| + getId() / setId()                               |
| + getName() / setName()                           |
| + getDescription() / setDescription()             |
| + getPrice() / setPrice()                         |
| + getStock() / setStock()                         |
| + reduceStock(qty)                                |
| + toFileString() / fromFileString()                 |
+---------------------------------------------------+
                        ^
                        | uses (many)
          +----------------------------+
          |        Inventory             |
          +----------------------------+
          | - products[]                 |
          | - filename                   |
          +----------------------------+
          | + addProduct()               |
          | + updateProduct()            |
          | + deleteProduct()            |
          | + findProduct()              |
          | + displayAll()               |
          | + displayAvailable()         |
          | + loadFromFile()             |
          | + saveToFile()               |
          +----------------------------+
                        ^
                        | uses
          +----------------------------+
          |          Cart                |
          +----------------------------+
          | - items[] (CartItem)         |
          +----------------------------+
          | + addItem()                  |
          | + removeItem()               |
          | + updateQuantity()           |
          | + viewCart()                 |
          | + getTotal()                 |
          | + clear()                    |
          +----------------------------+
                        ^
                        | uses
          +----------------------------+
          |          Order               |
          +----------------------------+
          | - orderId                    |
          | - customerUsername           |
          | - orderDate                  |
          | - totalAmount                |
          | - status                     |
          | - items[] (CartItem)         |
          +----------------------------+
          | + toFileString()             |
          | + fromFileString()           |
          +----------------------------+
```

## Relationships

- **Inheritance**: `Customer` → `User`, `Admin` → `User`, `ShopException` → `std::exception`
- **Composition**: `Inventory` has many `Products`, `Cart` has many `CartItem`s, `Order` has many items
- **Dependency**: `Cart` uses `Inventory` for lookups and stock validation
- **Association**: `main` holds `User*`, `Inventory`, `Cart`, and `Order` objects

## Runtime Polymorphism

The `User` abstract class declares pure virtual functions:
- `virtual void displayMenu() const = 0`
- `virtual string getRole() const = 0`

In `main.cpp`, a `User* currentUser` pointer is assigned either a `Customer` or `Admin` object at runtime. Calling `currentUser->displayMenu()` dispatches to the derived class's implementation — this is the required runtime polymorphism.
