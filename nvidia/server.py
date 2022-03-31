import aditofpython as tof
import numpy as np
import socket
import cv2
import pickle
import socket
import struct

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('192.168.0.227', 8486))



system = tof.System()

cameras = []
status = system.getCameraList(cameras)
camera1 = cameras[0]
modes = []
status = camera1.getAvailableModes(modes)
types = []
status = camera1.getAvailableFrameTypes(types)
print("system.getAvailableFrameTypes()", status)
print(types)
status = camera1.initialize()
camDetails = tof.CameraDetails()
status = camera1.getDetails(camDetails)
status = camera1.setFrameType(types[1])
status = camera1.setMode(modes[0])
frame = tof.Frame()

while(1):
    status = camera1.requestFrame(frame)
    image = np.array(frame.getData(tof.FrameDataType.Depth), copy=False)
    print(image)
    data = pickle.dumps(image, 0)
    size = len(data)
    client_socket.sendall(struct.pack(">L", size) + data)

    if cv2.waitKey(1) == 27:
        break  # esc to quit

