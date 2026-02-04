#include "setupclone.h"
#include "menu_plugins.h"
#include "menu_setup.h"
#include <vdr/tools.h>
#include <cstring>

std::vector<std::string> PluginOrder;

cOsdObject *cPluginSetupClone::MainMenuAction(void)
{
  return new cOsdMenuSortedPlugins;
}

cMenuSetupPage *cPluginSetupClone::SetupMenu(void)
{
  return new cOsdMenuSetupPlugins;
}

bool cPluginSetupClone::SetupParse(const char *Name, const char *Value)
{
  if (!strcmp(Name, "Order")) {
    PluginOrder.clear();
    cString s = Value;
    char *p;
    while ((p = strsep(&s, ",")))
      PluginOrder.emplace_back(p);
    return true;
  }
  return false;
}

VDRPLUGINCREATOR(cPluginSetupClone);
