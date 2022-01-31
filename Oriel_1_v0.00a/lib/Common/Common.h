#ifndef COMMON_h
#define COMMON_h

#define DEVICE_NAME "MIRA"
#define DEVICE_VERSION 1.0
#define FIRMWARE_VERSION "0.00a"

enum FirmwareState
{
  IMAGE_CYCLING,
  ORIEL_SERVER_SYNCING,
  HOSTING_INTERNAL_SERVER
};

enum PowerState
{
  BATTERY,
  PLUGIN
};

/**
 * DisplayTheme
 * ------------
 * General display properties for the device. Defines
 * the theme of the basic device UI.
 */
struct DisplayTheme
{
  uint16_t background_color;
  uint16_t text_color;
};

#endif /* _COMMON_H */