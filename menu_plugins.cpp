#include "menu_plugins.h"
#include "setupclone.h"

#include <vdr/plugin.h>
#include <vdr/menuitems.h>


class cPluginMenuItem : public cOsdItem {
public:
  cPlugin *plugin;

  cPluginMenuItem(cPlugin *Plugin)
  : cOsdItem(Plugin->MainMenuEntry()), plugin(Plugin) {}
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

  // 2. Restliche Plugins anhängen (VDR 2.7.x Iterator)
  for (cPlugin *p : cPluginManager::Plugins()) {
    if (!p->MainMenuEntry()) continue;

    bool known = false;
    for (auto &n : PluginOrder)
      if (n == p->Name())
        known = true;

    if (!known)
      Add(new cPluginMenuItem(p));
  }

  Display();
};


eOSState cOsdMenuSortedPlugins::ProcessKey(eKeys Key)
{
  if (Key == kOk) {
    cPluginMenuItem *item =
      dynamic_cast<cPluginMenuItem *>(Get(Current()));

    if (item && item->plugin) {
      cOsdObject *o = item->plugin->MainMenuAction();
      if (o)
        return AddSubMenu(o);
    }
    return osContinue;
  }

  return cOsdMenu::ProcessKey(Key);
};

