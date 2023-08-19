// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Novel Header

#ifndef TOSHOKAN_BMS_NOVEL_HPP_
#define TOSHOKAN_BMS_NOVEL_HPP_

#include <string>
#include <string_view>

#include <toshokan-bms/Book.hpp>

class Novel : public Book {
 private:
    std::string m_genre;

 public:
    Novel(uint32_t isbn, std::string_view t, std::string_view a,
    std::string_view p, uint32_t y, std::string_view g);
    Novel(const Novel&);
    virtual ~Novel();
    virtual bool checkOther(std::string_view) const;
    virtual std::ostream& print(std::ostream& out) const;
};


#endif  // TOSHOKAN_BMS_NOVEL_HPP_
