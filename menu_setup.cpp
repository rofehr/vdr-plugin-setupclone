#include "menu_setup.h"
#include "setupclone.h"
#include <vdr/plugin.h>

cOsdMenuSetupPlugins::cOsdMenuSetupPlugins()
{
  if (PluginOrder.empty()) {
//    for (cPlugin *p = cPluginManager::First(); p; p = cPluginManager::Next(p)) {
//      if (p->MainMenuEntry())
//        PluginOrder.emplace_back(p->Name());
//    }
  }
  Refresh();
}

void cOsdMenuSetupPlugins::Refresh(void)
{
  Clear();
  SetTitle(tr("Sort plugins (Red=Up Green=Down)"));
  for (auto &n : PluginOrder)
    Add(new cOsdItem(n.c_str()));
  Display();
}

void cOsdMenuSetupPlugins::Move(int f, int t)
{
  if (t < 0 || t >= (int)PluginOrder.size()) return;
  std::swap(PluginOrder[f], PluginOrder[t]);
  SetCurrent(t);
  Refresh();
}

eOSState cOsdMenuSetupPlugins::ProcessKey(eKeys k)
{
  int c = Current();
  if (k == kRed)   { Move(c, c - 1); return osContinue; }
  if (k == kGreen) { Move(c, c + 1); return osContinue; }
  return cMenuSetupPage::ProcessKey(k);
}

void cOsdMenuSetupPlugins::Store(void)
{
  cString s;
  for (size_t i = 0; i < PluginOrder.size(); ++i)
    s = i ? cString::sprintf("%s,%s", *s, PluginOrder[i].c_str())
          : PluginOrder[i].c_str();
  SetupStore("Order", *s);
}
