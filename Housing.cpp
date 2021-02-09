#include "Housing.h"

namespace FundClass {

    Housing& Housing::set_number_of_housing(int val) {
        if (val < 1)
            throw std::invalid_argument("Неверный номер дома. Попробуйте еще раз.");
        number = val;
        return *this;
    }


    std::ostream& Housing::print(std::ostream& os) const {
        os << "адрес: " << street << ", " << number;
        return os;
    }

}
