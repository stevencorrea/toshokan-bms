// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Book-class Source Code

#include <cstdint>
#include <iostream>
#include <string_view>

#include <toshokan-bms/Item.hpp>

Item::Item(Book* b, uint32_t qty, double price) : m_book(b), m_qty(qty), m_price(price) {
}

Item::Item(const Item& i) : m_book(i.m_book), m_qty(i.m_qty), m_price(i.m_price) {
}

Item::~Item() {
    delete m_book;
}

void Item::display() const {
    std::cout << *m_book << '\n';
}

void Item::updatePrice(double newPrice) {
    m_price = newPrice;
}

void Item::updateQty(uint32_t newQty) {
    m_qty = newQty;
}

void Item::modifyQty(int32_t val) {
    int32_t temp = m_qty + val;

    if (temp < 0) {
        temp = 0;
    }

    m_qty = temp;
}

bool Item::checkInStock(uint32_t val = 1) const {
    return m_qty >= val;
}

bool Item::checkAll(std::string_view s) const {
    return false;
}

bool Item::checkISBN(const uint64_t s) const {
    return m_book->checkISBN(s);
}

bool Item::checkTitle(std::string_view s) const {
    return m_book->checkTitle(s);
}

bool Item::checkAuthor(std::string_view s) const {
    return m_book->checkAuthor(s);
}

bool Item::checkPublisher(std::string_view s) const {
    return m_book->checkPublisher(s);
}

bool Item::checkYear(uint32_t s) const {
    return m_book->checkYear(s);
}

bool Item::checkOther(std::string_view s) const {
    return m_book->checkOther(s);
}
