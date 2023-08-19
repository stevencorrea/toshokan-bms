// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// TextBook-class Source Code

#include <toshokan-bms/TextBook.hpp>

#include <cstdint>
#include <string>
#include <string_view>

TextBook::TextBook(uint32_t isbn, std::string_view t, std::string_view a,
std::string_view p, uint32_t y, std::string_view s) :
Book(isbn, t, a, p, y), m_subject(s) {
}

TextBook::TextBook(const TextBook& b) : Book(b.m_ISBN, b.m_title, b.m_author,
b.m_publisher, b.m_year), m_subject(b.m_subject) {
}

TextBook::~TextBook() {
}

bool TextBook::checkOther(std::string_view subject) const {
    if (m_subject.find(subject) != std::string_view::npos) {
        return true;
    }
    return false;
}

std::ostream& TextBook::print(std::ostream& out) const {
    out << m_title << " " << m_ISBN << " " << m_author << " " << m_publisher
    << " " << m_year << " " << m_subject;
    return out;
}
