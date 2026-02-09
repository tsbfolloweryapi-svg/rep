#include "pch.h"
#// Р¤Р°Р№Р»: Task3/MenuItem.cpp
#// Р”РµР№СЃС‚РІРёРµ: СЂРµР°Р»РёР·СѓРµРј СЌР»РµРјРµРЅС‚ РјРµРЅСЋ
#include "MenuItem.h"
// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

MenuItem::MenuItem() :MenuItem(1, "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ"s) {}

MenuItem::MenuItem(int command, const string &text):
	command_(command), text_(text), selected_(false)
{
} // MenuItem::MenuItem

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
int MenuItem::command() const { return command_; }
const string &MenuItem::text() const { return text_; }

// фильтруем
bool MenuItem::isSelected() const { return selected_; }
// фильтруем
void MenuItem::selected(bool value) { selected_ = value; }
