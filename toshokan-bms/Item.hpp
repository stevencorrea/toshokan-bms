// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Item-class Header

#ifndef TOSHOKAN_BMS_ITEM_HPP_
#define TOSHOKAN_BMS_ITEM_HPP_

#include <cstdint>
#include <string_view>

#include <toshokan-bms/Book.hpp>

class Item {
 private:
    Book* m_book;
    uint32_t m_qty;
    double m_price;

 public:
    Item(Book*, uint32_t, double);
    Item(const Item&);
    ~Item();
    void display() const;
    void updatePrice(double);
    void updateQty(uint32_t);
    void modifyQty(int32_t);
    bool checkInStock(uint32_t) const;
    bool checkAll(std::string_view) const;
    bool checkISBN(const uint64_t) const;
    bool checkTitle(std::string_view) const;
    bool checkAuthor(std::string_view) const;
    bool checkPublisher(std::string_view) const;
    bool checkYear(uint32_t) const;
    bool checkOther(std::string_view) const;
};

#endif  // TOSHOKAN_BMS_ITEM_HPP_
