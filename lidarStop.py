import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import threading
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from rplidar import RPLidar

PORT_NAME = "/dev/cu.usbserial-0001"
lidar = RPLidar(PORT_NAME)

length = 360*4

scanX = [0] * length
scanY = [0] * length

try:
    def fetchData():
        global scanX
        global scanY
        global lidar
        for scan in lidar.iter_scans():
            for (_, angle, distance) in scan:
                if (distance <= 500):
                    print("STOP!!!")
                else:
                    print("MOVE!!!")
                angle_value = float(angle) * 0.0174533
                ox = distance * np.sin(angle_value)
                oy = distance * np.cos(angle_value)
                scanX.append(ox)
                scanY.append(oy)
                scanX = scanX[-length:]
                scanY = scanY[-length:]
    firstThread = threading.Thread(target=fetchData)
    firstThread.start()
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


