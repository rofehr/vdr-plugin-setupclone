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
: cOsdMenu(tr("Plugin-Sort"))
{
  for (const auto &name : PluginOrder) {
    cPlugin *p = cPluginManager::GetPlugin(name.c_str());
    if (p && p->MainMenuEntry())
      Add(new cPluginMenuItem(p));
  }

  Display();
};


eOSState cOsdMenuSortedPlugins::ProcessKey(eKeys Key)
{
    if (Key == kOk) {
        cPluginMenuItem *item =
            dynamic_cast<cPluginMenuItem*>(Get(Current()));
        if (item && item->plugin) {
            cOsdObject *o = item->plugin->MainMenuAction();
            if (o) {
                cOsdMenu *menu = dynamic_cast<cOsdMenu*>(o);
                if (menu)
                    return AddSubMenu(menu);
                else
                    delete o; // Plugin liefert kein Menü, sauber löschen
            }
        }
        return osContinue;
    }

    return cOsdMenu::ProcessKey(Key);
};

