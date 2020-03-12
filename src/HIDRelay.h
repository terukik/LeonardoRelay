/** HIDRelay.h
 */

#ifndef HIDRELAY_h
#define HIDRELAY_h

#include "USBAPI.h"
#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

#if !defined(HIFRELAY_SERIAL)
#define HIFRELAY_SERIAL "UNSET"
#endif /* !defined(HIFRELAY_SERIAL) */
#if !defined(HIFRELAY_NUMBER)
#define HIFRELAY_NUMBER (2)
#endif /* !defined(HIFRELAY_NUMBER) */

#if !defined(USB_PRODUCT)
#define USB_PRODUCT     ['U', 'S', 'B', 'R', 'e', 'l', 'a', 'y', '0' + HIFRELAY_NUMBER, '\0']
#endif /* !defined(USB_PRODUCT */
#if !defined(USB_VID)
#define USB_VID (0x16C0)
#endif /* !defined(USB_VID) */
#if !defined(USB_PID)
#define USB_PID (0x05DC)
#endif /* !defined(USB_PID) */
#if !defined(USB_MANUFACTURER)
#define USB_MANUFACTURER "www.dcttech.com"
#endif /* !defined(USB_MANUFACTURER) */

//================================================================================
//================================================================================

class HIDRelay_
{
private:
  unsigned int _relays;
public:
  HIDRelay_(void);
  void begin();
  void end();
  unsigned int get();
  void set(unsigned int relays);
};
extern HIDRelay_ HIDRelay;

#endif
#endif
