#ifndef __SETUPCLONE_H
#define __SETUPCLONE_H

#include <vdr/plugin.h>
#include <vector>
#include <string>

extern std::vector<std::string> PluginOrder;

class cPluginSetupClone : public cPlugin {
public:
  const char *Version(void) { return "1.0"; }
  const char *Description(void) { return "Plugin menu setup (setup clone)"; }

  const char *MainMenuEntry(void) { return tr("Pluginsort"); }
  cOsdObject *MainMenuAction(void);

  cMenuSetupPage *SetupMenu(void);
  bool SetupParse(const char *Name, const char *Value);
};

#endif
