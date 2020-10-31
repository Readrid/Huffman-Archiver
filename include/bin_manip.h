#ifndef _BIN_MANIP_H_
#define _BIN_MANIP_H_

#include <iostream>

class write_le_int32 {
public:
    write_le_int32(int32_t number);
    std::ostream& operator()(std::ostream &out) const;

private:
    int32_t number;
    char buf[4];
};

std::ostream &operator<<(std::ostream &out, const write_le_int32 &manip);

class read_le_int32 {
public:
    read_le_int32(int32_t &number);
    std::istream& operator()(std::istream &in) const;

private:
    int32_t &number;
};

std::istream &operator>>(std::istream &in, const read_le_int32 &manip);


#endif