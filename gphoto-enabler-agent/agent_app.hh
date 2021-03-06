#ifndef GPHOTO_ENABLER_AGENT_APP_HH_
#define GPHOTO_ENABLER_AGENT_APP_HH_

#include "utility.hh"
#include "hub.hh"
#include "dispatch_source.hh"
#include "discovery_db_fixup.hh"

#include <IOKit/IOKitLib.h>

#include <launch.h>

#include <vector>
#include <memory>


GPHOTO_ENABLER_NS_BEGIN


/*
 * Primary application class
 */
class agent_app {

public:
  agent_app();
  ~agent_app();

  void client_did_connect();
  void client_will_disconnect();
  void setup_device_matching();
  void setup_launchd_listeners();

  bool check_vid_pid(int vid, int pid) {
    return true;
  }

  hub *get_hub() { return &hub; }

  IONotificationPortRef get_notification_port() { return notification_port; }

private:
  void init_devices(io_iterator_t iter);

  static void init_devices_cb(void *p, io_iterator_t iter);

  static void setup_launchd_listeners_helper(
    launch_data_t sockets, const char *name, void *p);

  void timed_killer_set_timer();

  IONotificationPortRef      notification_port;
  dispatch_source            timed_killer;
  std::vector<std::unique_ptr<dispatch_source>>
                             other_sources;
  std::unique_ptr<discovery_db_fixup>
                             fixup;
  int                        clients_count;
  hub                        hub;
};


GPHOTO_ENABLER_NS_END

#endif

