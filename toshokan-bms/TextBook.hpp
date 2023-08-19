// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// TextBook Header

#ifndef TOSHOKAN_BMS_TEXTBOOK_HPP_
#define TOSHOKAN_BMS_TEXTBOOK_HPP_

#include <string>
#include <string_view>

#include <toshokan-bms/Book.hpp>

class TextBook : public Book {
 private:
    std::string m_subject;

 public:
    TextBook(uint32_t isbn, std::string_view t, std::string_view a,
    std::string_view p, uint32_t y, std::string_view s);
    TextBook(const TextBook&);
    virtual ~TextBook();
    virtual bool checkOther(std::string_view) const;
    virtual std::ostream& print(std::ostream& out) const;
};


#endif  // TOSHOKAN_BMS_TEXTBOOK_HPP_
