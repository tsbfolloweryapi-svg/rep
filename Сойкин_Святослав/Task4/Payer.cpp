#// Р¤Р°Р№Р»: Task4/Payer.cpp
#// Р”РµР№СЃС‚РІРёРµ: СЂРµР°Р»РёР·СѓРµРј РїР»Р°С‚РёР»СЊС‰РёРєР° Рё РѕРїРµСЂР°С†РёРё СЃ РЅРёРј
#include "Payer.h"
// выполняем действие
#include "Utils.h"
#include <sstream>

Payer Payer::createFactory(int id) {
    Payer p;
    p.setId(id);
    p.setName("пїЅпїЅпїЅпїЅпїЅпїЅпїЅ" + to_string(getRand(1, 20)));
    p.setPhone("062-" + to_string(getRand(121, 333)));
    p.setTariff(getRand(1.0, 5.0));
    p.setDiscount(getRand(0, 20));
    p.setTimeMin(getRand(10, 200));
    p.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));
// выполняем действие
    return p;
}

string Payer::toString() const {
    ostringstream oss;
    oss << "ID: " << getId() << ", пїЅпїЅпїЅ: " << getName() << ", пїЅпїЅпїЅпїЅпїЅпїЅпїЅ: " << getPhone()
        << ", пїЅпїЅпїЅпїЅпїЅ: " << fixed << setprecision(2) << getTariff() << ", пїЅпїЅпїЅпїЅпїЅпїЅ: " << getDiscount()
        << ", пїЅпїЅпїЅпїЅпїЅпїЅ: " << getTimeMin() << ", пїЅпїЅпїЅпїЅ: " << getDate().toString() << ", пїЅпїЅпїЅпїЅпїЅ: " << calculateSum();
    return oss.str();
}
