#include "menu_plugins.h"
#include "setupclone.h"
#include <vdr/plugin.h>
#include <algorithm>

cOsdMenuSortedPlugins::cOsdMenuSortedPlugins()
: cOsdMenu(tr("Plugins"))
{
  for (const auto &name : PluginOrder) {
    cPlugin *p = cPluginManager::GetPlugin(name.c_str());
    if (p && p->MainMenuEntry())
      Add(new cMenuPluginItem(p));
  }

  for (cPlugin *p = cPluginManager::First(); p; p = cPluginManager::Next(p)) {
    if (!p->MainMenuEntry()) continue;
    if (std::find(PluginOrder.begin(), PluginOrder.end(), p->Name()) == PluginOrder.end())
      Add(new cMenuPluginItem(p));
  }

  Display();
}
