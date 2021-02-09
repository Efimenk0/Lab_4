#include "Flat.h"

namespace FundClass
{

    Flat::Flat(const std::string& str) : Housing(str), number(-1)
    {
        rooms[0].set_name("гостинная");
        rooms[1].set_name("кухня");
        rooms[2].set_name("санузел");
        rooms[3].set_name("прихожая");
    }

    double Flat::get_area() const
    {
        return rooms[0].get_area() + rooms[1].get_area() + rooms[2].get_area() + rooms[3].get_area();
    }


    Flat& Flat::set_number(int val) {
        if (val < 1)
            throw std::invalid_argument("Неверный номер квартиры. Попробуйте еще раз.");
        number = val;
        return *this;
    }

    Room& Flat::select_room(int pos) {
        if (pos < 1 || pos > 4)
            throw std::out_of_range("Неверный номер квартиры. Попробуйте еще раз.");
        return rooms[pos - 1];
    }

    std::ostream& Flat::print(std::ostream& os) const {
        os << "Тип жилья: квартира; ";
        Housing::print(os) << ", кв. " << number << ";";
        for (int i = 0; i < 4; ++i)
            os << "\n " << rooms[i];
        os << "\nОбщая жилая площадь квартиры: " << get_area();
        return os;
    }


    std::ostream& operator << (std::ostream& os, const Flat& flat) {
        flat.print(os);
        return os;
    }

}
