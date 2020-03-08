/** HIDRelay.cpp
 */

#include "HIDRelay.h"

#if defined(_USING_HID)

//================================================================================
//================================================================================
//	HIDRelay

#define CMD_ALL_ON      (0xFE)
#define CMD_ALL_OFF     (0xFC)
#define CMD_ON          (0xFF)
#define CMD_OFF         (0xFD)
#define CMD_SET_SERIAL  (0xFA)

#define REPORT_SIZE     (0x08)

static const uint8_t _hidReportDescriptor[] PROGMEM = {
    0x06, 0x00, 0xFF,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xA1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, REPORT_SIZE,             //   REPORT_SIZE (8)
    0x95, REPORT_SIZE,             //   REPORT_COUNT (8)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xB2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xC0                           // END_COLLECTION
};

HIDRelay_::HIDRelay_(void):
	_relays(0)
{
	static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
	HID().AppendDescriptor(&node);
}

void HIDRelay_::begin(void)
{
}

void HIDRelay_::end(void)
{
}

unsigned int HIDRelay_::poll(void)
{
	unsigned int relays = this->_relays;
	if (USB_Available(HID_RX) > 0) {
		uint8_t id;
		uint8_t report[8];
		USB_Recv(HID_RX, &id, sizeof(id));
		USB_Recv(HID_RX, report, sizeof(report));
		switch (report[0]) {
		case CMD_ALL_ON:
			relays = ~0u;
			break;
		case CMD_ALL_OFF:
			relays = 0u;
			break;
		case CMD_ON:
			relays = relays | (1u << report[1]);
			break;
		case CMD_OFF:
			relays = relays & ~(1u << report[1]);
			break;
		case CMD_SET_SERIAL:
			break;
		}
		this->_relays = relays;
	}
	return relays;
}

HIDRelay_ HIDRelay;

#endif

