import numpy as np
import matplotlib.pyplot as plt

Data = np.loadtxt("cpp/output/main_output.txt")
Data_x = Data[:, 0]
Data_y1 = Data[:, 1]
Data_y2 = Data[:, 2]
Data_y3 = Data[:, 3]
Data_y4 = Data[:, 4]

fig, axs = plt.subplots(4)

i = 9000
j = 10000

axs[0].plot(Data_x[i:j], Data_y1[i:j])
axs[0].text(1010, 0.1, '(a)')
axs[0].set_xticklabels([])

axs[1].plot(Data_x[i:j], Data_y2[i:j])
axs[1].text(1010, 0.15, '(b)')
axs[1].set_xticklabels([])

axs[2].plot(Data_x[i:j], Data_y3[i:j])
axs[2].text(1010, 0.15, '(c)')
axs[2].set_xticklabels([])

axs[3].plot(Data_x[i:j], Data_y4[i:j])
axs[3].text(1010, 0.15, '(d)')
plt.xlabel('t')

for ax in axs:
    ax.set_ylabel('f')

plt.show()