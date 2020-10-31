#include "doctest.h"
#include "HuffmanArchiver.h"

#include <sstream>

TEST_CASE("End-to-end #1: simple case") {
    std::string str = "abacabacabac\n";
    std::istringstream in(str);
    std::ostringstream out;
    HuffmanArchiver arch(in, out);
    arch.compress();
    std::istringstream new_in(out.str());
    std::ostringstream new_out;
    HuffmanArchiver arch1(new_in, new_out);
    arch1.extract();
    CHECK(str == new_out.str());
}

TEST_CASE("End-to-end #2: one character") {
    std::string str = "aaaaaaaaa";
    std::istringstream in(str);
    std::ostringstream out;
    HuffmanArchiver arch(in, out);
    arch.compress();
    std::istringstream new_in(out.str());
    std::ostringstream new_out;
    HuffmanArchiver arch1(new_in, new_out);
    arch1.extract();
    CHECK(str == new_out.str());
}

TEST_CASE("End-to-end #3: same frequency") {
    std::string str = "1234567890\n";
    std::istringstream in(str);
    std::ostringstream out;
    HuffmanArchiver arch(in, out);
    arch.compress();
    std::istringstream new_in(out.str());
    std::ostringstream new_out;
    HuffmanArchiver arch1(new_in, new_out);
    arch1.extract();
    CHECK(str == new_out.str());
}

TEST_CASE("End-to-end #4: fibonacci sequence") {
    std::string str = "1233444555556666666677777777777778888888888888888888889999999999999999999999999999999999";
    std::istringstream in(str);
    std::ostringstream out;
    HuffmanArchiver arch(in, out);
    arch.compress();
    std::istringstream new_in(out.str());
    std::ostringstream new_out;
    HuffmanArchiver arch1(new_in, new_out);
    arch1.extract();
    CHECK(str == new_out.str());
}

TEST_CASE("End-to-end #5: chaos") {
    std::string str = "\n\nhul.ewi;fiw893y89h;dlJ'""FW&^*+  __+--=--=ONWOWOWOWstop ||||///?//!@\n#^&^*(%&*$*fwefw";
    std::istringstream in(str);
    std::ostringstream out;
    HuffmanArchiver arch(in, out);
    arch.compress();
    std::istringstream new_in(out.str());
    std::ostringstream new_out;
    HuffmanArchiver arch1(new_in, new_out);
    arch1.extract();
    CHECK(str == new_out.str());
}