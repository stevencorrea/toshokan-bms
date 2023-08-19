// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// GraphicNovel Header

#ifndef TOSHOKAN_BMS_GRAPHICNOVEL_HPP_
#define TOSHOKAN_BMS_GRAPHICNOVEL_HPP_

#include <string>
#include <string_view>

#include <toshokan-bms/Book.hpp>

class GraphicNovel : public Book {
 private:
    std::string m_artist;

 public:
    GraphicNovel(uint32_t isbn, std::string_view t, std::string_view a,
    std::string_view p, uint32_t y, std::string_view i);
    GraphicNovel(const GraphicNovel&);
    virtual ~GraphicNovel();
    virtual bool checkOther(std::string_view) const;
    virtual std::ostream& print(std::ostream& out) const;
};


#endif  // TOSHOKAN_BMS_GRAPHICNOVEL_HPP_
