#ifndef __MENU_PLUGINS_H
#define __MENU_PLUGINS_H

#include <vdr/osdbase.h>
#include <vdr/plugin.h>

class cPluginMenuItem : public cOsdItem {
public:
	cPlugin *plugin;
	cPluginMenuItem(cPlugin *Plugin)
	: cOsdItem(Plugin->MainMenuEntry()), plugin(Plugin) {}
};


class cOsdMenuSortedPlugins : public cOsdMenu {
public:
  cOsdMenuSortedPlugins();
  eOSState ProcessKey(eKeys Key) override;
};

#endif
