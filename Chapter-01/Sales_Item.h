#ifndef SALESITEM_H
#define SALESITEM_H

#include <iostream>
#include <string>

class Sales_Item {
    friend std::istream& operator>>(std::istream&, Sales_Item&);
    friend std::ostream& operator<<(std::ostream&, Sales_Item&);
    friend bool operator==(const Sales_Item&, const Sales_Item&);

    public:
        Sales_Item() = default; // required to initialize members of built-in type
        Sales_Item(const std::string &book): bookNo(book) { }
        Sales_Item(std::istream &is) { is >> *this; }

        Sales_Item& operator+=(const Sales_Item&);
        std::string isbn() const { return bookNo; }
        double avg_price() const;

    private:
        std::string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
};

inline bool compareIsbn(const Sales_Item &lhs, const Sales_Item &rhs) {
    return lhs.isbn() == rhs.isbn();
}

std::istream& operator>>(std::istream& in, Sales_Item& s) {
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    if (in)
        s.revenue = s.units_sold * price;
    else
        s = Sales_Item();
    
    return in;
}

std::ostream& operator<<(std::ostream& out, Sales_Item& s) {
    out << s.isbn() << " " << s.units_sold << " "
        << s.revenue << " " << s.avg_price();

    return out;
}

bool operator==(const Sales_Item &lhs, const Sales_Item &rhs) {
    return  lhs.isbn() == rhs.isbn() &&
            lhs.revenue == rhs.revenue &&
            lhs.units_sold == rhs.units_sold;
}

inline bool operator!=(const Sales_Item &lhs, const Sales_Item& rhs) {
    return !(lhs == rhs);
}

Sales_Item operator+(const Sales_Item &lhs, const Sales_Item &rhs) {
    Sales_Item ret(lhs);
    ret += rhs;

    return ret;
}

// assuming that both object have same ISBN
Sales_Item& Sales_Item::operator+=(const Sales_Item& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;

    return *this;
}

double Sales_Item::avg_price() const {
    if (units_sold)
        return revenue/units_sold;
    else
        return 0;
}
#endif