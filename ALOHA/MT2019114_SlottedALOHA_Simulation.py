# SRAVYA M (MT2019114)
# Slotted Aloha Simulation
import numpy as np
import math
import matplotlib.pyplot as plt
import random

my_lambda=[]
throughput=[]

# Calculating times of packet generation and throughput
for load in np.arange(0.1,3.5,0.1):
    my_time_list=[]
    t=0
    while t<=10000:
        x=random.random()
        if x==0:
            x=random.random()
        t=t-(math.log(x)/load)

        my_time_list.append(t)

    success=0
    for i in range(1,len(my_time_list)-1):
        p2=my_time_list[i]
        p1=my_time_list[i-1]
        if ((p2-p1)>1):
            success=success+1

    # Throughput
    throughput.append(success/10000)
    my_lambda.append(load)

# graph of Load (Lambda) versus Throughput
plt.plot(my_lambda,throughput,marker='o', markerfacecolor='blue', markersize=12)
plt.xlabel("Load")
plt.ylabel("Throughput")
plt.show()
