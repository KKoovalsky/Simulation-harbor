#!/usr/bin/env python
# -*- coding:utf-8 -*-
#------------------------------------------------
# IMPORT LIBRARIES:
#------------------------------------------------
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import numpy as np
#------------------------------------------------
# PLOT OPTIONS:
#------------------------------------------------
marker_set = ['o', 'D', '+', '3', 's', '*', 'd', 'v', '<', '>', '^', '|']
colors_set = ['r', 'b', 'g', 'm', 'y', 'k']
drawstyle_set = ['-', '--', '-.', ':']

marker_idx=0
color_idx=0
drawstyle_idx=0

labels_size = 12
marker_size = 2
line_width = 1.0
#------------------------------------------------
# Simple Moving Average:
#------------------------------------------------
def SMA(x, ws):
    
    y = [np.sum(x[:n])/n for n in range(1, ws)]

    y += [np.sum(x[n:(n+ws)])/ws for n in range(len(x) - ws)]

    return y
#------------------------------------------------
# SET PARAMETERS:
#------------------------------------------------
L = 4
L_SPAN = 1

M = 10

plot_realizations = True

plot_average = True

plot_moving_average = True

window_size = 40

file_path = '../output/'
figure_idx = 1
#------------------------------------------------
# SET FIGURE:
#------------------------------------------------
plt.figure(figure_idx)
plt.subplots_adjust(wspace=0.1, left=0.09, right=0.975, bottom=0.075, top=0.95)
plt.subplot(111)
#------------------------------------------------
# PLOT DATA:
#------------------------------------------------
for l in range(L, L+L_SPAN, 1):
    
    data_set = []
    
    for m in range(0, M):
        
        data = mlab.csv2rec(file_path + 'client_stats_' + str(l) + '_' + str(m) + '.csv', delimiter=';')
    
        if plot_realizations:
            plt.plot(range(len(data.service_duration)), data.service_duration, color=colors_set[color_idx+1], linestyle='-', linewidth=line_width-1, marker=marker_set[marker_idx], markersize=marker_size, label='L:'+ str(l) + ' m:' + str(m))
            marker_idx = (marker_idx+1) % len(marker_set)

        # Remember smallest length of data vector
        if m == 0:
            smallest_data_length = len(data.service_duration)
        else:
            smallest_data_length = min(smallest_data_length, len(data.service_duration))
        
        print "smallest_data_length:" + str(smallest_data_length)
        
        data_set.append(data.service_duration)
        
    # Calculate average value over M realizations
    for m in range(0, M):
        if m == 0:
            ave_data = data_set[m][:smallest_data_length]
        else:
            ave_data += data_set[m][:smallest_data_length]
    ave_data /= M
    
    if plot_average:
        plt.plot(range(len(ave_data)), ave_data, color=colors_set[color_idx], linestyle='--', linewidth=line_width, marker=marker_set[marker_idx], markersize=marker_size, label='AVE L:'+ str(l) + ' M:' + str(M))    
    
    # Moving average
    value = SMA(ave_data, window_size)
    point = range(len(value))

    if plot_moving_average:
        plt.plot(point, value, color=colors_set[color_idx], linestyle='-', linewidth=line_width+2, marker=marker_set[marker_idx], markersize=marker_size, label='MOV AVE L:'+ str(l) + ' M:' + str(M))
        
        if color_idx == len(colors_set)-1:
            marker_idx = (marker_idx+1) % len(marker_set)
        
    color_idx = (color_idx+1) % len(colors_set)
    
#================================================
plt.title('Service duration', fontsize=labels_size)
plt.xlabel('Process sample', fontsize=labels_size)
plt.ylabel('Mean wait time', fontsize=labels_size)
#------------------------------------------------
fig = plt.gcf()
fig.set_size_inches(14, 8)
#------------------------------------------------
if len(plt.legend().get_texts()) > 2:
    ax = plt.gca()
    box = ax.get_position()
    ax.set_position([box.x0, box.y0, box.width * 0.7, box.height])
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5))
else:
    plt.legend(loc=1)
#================================================
plt.savefig(file_path + 'clients.png', bbox_inches='tight', dpi=96)
plt.show()

'''
#------------------------------------------------
# Weighted Moving Average:
#------------------------------------------------

def WMA(x, w, ws):
    
    Y = [np.sum(np.multiply(x[:n], w[:n])) for n in range(1, ws)]
    
    Y += [np.sum(np.multiply(x[n:(n+ws)], w[n:(n+ws)])) for n in range(len(x))]
    
    W = [np.sum(w[:n]) for n in range(1, ws)]
    
    W += [np.sum(w[n:(n+ws)]) for n in range(len(w))]
    
    return np.divide(Y, W)
'''
