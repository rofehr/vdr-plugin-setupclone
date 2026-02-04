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

    char *tmp = strdup(Value);
    char *p = tmp;
    char *token;

    while ((token = strsep(&p, ",")) != nullptr) {
      if (*token)
        PluginOrder.emplace_back(token);
    }

    free(tmp);
    return true;
  }
  return false;
}

VDRPLUGINCREATOR(cPluginSetupClone);
