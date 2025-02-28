import sys
import time
from ctypes import cast, POINTER, CDLL
CDLL("C:/Data/Software/Source/hidapi-win/x64/hidapi.dll")
import hid
from comtypes import CLSCTX_ALL, COMObject, COMError
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume, IAudioEndpointVolumeCallback

vendor_id     = 0x4D44
product_id    = 0x5244

usage_page    = 0xFF60
usage         = 0x61
report_length = 32

interfaces = []

def get_raw_hid_interfaces():
    global interfaces
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [i for i in device_interfaces if i['usage_page'] == usage_page and i['usage'] == usage]

    interfaces = []

    if len(raw_hid_interfaces) == 0:
        return

    for interface in raw_hid_interfaces:
        interfaces.append(hid.Device(path=interface['path']))

def send_volume(current_volume_percentage):
    if len(interfaces) == 0:
        # print("No device found")
        return
    request_data = [0x00] * (report_length + 1) # First byte is Report ID
    # [ command_id, channel_id, value_id, value_data ]
    request_data[1:5] = [0x07, 0, 0, current_volume_percentage]
    request_report = bytes(request_data)
    print(f"Sending data: {request_data}") # Debugging output
    print(f"Sending report: {request_report}") # Debugging output
    try:
        for interface in interfaces:
            interface.write(request_report)
    finally:
        for interface in interfaces:
            interface.close()

class VolumeChangeCallback(COMObject):
    _com_interfaces_ = [IAudioEndpointVolumeCallback]

    def OnNotify(self, pNotify):
        # Get the current volume level (0.0 to 1.0)
        current_volume = volume.GetMasterVolumeLevelScalar()
        # Convert to a percentage (0-100)
        current_volume_percentage = int(current_volume * 100)
        send_volume(current_volume_percentage)

while True:
    try:
        get_raw_hid_interfaces()
        if len(interfaces) == 0:
            time.sleep(5)
            continue
        # Get the default audio device
        devices = AudioUtilities.GetSpeakers()
        interface = devices.Activate(
            IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
        volume = cast(interface, POINTER(IAudioEndpointVolume))

        # Register the callback
        callback = VolumeChangeCallback()
        volume.RegisterControlChangeNotify(callback)

        print("Audio device found. Monitoring volume changes...")

        # Keep the script running to listen for volume changes
        try:
            while True:
                time.sleep(1)
        except KeyboardInterrupt:
            # Unregister the callback when exiting
            volume.UnregisterControlChangeNotify(callback)
            print("Callback unregistered and script terminated.")
            break
    except COMError:
        # print("No audio device found. Retrying in 5 seconds...")
        time.sleep(5)
    except Exception as e:
        print(f"Unexpected error: {e}")
        time.sleep(5)
