from rplidar import RPLidar
#import matplotlib.pyplot as plt
import numpy as np

PORT_NAME = "/dev/cu.usbserial-0001"
lidar = RPLidar(PORT_NAME)

ptr = open("lidarData.csv", 'w')
count = 0
tot = 360*4

try:
    for scan in lidar.iter_scans():
        for (_, angle, distance) in scan:
            curr = str(distance) + " " + str(angle) + '\n'
            ptr.write(curr)
            #plt.plot(distance*np.cos(np.radians(angle)), distance*np.sin(np.radians(angle)), marker="o")
            count += 1
            if (count > tot):
                lidar.stop()
                lidar.disconnect()
                break

except KeyboardInterrupt:
    print("Stopping...")

ptr.close()

lidar.stop()
lidar.disconnect()


#plt.show()
