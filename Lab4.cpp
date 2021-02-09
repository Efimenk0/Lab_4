
#include "Lab4.h"
#include "Cottage.h"
#include "Apartments.h"
#include "Flat.h"

#define line "----------------------------------------------------------"



namespace Lab4 {

int dialog(const std::vector<std::string> msgs) {
        std::string errmsgs = "";
        int rc, i;
        do {
            std::cout << errmsgs;
            errmsgs = "Ошибка! Повторите ввод!";
            for (i = 0; i < msgs.size(); ++i)                    // Вывод списка альтернатив
                std::cout << (msgs[i]) << "\n";
            printf("Выберите: --> ");
            inputType(rc, std::cin, std::cout);
        } while (rc >= msgs.size());
        return rc;
    }


    FundClass::Application Initialization() {
        while (true) {
            std::cout << "Выберите: 1 - Создать новую таблицу; 2 - Загрузить существующую;\n --> ";
            int choose = 0;
            inputType(choose, std::cin, std::cout);
            while (choose < 1 || choose > 2) {
                std::cout << "Неверное число! Попробуйте еще раз:ы\n--> ";
                getType(choose, std::cin);
            }
            if (choose == 2) {
                std::cout << "Введите имя файла: --> ";
                std::string filename;
                std::getline(std::cin, filename);
                try {
                    Application table;
                    table.load(filename);
                    return table;
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << "\n";
                }
            }
            else {
                Application table;
                return table;
            }
        }
    }



    int D_Save(FundClass::Application& table) {
        std::string filename;
        std::cout << "Введите имя файла: --> ";
        std::getline(std::cin, filename);
        try {
            table.save(filename);
            std::cout << "Таблица успешно создана!\n";
            return 1;
        }
        catch (const std::invalid_argument& ex) {
            std::cout << ex.what() << "\n";
        }
        return 1;
    }


    int D_Add(Application& table) {
        Housing* ptr = nullptr;
        std::cout << "ВЫберите тип жилья:\n 1 - квартира;\n 2 - апартаменты;\n 3 - коттедж;\n --> ";
        int choose;
        inputType(choose, std::cin, std::cout);
        while (choose < 1 || choose > 3) {
            std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
            getType(choose, std::cin);
        }
        std::string street;
        int house;
        std::cout << "Введите улицу: --> ";
        std::getline(std::cin, street);
        std::cout << "Введите номер дома: --> ";
        inputType(house, std::cin, std::cout);
        if (choose == 1) {
            bool st = true;
            while (st) {
                int door;
                std::cout << "Введите номер квартиры: --> ";
                inputType(door, std::cin, std::cout);
                if (table.find(street, house, door) != -1)
                {
                    std::cout << "Жилье по данному адресу уже зарегестировано. Попробуйте еще раз.\n";
                    continue;
                }
                try {
                    ptr = new Flat(street);
                    ptr->set_number_of_housing(house);
                    dynamic_cast<Flat*>(ptr)->set_number(door);
                    st = !st;
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << "\n";
                }
            }
            std::cout << "Теперь опишите помещения: прихожая, кухня, санузел, гостинная:\n ";
            std::string rooms[4] = { "прихожая", "кухня", "санузел", "гостинная" };
            for (int i = 0; i < 4; ++i) {
                bool state = true;
                while (state) {
                    double area;
                    std::cout << "Площадь: " << rooms[i] << ": -- > ";
                    inputType(area, std::cin, std::cout);
                    std::string remark;
                    std::cout << "Комментарий: --> ";
                    std::getline(std::cin, remark);
                    Room* room = nullptr;
                    room = create_room(rooms[i], area, remark);
                    if (room) {
                        state = !state;
                        dynamic_cast<Flat*>(ptr)->select_room(i + 1) = *room;
                    }
                    else
                        continue;
                    delete room;
                }
            }
        }
        else if (choose == 2) {
            bool st = true;
            while (st)
            {
                int door;
                std::cout << "Введите номер апартаментов: --> ";
                inputType(door, std::cin, std::cout);
                if (table.find(street, house, door) != -1)
                {
                    std::cout << "Жилье по данному адресу уже зарегистрировано. Попробуйте еще раз\n";
                    continue;
                }
                try {
                    ptr = new Apartments(street);
                    ptr->set_number_of_housing(house);
                    dynamic_cast<Apartments*>(ptr)->set_number(door);
                    st = !st;
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << "\n";
                    continue;
                }
            }
            int count;
            std::cout << "Введите кол-во комнат в апартаментах: --> ";
            inputType(count, std::cin, std::cout);
            while (count < 1) {
                std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
                getType(count, std::cin);
            }
            for (int i = 0; i < count; ++i) {
                bool state = true;
                while (state) {
                    std::string name;
                    std::cout << "Введите название: --> ";
                    std::getline(std::cin, name);
                    double area;
                    std::cout << "Площадь: -- > ";
                    inputType(area, std::cin, std::cout);
                    std::string remark;
                    std::cout << "Комментарий: --> ";
                    std::getline(std::cin, remark);
                    Room* room = nullptr;
                    room = create_room(name, area, remark);
                    if (room) {
                        state = !state;
                        dynamic_cast<Apartments*>(ptr)->add_room(*room);
                    }
                    else
                        continue;
                    delete room;
                }
            }
        }
        else {
            bool st = true;
            while (st) {
                if (table.find(street, house, -1) != -1) {
                    std::cout << "Жилье по данному адресу уже зарегестировано. Попробуйте еще раз.\n";
                    continue;
                }
                try {
                    ptr = new Cottage(street);
                    ptr->set_number_of_housing(house);
                    st = !st;
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << "\n";
                    continue;
                }
            }
            int count;
            std::cout << "Введите кол-во строений в коттедже: --> ";
            inputType(count, std::cin, std::cout);
            while (count < 1)
            {
                std::cout << "Неверное число! Попробуйте еще рвз\n--> ";
                getType(count, std::cin);
            }
            for (int i = 0; i < count; ++i) {
                Building* b = create_building();
                dynamic_cast<Cottage*>(ptr)->add_building(*b);
                delete b;
            }
        }
        bool state = true;
        while (state) {
            double val;
            std::cout << "Введите стоимость 1 кв. метра жилья: --> ";
            inputType(val, std::cin, std::cout);
            try {
                table.insert(ptr, val);
                state = !state;
                std::cout << "Жилье успешно добавлено!" << "\n";
            }
            catch (const std::invalid_argument& ex) {
                std::cout << ex.what() << "\n";
            }
        }
        return 1;
    }



    Room* create_room(const std::string& name, double area, const std::string& remark) {
        Room* ptr = new Room(name);
        try {
            ptr->set_remark(remark).set_area(area);
            return ptr;
        }
        catch (const std::invalid_argument& ex) {
            std::cout << ex.what();
            delete ptr;
        }
        return nullptr;
    }


    Building* create_building() {
        Building* ptr = new Building;
        bool state = true;
        while (state) {
            int number;
            std::cout << "Введите номер здания: --> ";
            getType(number, std::cin);
            try
            {
                ptr->set_number(number);
                state = !state;
            }
            catch (const std::invalid_argument& ex)
            {
                std::cout << ex.what();
            }
        }
        while (true) {
            std::cout << "Выберите:\n 1 - Добавить новую комнату\n 2 - Удалить существующую;\n 0 - Вернуться обратно;\n --> ";
            int choose;
            inputType(choose, std::cin, std::cout);
            while (choose < 0 || choose > 2) {
                std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
                getType(choose, std::cin);
            }
            if (!choose)
                return ptr;
            if (choose == 1) {
                Room* room = nullptr;
                std::string name;
                std::cout << "Введите название комнаты: --> ";
                std::getline(std::cin, name);
                int area;
                std::cout << "Площадь: --> ";
                inputType(area, std::cin, std::cout);
                std::string remark;
                std::cout << "Комментарий: --> ";
                std::getline(std::cin, remark);
                if (room = create_room(name, area, remark)) {
                    ptr->add_room(*room);
                    std::cout << "Комната успешно добавлена:\n" << *ptr << "\n";
                }
                delete room;
            }
            else {
                int number;
                std::cout << "Введите номер комнты: --> ";
                inputType(number, std::cin, std::cout);
                try {
                    ptr->exclude_room(number);
                    std::cout << "Комната успешно добвлена:\n" << *ptr << "\n";
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << "\n";
                }
            }

        }
    }


    int D_Delete(Application& table) {
        while (true) {
            int choose;
            std::cout << "1. Продолжить.\n0. Вернуться в меню.\n --> ";
            inputType(choose, std::cin, std::cout);
            while (choose < 0 || choose > 1) {
                std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
                getType(choose, std::cin);
            }
            if (!choose)
                break;
            std::string street;
            int house;
            int door = -1;
            adress(street, house, door);
            int i = table.find(street, house, door);
            if (i == -1) {
                std::cout << "Жилья с таким адресом нет. Попробуйте еще раз.\n";
            }
            else {
                std::cout << line << "Предложение #" << i + 1 << ":\n" << ((*table.access_to_table())[i]) << "\n успешно удалено из таблицы.\n";
                table.access_to_table()->erase(table.access_to_table()->begin() + i);
                return 1;
            }
        }
        return 1;
    }


    int D_Find(Application& table) {
        while (true) {
            int choose;
            std::cout << "1. Продолжить.\n0. Вернуться в меню.\n --> ";
            inputType(choose, std::cin, std::cout);
            while (choose < 0 || choose > 1) {
                std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
                getType(choose, std::cin);
            }
            if (!choose)
                break;
            std::string street;
            int house;
            int door = -1;
            adress(street, house, door);
            int i = table.find(street, house, door);
            if (i == -1) {
                std::cout << "Жилья с таким адресом нет. Попробуйте еще раз.\n";
            }
            else {
                std::cout << line << "Найдено предложение:\n" << "\n" << (*table.access_to_table())[i] << "\n" << line << "\n";
                return 1;
            }
        }
        return 1;
    }


    int D_RegisterIn(Application& table) {
        while (true) {
            int choose;
            std::cout << "1. Продолжить.\n0. Вернуться в меню.\n --> ";
            inputType(choose, std::cin, std::cout);
            while (choose < 0 || choose > 1) {
                std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
                getType(choose, std::cin);
            }
            if (!choose)
                break;
            std::string street;
            int house;
            int door = -1;
            adress(street, house, door);
            int i = table.find(street, house, door);
            if (i == -1) {
                std::cout << "Жилья с таким адресом нет. Попробуйте еще раз.\n";
            }
            else {
                if ((*table.access_to_table())[i].get_status())
                    std::cout << "Жилье с таким адресом уже зарегестировано.\n";
                else {
                    (*table.access_to_table())[i].change_status();
                    std::cout << line << "\nЗаселение успешно зарегестировано:\n" << line << "\n" << (*table.access_to_table())[i] << "\n";
                }
                return 1;
            }
        }
        return 1;
    }


    int D_RegisterOut(Application& table) {
        while (true) {
            int choose;
            std::cout << "1. Продолжить\n0. Вернуться в меню.\n --> ";
            inputType(choose, std::cin, std::cout);
            while (choose < 0 || choose > 1) {
                std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
                getType(choose, std::cin);
            }
            if (!choose)
                break;
            std::string street;
            int house;
            int door = -1;
            adress(street, house, door);
            int i = table.find(street, house, door);
            if (i == -1) {
                std::cout << "Жилья с таким адресом нет. Попробуйте еще раз.\n";
            }
            else {
                if (!(*table.access_to_table())[i].get_status())
                    std::cout << "Жилье с таким адресом уже свободно.\n";
                else {
                    (*table.access_to_table())[i].change_status();
                    std::cout << line << "\nЖилье успешно освобождено:\n" << line << "\n" << (*table.access_to_table())[i];
                }
                return 1;
            }
        }
        return 1;
    }


    int D_ShowAll(Application& table) {
        std::cout << line << "\n" << table << "\n" << line << "\n";
        return 1;
    }


    int D_ShowFree(Application& table) {
        std::cout << line << "\n";
        for (int i = 0; i < table.access_to_table()->size(); ++i)
            if (!(*table.access_to_table())[i].get_status())
                std::cout << " Предложение #" << i + 1 << ":\n" << (*table.access_to_table())[i] << "\n";
        std::cout << line << "\n";
        return 1;
    }


    void adress(std::string& street, int& house, int& door) {
        std::cout << "Введите название улицы: --> ";
        std::getline(std::cin, street);
        std::cout << "Введите номер дома/строения: --> ";
        inputType(house, std::cin, std::cout);
        std::cout << "Ваше жилье квартира/апартаменты? 1 - да, 2 - нет: --> ";
        int choose;
        inputType(choose, std::cin, std::cout);
        while (choose < 1 || choose > 2) {
            std::cout << "Неверное число! Попробуйте еще раз:\n--> ";
            getType(choose, std::cin);
        }
        if (choose == 1)
        {
            std::cout << "Введите номер квартиры/апартаментов: --> ";
            inputType(door, std::cin, std::cout);
        }
    }

}
