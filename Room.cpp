
#include "Room.h"

namespace FundClass {

    Room& Room::set_area(double val) {
        if (val <= 0)
            throw std::invalid_argument("Неверная площадь. Попробуйте еще раз.");
        area = val;
        return *this;
    }

    std::ostream& operator <<(std::ostream& os, const Room& room) {
        os << "название комнаты: " << room.name << "; площадь: " << room.area << "; комментарий: " << room.remark << ";";
        return os;
    }


}
