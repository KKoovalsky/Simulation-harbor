#!/usr/bin/env python
# -*- coding:utf-8 -*-

import matplotlib.mlab as mlab
import matplotlib.pyplot as plt
import numpy as np

file_path = '../output/'
data = mlab.csv2rec( file_path + 'model_stats.csv', delimiter=';')

plt.figure()
plt.subplots_adjust(wspace=0.1, left=0.09, right=0.975, bottom=0.075, top=0.95)
plt.subplot(111)


plt.errorbar(data.intensity, data.mean_wait_time, yerr=data.delta, marker='s', markerfacecolor='red', markeredgecolor='green', markersize = 6, markeredgewidth = 2, label="Service time")
#plt.errorbar(data.lambda_1, data.est_mu_st, yerr=data.delta, label="Service time", fmt='-', ecolor=None, elinewidth=None, capsize=3, barsabove=False, lolims=False, uplims=False, xlolims=False, xuplims=False, errorevery=1, capthick=None)

plt.xlim(0.075, 0.105)
plt.ylim(0, max(data.mean_wait_time)*1.4)
plt.title('Mean wait time', fontsize=12)
plt.xlabel('Lambda', fontsize=12)
plt.ylabel('Mean', fontsize=12)

plt.legend(loc=2)
fig = plt.gcf()
fig.set_size_inches(10, 6)
plt.savefig( file_path + 'model_analysis.png', bbox_inches='tight', dpi=250)
plt.show()
