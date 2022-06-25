from dis import dis
import serial
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import threading
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from rplidar import RPLidar

PORT_NAME = "/dev/cu.usbserial-0001"
lidar = RPLidar(PORT_NAME)

length = 360*2

scanX = [0] * length
scanY = [0] * length

arduino = serial.Serial(port='/dev/cu.usbmodem11101', baudrate=115200, timeout=.1)

decision = '1'

try:
    def fetchData():

        global scanX
        global scanY
        global lidar
        global decision

        for scan in lidar.iter_scans():

            obstruction = 1e99
            ang = 370

            for (_, angle, distance) in scan:

                if (angle <= 45 or angle >= 315):

                    #print("single:", angle, distance, obstruction)

                    if (distance <= obstruction):

                        obstruction = distance
                        ang = angle
                
                    angle_value = float(angle) * 0.0174533

                    ox = distance * np.sin(angle_value)
                    oy = distance * np.cos(angle_value)

                    scanX.append(ox)
                    scanY.append(oy)

                    scanX = scanX[-length:]
                    scanY = scanY[-length:]

            #print("final:", ang, obstruction)

            if (obstruction <= 500):
                decision = '5'
            elif (obstruction >= 500 and obstruction <= 1000):
                if (ang <= 45):
                    decision = '2'
                else:
                    decision = '3'
            else:
                decision = '1'

            #print("decision:", decision)

    def writeToArd ():
        global decision
        try:
            while True:
                #print("writting to arduino",decision)
                arduino.write(bytes(decision, 'utf-8'))
                data = arduino.readline()
                print(data)
        finally:
            arduino.close()

    firstThread = threading.Thread(target=fetchData)
    firstThread.start()

    if not arduino.isOpen():
        arduino.open()

    dataThread = threading.Thread(target=writeToArd)
    dataThread.start()

    fig = plt.figure()

    radius = 500
    ax = fig.add_subplot(1, 1, 1)
    

    def animate(i):
        global scanX
        global scanY
        ax.clear()
        ax.plot(scanX, scanY, "bo")
        for i in range (360):
            ax.plot(radius * np.cos(np.radians(i)), radius * np.sin(np.radians(i)), "ro")

    ani = animation.FuncAnimation(fig, animate, fargs = (), interval = 1)
    plt.show()

finally:
    lidar.stop()
    lidar.disconnect()
    firstThread.join()
    dataThread.join()
