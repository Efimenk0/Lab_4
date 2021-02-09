#include "Lab4.h"

#include <iomanip>

const std::vector<std::string> msgs  = {
"0. Выйти (таблица не сохраняется);",
"1. Сохранить таблицу в файлв;",
"2. Добавить новое предложение;",
"3. Удалить предложениеr;",
"4. Найти предложение;",
"5. Зарегестировать заселение;",
"6. Зарегестировать выселение;",
"7. Показать все предложения;;",
"8. Показать только свободные предложения;"
};


int (*fptr[])(FundClass::Application&) = {
    nullptr,
    Lab4::D_Save,
    Lab4::D_Add,
    Lab4::D_Delete,
    Lab4::D_Find,
    Lab4::D_RegisterIn,
    Lab4::D_RegisterOut,
    Lab4::D_ShowAll,
    Lab4::D_ShowFree
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    Application table = Lab4::Initialization();
    int rc;
    while (rc = Lab4::dialog(msgs))
        if (!fptr[rc](table))
            break;
    return 0;
}
