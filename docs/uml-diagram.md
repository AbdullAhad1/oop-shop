<div align="center">

<h1>BDStore-1971 — UML Class Diagram</h1>
<p>Object-Oriented Design Overview</p>

</div>

---

## Class Diagram

```mermaid
classDiagram
    direction TB

    %% ======== INHERITANCE HIERARCHY ========
    class User {
        &lt;&lt;abstract&gt;&gt;
        # username : string
        # password : string
        + User(string u, string p)
        + ~User()
        + getUsername() string
        + checkPassword(string p) bool
        + displayMenu() void
        + getRole() string
    }

    class Customer {
        + Customer(string u, string p)
        + displayMenu() void
        + getRole() string
    }

    class Admin {
        + Admin(string u, string p)
        + displayMenu() void
        + getRole() string
    }

    User <|-- Customer : inherits
    User <|-- Admin : inherits

    %% ======== PRODUCT & INVENTORY ========
    class Product {
        - productId : int
        - name : string
        - description : string
        - price : double
        - stockQuantity : int
        + Product()
        + Product(int id, string n, string d, double p, int qty)
        + getId() int
        + getName() string
        + getDescription() string
        + getPrice() double
        + getStock() int
        + setName(string n) void
        + setDescription(string d) void
        + setPrice(double p) void
        + setStock(int qty) void
        + reduceStock(int qty) void
        + toFileString() string
        + fromFileString(string line) Product$
    }

    class Inventory {
        - products : vector~Product~
        - filename : string
        - nextProductId : int
        + Inventory(string fname)
        + loadFromFile() void
        + saveToFile() void
        + addProduct(Product p) void
        + updateProduct(int id, Product p) void
        + deleteProduct(int id) void
        + findProduct(int id) Product*
        + displayAll() void
        + displayAvailable() void
        + getProducts() vector~Product~
        + getNextId() int
    }

    Inventory "1" o-- "0..*" Product : manages

    %% ======== CART ========
    class CartItem {
        + productId : int
        + quantity : int
    }

    class Cart {
        - items : vector~CartItem~
        + addItem(int pid, int qty, Inventory& inv) void
        + removeItem(int pid) void
        + updateQuantity(int pid, int qty, Inventory& inv) void
        + clear() void
        + viewCart(Inventory& inv) void
        + getTotal(Inventory& inv) double
        + getItems() vector~CartItem~
        + isEmpty() bool
    }

    Cart "1" *-- "0..*" CartItem : contains

    %% ======== ORDER ========
    class Order {
        - orderId : int
        - customerUsername : string
        - orderDate : string
        - totalAmount : double
        - status : string
        - items : vector~CartItem~
        + Order()
        + Order(int oid, string user, string date, double total, string stat, vector~CartItem~ its)
        + getOrderId() int
        + getCustomer() string
        + getTotal() double
        + getDate() string
        + getStatus() string
        + getItems() vector~CartItem~
        + toFileString() string
        + fromFileString(string line) Order$
    }

    Order "1" *-- "0..*" CartItem : contains

    %% ======== EXCEPTION ========
    class std_exception {
        <<standard>>
    }

    class ShopException {
        - message : string
        + ShopException(string msg)
        + ~ShopException()
        + what() const char*
    }

    std_exception <|-- ShopException : extends

    %% ======== UI NAMESPACE ========
    class UI {
        <<namespace>>
        + clearScreen() void$
        + drawHeader(string title) void$
        + drawSubHeader(string text) void$
        + drawSeparator(char c) void$
        + drawMenuItem(int num, string label) void$
        + drawPortalMenu() void$
        + drawCustomerPortal() void$
        + drawSuccess(string text) void$
        + drawError(string text) void$
        + drawWarning(string text) void$
        + drawInfo(string text) void$
        + drawBanner(string text) void$
        + drawTableHeader(...) void$
        + drawTableRow(...) void$
        + drawProductCard(...) void$
        + drawLogo() void$
        + drawSmallLogo() void$
        + inputString(string prompt) string$
        + inputInt(string prompt) int$
        + inputDouble(string prompt) double$
    }

    %% ======== USAGE RELATIONSHIPS ========
    Customer ..> Cart : uses
    Customer ..> Inventory : browses
    Customer ..> Order : places
    Admin ..> Inventory : manages
    Admin ..> Order : views
    Cart ..> Inventory : queries
```

---

## Relationship Summary

| Type | From | To | Meaning |
|------|------|-----|---------|
| Inheritance | `Customer` | `User` | Customer is a User |
| Inheritance | `Admin` | `User` | Admin is a User |
| Inheritance | `ShopException` | `std::exception` | Custom domain exception |
| Composition | `Cart` | `CartItem` | Cart owns its items |
| Composition | `Order` | `CartItem` | Order owns its items |
| Aggregation | `Inventory` | `Product` | Inventory manages Products |
| Dependency | `Customer` | `Cart`, `Inventory`, `Order` | Customer uses these |
| Dependency | `Admin` | `Inventory`, `Order` | Admin uses these |
| Dependency | `Cart` | `Inventory` | Cart queries stock |

---

## Design Notes

- **Runtime Polymorphism** is demonstrated via the `User*` pointer in `main.cpp`: it holds either a `Customer` or `Admin` object, and calling `displayMenu()` or `getRole()` dispatches to the correct derived class at runtime.
- **Abstraction** is enforced by making `User` abstract (pure virtual methods), preventing direct instantiation.
- **Composition** is used for `Cart`→`CartItem` and `Order`→`CartItem`, meaning items are owned and destroyed with their container.
- **Aggregation** is used for `Inventory`→`Product`, as Products can exist independently (e.g., loaded from/saved to file).
- **Encapsulation** keeps all data members private; controlled access through public getters/setters.
