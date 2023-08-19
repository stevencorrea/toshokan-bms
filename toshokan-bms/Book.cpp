// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Book-class Source Code

#include <cstdint>
#include <ostream>
#include <string>
#include <string_view>

#include <toshokan-bms/Book.hpp>

Book::Book(uint64_t isbn, std::string_view t, std::string_view a,
std::string_view p, uint32_t y) : m_ISBN(isbn), m_title(t),
m_author(a), m_publisher(p), m_year(y) {
}

Book::Book(const Book& i) :  m_ISBN(i.m_ISBN), m_title(i.m_title),
m_author(i.m_author), m_publisher(i.m_publisher), m_year(i.m_year) {
}

Book::~Book() {
}

bool Book::checkISBN(const uint64_t ISBN) const {
    return ISBN == m_ISBN;
}

bool Book::checkTitle(std::string_view title) const {
    if (m_title.find(title) != std::string_view::npos) {
        return true;
    }
    return false;
}

bool Book::checkAuthor(std::string_view author) const {
    if (m_author.find(author) != std::string_view::npos) {
        return true;
    }
    return false;
}

bool Book::checkPublisher(std::string_view pub) const {
    if (m_publisher.find(pub) != std::string_view::npos) {
        return true;
    }
    return false;
}

bool Book::checkYear(const uint32_t year) const {
    return year == m_year;
}

std::ostream& operator<<(std::ostream& out, const Book& i) {
    return i.print(out);
}
