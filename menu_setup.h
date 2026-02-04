#ifndef __MENU_SETUP_H
#define __MENU_SETUP_H

#include <vdr/menuitems.h>

class cOsdMenuSetupPlugins : public cMenuSetupPage {
private:
  void Move(int from, int to);
  void Refresh(void);

public:
  cOsdMenuSetupPlugins();
  eOSState ProcessKey(eKeys Key);
  void Store(void);
};

#endif
