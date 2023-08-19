// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// GraphicNovel-class Source Code

#include <toshokan-bms/GraphicNovel.hpp>

#include <cstdint>
#include <string>
#include <string_view>

GraphicNovel::GraphicNovel(uint32_t isbn, std::string_view t, std::string_view a,
std::string_view p, uint32_t y, std::string_view i) :
Book(isbn, t, a, p, y), m_artist(i) {
}

GraphicNovel::GraphicNovel(const GraphicNovel& b) : Book(b.m_ISBN, b.m_title, b.m_author,
b.m_publisher, b.m_year), m_artist(b.m_artist) {
}

GraphicNovel::~GraphicNovel() {
}

bool GraphicNovel::checkOther(std::string_view artist) const {
    if (m_artist.find(artist) != std::string_view::npos) {
        return true;
    }
    return false;
}

std::ostream& GraphicNovel::print(std::ostream& out) const {
    out << m_title << " " << m_ISBN << " " << m_author << " " << m_publisher
    << " " << m_year << " " << m_artist;
    return out;
}
