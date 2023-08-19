// Copyright 2023 Michael Larson
// Toshokan-BMS for CINS242
// Book-class Header

#ifndef TOSHOKAN_BMS_BOOK_HPP_
#define TOSHOKAN_BMS_BOOK_HPP_

#include <cstdint>
#include <ostream>
#include <string>
#include <string_view>

class Book {
 protected:
    uint64_t m_ISBN;
    std::string m_title;
    std::string m_author;
    std::string m_publisher;
    uint32_t m_year;

 public:
    Book(uint64_t, std::string_view, std::string_view, std::string_view,
    uint32_t);
    Book(const Book&);
    virtual ~Book();
    bool checkISBN(const uint64_t) const;
    bool checkTitle(std::string_view) const;
    bool checkAuthor(std::string_view) const;
    bool checkPublisher(std::string_view) const;
    bool checkYear(uint32_t) const;
    virtual bool checkOther(std::string_view) const = 0;
    virtual std::ostream& print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const Book& i);
};

#endif  // TOSHOKAN_BMS_BOOK_HPP_
