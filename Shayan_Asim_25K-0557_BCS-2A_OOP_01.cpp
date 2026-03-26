#include <iostream>
#include <string>
using namespace std;

class Seller;
class Marketplace;

class Vehicle {
private:
    string brand;
    string model;
    int year;
    double mileage;
    double engineCapacity;
    const string country;

public:
    Vehicle() : country("Japan") {
        brand = "Unknown"; model = "Unknown";
        year = 0; mileage = 0; engineCapacity = 0;
    }

    Vehicle(string b, string m, int y, double mil, double eng, string cntry) : country(cntry) {
        brand = b; model = m; year = y; mileage = mil; engineCapacity = eng;
    }

    Vehicle(const Vehicle& v) : country(v.country) {
        brand = v.brand; model = v.model; year = v.year;
        mileage = v.mileage; engineCapacity = v.engineCapacity;
    }

    void displaySpecs() const {
        cout << brand << " " << model << " " << year << " "
             << mileage << "km " << engineCapacity << "cc " << country << endl;
    }

    void updateMileage(double m) { mileage = m; }

    bool filterBrand(string b)   const { return brand == b; }
    bool filterModel(string m)   const { return model == m; }
    bool filterYear(int y)       const { return year == y; }
    bool filterMileage(double m) const { return mileage <= m; }

    string getBrand()   const { return brand; }
    string getModel()   const { return model; }
    int    getYear()    const { return year; }
    double getMileage() const { return mileage; }
    double getEngine()  const { return engineCapacity; }
};

class User {
protected:
    int id;
    string name;
    string email;
    string phone;
    string password;
    static int totalUsers;

public:
    User() {
        id = ++totalUsers;
        name = "Unknown"; email = "Unknown"; phone = "0000"; password = "1234";
    }

    User(string n, string e, string ph, string pass) {
        id = ++totalUsers; name = n; email = e; phone = ph; password = pass;
    }

    User(const User& u) {
        id = u.id; name = u.name; email = u.email;
        phone = u.phone; password = u.password;
    }

    void displayProfile() const {
        cout << id << " " << name << " " << email << endl;
    }

    void login() {
        cout << name << " logged in" << endl;
    }

    void logout() {
        cout << name << " logged out" << endl;
    }

    void updateName(string n) { name = n; }

    static int getTotalUsers() { return totalUsers; }

    int    getID()   const { return id; }
    string getName() const { return name; }
};

int User::totalUsers = 0;

class Product {
private:
    int    productID;
    string name;
    string category;
    double price;
    int    stock;
    static int totalProducts;

public:
    Product() {
        productID = ++totalProducts;
        name = "Unknown"; category = "General"; price = 0; stock = 0;
    }

    Product(string n, string cat, double p, int s) {
        productID = ++totalProducts;
        name = n; category = cat; price = p; stock = s;
    }

    Product(const Product& pr) {
        productID = pr.productID; name = pr.name;
        category = pr.category; price = pr.price; stock = pr.stock;
    }

    void display() const {
        cout << "Product #" << productID << " [" << category << "] "
             << name << " | Rs." << price << " | Stock: " << stock << endl;
    }

    void restock(int qty)      { stock += qty; }
    void updatePrice(double p) { price = p; }
    bool isAvailable()   const { return stock > 0; }

    static int getTotalProducts() { return totalProducts; }

    string getName()     const { return name; }
    double getPrice()    const { return price; }
    string getCategory() const { return category; }
};

int Product::totalProducts = 0;

class Listing {
private:
    int     listingID;
    Vehicle vehicle;
    double  price;
    string  status;
    Seller* seller;
    static int totalListings;

public:
    Listing() : vehicle() {
        listingID = ++totalListings; price = 0; status = "Pending"; seller = NULL;
    }

    Listing(Vehicle v, double p, Seller* s) : vehicle(v) {
        listingID = ++totalListings; price = p; status = "Pending"; seller = s;
    }

    Listing(const Listing& l) : vehicle(l.vehicle) {
        listingID = l.listingID; price = l.price; status = l.status; seller = l.seller;
    }

    void displayListing() const {
        cout << "ID: " << listingID << " Price: " << price << " Status: " << status << endl;
        vehicle.displaySpecs();
    }

    void updatePrice(double p)  { price = p; }
    void changeStatus(string s) { status = s; }

    bool filterPrice(double min, double max) const { return price >= min && price <= max; }
    bool filterBrand(string b)   const { return vehicle.filterBrand(b); }
    bool filterModel(string m)   const { return vehicle.filterModel(m); }
    bool filterYear(int y)       const { return vehicle.filterYear(y); }
    bool filterMileage(double m) const { return vehicle.filterMileage(m); }

    int    getID()     const { return listingID; }
    string getStatus() const { return status; }
    double getPrice()  const { return price; }

    static int getTotalListings() { return totalListings; }
};

int Listing::totalListings = 0;

class Favorite {
private:
    int      favID;
    Listing* listing;
    string   dateSaved;
    bool     active;
    string   note;
    static int totalFav;

public:
    Favorite() {
        favID = ++totalFav; listing = NULL;
        dateSaved = "None"; active = false; note = "";
    }

    Favorite(Listing* l, string d, string n = "") {
        favID = ++totalFav; listing = l;
        dateSaved = d; active = true; note = n;
    }

    Favorite(const Favorite& f) {
        favID = f.favID; listing = f.listing;
        dateSaved = f.dateSaved; active = f.active; note = f.note;
    }

    void displayFavorite() const {
        if (active && listing) {
            listing->displayListing();
            if (!note.empty()) {
                cout << "  Note: " << note << endl;
            }
        }
    }

    void deactivate()         { active = false; }
    bool isSame(Listing* l)   { return listing == l; }
    void updateDate(string d) { dateSaved = d; }
    void setNote(string n)    { note = n; }

    bool   isActive() const { return active; }
    string getDate()  const { return dateSaved; }
};

int Favorite::totalFav = 0;

class Seller : public User {
private:
    Listing* listings[10];
    int      listingCount;
    double   rating;
    int      totalSales;
    string   location;

public:
    Seller(string n, string e, string ph, string pass, string loc) : User(n, e, ph, pass) {
        listingCount = 0; rating = 0; totalSales = 0; location = loc;
    }

    void createListing(Listing* l) {
        if (listingCount < 10) listings[listingCount++] = l;
    }

    void updateListing(int id, double price) {
        for (int i = 0; i < listingCount; i++)
            if (listings[i]->getID() == id)
                listings[i]->updatePrice(price);
    }

    void deleteListing(int id) {
        for (int i = 0; i < listingCount; i++)
            if (listings[i]->getID() == id)
                listings[i]->changeStatus("Deleted");
    }

    void viewMyListings() const {
        for (int i = 0; i < listingCount; i++)
            listings[i]->displayListing();
    }

    string getLocation() const { return location; }
    double getRating()   const { return rating; }
};

class Buyer : public User {
private:
    Favorite favorites[10];
    int      favCount;
    string   preferredBrand;
    double   budget;
    string   location;

public:
    Buyer(string n, string e, string ph, string pass, string loc) : User(n, e, ph, pass) {
        favCount = 0; preferredBrand = "Any"; budget = 0; location = loc;
    }

    void saveFavorite(Listing* l, string note = "") {
        if (favCount < 10)
            favorites[favCount++] = Favorite(l, "Today", note);
    }

    void removeFavorite(int index) {
        if (index < favCount) favorites[index].deactivate();
    }

    void viewFavorites() const {
        for (int i = 0; i < favCount; i++)
            favorites[i].displayFavorite();
    }

    void sendMessage(User* s, string text) {
        cout << "Message from " << name << " to " << s->getName() << ": " << text << endl;
    }

    void setBudget(double b)          { budget = b; }
    void setPreferredBrand(string b)  { preferredBrand = b; }
    double getBudget()          const { return budget; }
};

class Admin : public User {
private:
    const string role;
    int    level;
    bool   superAccess;
    string department;
    int    handled;

public:
    Admin(string n, string e, string ph, string pass) : User(n, e, ph, pass), role("Admin") {
        level = 1; superAccess = true; department = "Management"; handled = 0;
    }

    void approveListing(Listing* l) { l->changeStatus("Approved"); handled++; }
    void removeListing(Listing* l)  { l->changeStatus("Removed"); }

    void viewStats() const {
        cout << "Total Users: "    << User::getTotalUsers()       << endl;
        cout << "Total Listings: " << Listing::getTotalListings() << endl;
        cout << "Total Products: " << Product::getTotalProducts() << endl;
    }

    void displayRole() const {
        cout << role << endl;
    }

    int getHandled() const { return handled; }
};

class Message {
private:
    int         messageID;
    User* const sender;
    User*       receiver;
    string      text;
    string      timeStamp;
    static int  totalMsg;

public:
    Message(User* s, User* r, string t, string time) : sender(s) {
        messageID = ++totalMsg; receiver = r; text = t; timeStamp = time;
    }

    Message(const Message& m) : sender(m.sender) {
        messageID = m.messageID; receiver = m.receiver;
        text = m.text; timeStamp = m.timeStamp;
    }

    void display() const {
        cout << "[" << timeStamp << "] " << text << endl;
    }

    void edit(string t) { text = t; }
    void erase()        { text = ""; }

    void resend() {
        cout << "Resent: " << text << endl;
    }

    static int getTotalMessages() { return totalMsg; }

    string getText() const { return text; }
};

int Message::totalMsg = 0;

class Marketplace {
private:
    User*     users[50];
    Listing*  listings[100];
    Product   featuredProducts[20];
    int       userCount;
    int       listingCount;
    int       productCount;
    const int MAX_LISTINGS;

public:
    Marketplace() : MAX_LISTINGS(100) {
        userCount = 0; listingCount = 0; productCount = 0;
    }

    void registerUser(User* u) {
        if (userCount < 50) users[userCount++] = u;
    }

    void addListing(Listing* l) {
        if (listingCount < MAX_LISTINGS) listings[listingCount++] = l;
    }

    void addProduct(Product p) {
        if (productCount < 20) featuredProducts[productCount++] = p;
    }

    void removeListing(int id) {
        for (int i = 0; i < listingCount; i++)
            if (listings[i]->getID() == id)
                listings[i]->changeStatus("Removed");
    }

    void filter(string brand, string model, int year, double mileage, double minP, double maxP) {
        bool found = false;
        for (int i = 0; i < listingCount; i++)
            if (listings[i]->filterBrand(brand)      &&
                listings[i]->filterModel(model)      &&
                listings[i]->filterYear(year)        &&
                listings[i]->filterMileage(mileage)  &&
                listings[i]->filterPrice(minP, maxP) &&
                listings[i]->getStatus() == "Approved") {
                listings[i]->displayListing();
                found = true;
            }
        if (!found) {
            cout << "No matching listings found." << endl;
        }
    }

    void showAll() const {
        for (int i = 0; i < listingCount; i++)
            listings[i]->displayListing();
    }

    void showProducts() const {
        for (int i = 0; i < productCount; i++)
            featuredProducts[i].display();
    }
};

int main() {

    Marketplace market;

    Seller s("Ali",   "ali@mail.com",   "0300", "1234", "Karachi");
    Buyer  b("Ahmed", "ahmed@mail.com", "0311", "5678", "Lahore");
    Admin  a("Admin", "admin@mail.com", "0000", "admin");

    market.registerUser(&s);
    market.registerUser(&b);
    market.registerUser(&a);

    Vehicle v("Toyota", "Corolla", 2020, 30000, 1800, "Japan");
    Listing l(v, 4500000, &s);

    s.createListing(&l);
    market.addListing(&l);
    s.updateListing(l.getID(), 4300000);
    a.approveListing(&l);
    s.viewMyListings();

    cout << "Search Results" << endl;
    market.filter("Toyota", "Corolla", 2020, 40000, 4000000, 5000000);

    b.saveFavorite(&l, "Great mileage!");
    cout << "Favourites" << endl;
    b.viewFavorites();

    Message msg(&b, &s, "Is it still available?", "2024-01-01 10:00");
    msg.display();

    Product p1("PakWheels Car Polish", "Car Care", 2500, 50);
    Product p2("3D Seat Covers",       "Decor",    4800, 20);
    market.addProduct(p1);
    market.addProduct(p2);
    cout << "Featured Products" << endl;
    market.showProducts();

    cout << "Admin Stats" << endl;
    a.viewStats();

    return 0;
}