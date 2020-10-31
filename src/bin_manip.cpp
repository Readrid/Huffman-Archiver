#include "bin_manip.h"

write_le_int32::write_le_int32(int32_t number) : number(number) {
    buf[0] = number;
    buf[1] = number >> 8;
    buf[2] = number >> 16;
    buf[3] = number >> 24;
}

std::ostream& write_le_int32::operator()(std::ostream &out) const {
    out.write(buf, 4);
    return out;
}

std::ostream &operator<<(std::ostream &out, const write_le_int32 &manip) {
    return manip(out);
}

read_le_int32::read_le_int32(int32_t &number) : number(number) {}

std::istream& read_le_int32::operator()(std::istream &in) const {
    int32_t *number_pointer = &number;
    char *byte_number = reinterpret_cast<char*>(number_pointer);
    in.read(byte_number, 4);
    return in;
}

std::istream &operator>>(std::istream &in, const read_le_int32 &manip) {
    return manip(in);
}
