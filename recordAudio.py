#!/usr/bin/env python3
import pyaudio
import numpy as np
import rospy
from std_msgs.msg import Float64MultiArray, MultiArrayDimension

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
            
    while not rospy.is_shutdown():
        
        data = stream.read(CHUNK)
        
        # read data from stream
        for i in range (CHUNK):
            for j in range(4):
                
                sample[j,i]=int.from_bytes([data[j*2+i*8],data[j*2+i*8+1]], "little", signed=True)
                sample[j,i] = sample[j,i]/32768 
                accel_data.data.insert(j, sample[j,i].astype('float64'))
                
        # sample = sample/32768         
        
        #print(sample)
        # for k in range(4):
        #     accel_data.data.insert(k, sample[k,:].astype('float64')) 
            
        pub.publish(accel_data)
        
        accel_data.data[:] = []
        sample = np.zeros([4, CHUNK])
        rate.sleep()
        
    # stop Recording
    stream.stop_stream()
    stream.close()
    audio.terminate()

if __name__ == '__main__':
    
    rospy.init_node('talker', anonymous=True)
    pub = rospy.Publisher('accel_data', Float64MultiArray, queue_size =1000)
    rate = rospy.Rate(8000) #10hz

    try:
        talker()
    except rospy.ROSInterruptException:
        pass
    rospy.spin()
    
    