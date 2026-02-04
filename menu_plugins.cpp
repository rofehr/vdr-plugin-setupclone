#include "menu_plugins.h"
#include "setupclone.h"

#include <vdr/plugin.h>
#include <vdr/menuitems.h>

class cPluginMenuItem : public cOsdItem {
private:
  cPlugin *plugin;
public:
  cPluginMenuItem(cPlugin *Plugin)
  : cOsdItem(Plugin->MainMenuEntry()), plugin(Plugin) {}

  eOSState ProcessKey(eKeys Key) override
  {
    if (Key == kOk) {
      cOsdObject *o = plugin->MainMenuAction();
      if (o)
        return AddSubMenu(o);
      return osContinue;
    }
    return cOsdItem::ProcessKey(Key);
  }
};


cOsdMenuSortedPlugins::cOsdMenuSortedPlugins()
: cOsdMenu(tr("Plugins"))
{
  // 1. Sortierte Plugins
  for (const auto &name : PluginOrder) {
    cPlugin *p = cPluginManager::GetPlugin(name.c_str());
    if (p && p->MainMenuEntry())
      Add(new cPluginMenuItem(p));
  }

  // 2. Restliche Plugins anhängen
  for (cPlugin *p = cPluginManager::First(); p; p = cPluginManager::Next(p)) {
    if (!p->MainMenuEntry())
      continue;

    bool known = false;
    for (auto &n : PluginOrder)
      if (n == p->Name())
        known = true;

    if (!known)
      Add(new cPluginMenuItem(p));
  }

  Display();
}
