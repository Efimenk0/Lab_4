#include "Table.h"


namespace mystd {

ElemOfTable& ElemOfTable::set_price(double val) {
    if (val < 0)
        throw std::invalid_argument("Неверная цена. Попробуйте еще раз.");
    price = val;
    return *this;
}

std::ostream& operator <<(std::ostream& os, const ElemOfTable& eot) {
    os << *eot.house << "\nЦена за 1 кв.м: " << eot.price << ";\n статус: ";
    if (eot.status)
        os << "заселено.";
    else
        os << "не заселено.";
    return os;
}


}
