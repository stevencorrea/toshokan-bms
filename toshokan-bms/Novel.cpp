// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Novel-class Source Code

#include <toshokan-bms/Novel.hpp>

#include <cstdint>
#include <string>
#include <string_view>

Novel::Novel(uint32_t isbn, std::string_view t, std::string_view a,
std::string_view p, uint32_t y, std::string_view g) :
Book(isbn, t, a, p, y),  m_genre(g) {
}

Novel::Novel(const Novel& n) : Book(n.m_ISBN, n.m_title, n.m_author, n.m_publisher,
n.m_year), m_genre(n.m_genre) {
}

Novel::~Novel() {
}

bool Novel::checkOther(std::string_view genre) const {
    if (m_genre.find(genre) != std::string_view::npos) {
        return true;
    }
    return false;
}

std::ostream& Novel::print(std::ostream& out) const {
    out << m_title << " " << m_ISBN << " " << m_author << " " << m_publisher
    << " " << m_year << " " << m_genre;
    return out;
}
