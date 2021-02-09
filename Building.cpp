#include "Building.h"

namespace FundClass {

    double Building::get_area() const {
        double res = 0;
        for (int i = 0; i < countOfRooms; ++i)
            res += rooms[i].get_area();
        return res;
    }

    Building& Building::set_number(int val) {
        if (val < 1)
            throw std::invalid_argument("Неверный номер дома. Попробуйте еще раз.");
        number = val;
        return *this;
    }


    Building& Building::add_room(Room& room) {
        rooms.push_back(room);
        ++countOfRooms;
        return *this;
    }

    Building& Building::exclude_room(int pos) {
        if (pos < 1 || pos > countOfRooms)
            throw std::invalid_argument("Неверный номер комнаты. Попробуйте еще раз.");
        rooms.erase(rooms.begin() + pos - 1);
        --countOfRooms;
        return *this;
    }

    Room& Building::select_room(int pos) {
        if (pos < 1 || pos > countOfRooms)
            throw std::invalid_argument("Неверный номер комнаты. Попробуйте еще раз.");
        return rooms[pos - 1];
    }

    const Room& Building::get_room(int pos) const {
        if (pos < 1 || pos > countOfRooms)
            throw std::invalid_argument("Неверный номер комнаты. Попробуйте еще раз.");
        return rooms[pos - 1];
    }

    std::ostream& operator <<(std::ostream& os, const Building& building) {
        os << "строение #" << building.number << "; кол-во комнат: " << building.countOfRooms << ";";
        for (int i = 0; i < building.countOfRooms; ++i)
            os << "\n#" << i + 1 << ": " << building.rooms[i];
        os << "\nОбщая жилая площадь: " << building.get_area();
        return os;
    }

}
