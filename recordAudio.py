#!/usr/bin/env python3
import pyaudio
import numpy as np
import rospy
from std_msgs.msg import Float64MultiArray

# sample = np.zeros([4, CHUNK])
accel_data = Float64MultiArray()
accel_data.data = []

# publisher
def talker():
    
    # global sample

    FORMAT = pyaudio.paInt16
    CHANNELS = 4
    RATE = 8000
    CHUNK = 50
    sample = np.zeros([4, CHUNK])
    RECORD_SECONDS = 5
    
    audio = pyaudio.PyAudio()
        
    stream = audio.open(format=FORMAT, channels=CHANNELS,
            rate=RATE, input=True,
            frames_per_buffer=CHUNK,input_device_index=7)
    print("recording...")
    frames = []
        
    data = stream.read(CHUNK)
    
    while not rospy.is_shutdown():
        
        
        for i in range (CHUNK):
            for j in range(4):
                
                sample[j,i]=int.from_bytes([data[j*2+i*8],data[j*2+i*8+1]], "little", signed=True)
                
        sample = sample/32768
        #print(sample)
        for i in range(4):
            accel_data.data.insert(i, sample[:,i]) 
            
        pub.publish(accel_data)
        accel_data.data[:] = []
        rate.sleep()
        
    stream.stop_stream()
    stream.close()
    audio.terminate()

if __name__ == '__main__':
    
    rospy.init_node('talker', anonymous=True)
    pub = rospy.Publisher('accel_data', Float64MultiArray, queue_size =100)
    rate = rospy.Rate(4000) #10hz

    try:
        talker()
    except rospy.ROSInterruptException:
        pass
    rospy.spin()
    
    # stop Recording
    