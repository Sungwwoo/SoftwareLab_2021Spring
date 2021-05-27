import matplotlib.pyplot as plt
import numpy as np

content1 = []
with open("sended.txt", "r") as fileRead:
    for line in fileRead:
        content1.append(line.strip("\n").split(" "))

y1 = []
for i in range(0, len(content1)):
    for j in range(0, len(content1[i]) // 2):
        y1.append(float(content1[i][2 * j]))
        y1.append(float(content1[i][2 * j + 1]))

content2 = []
with open("received.txt", "r") as fileRead:
    for line in fileRead:
        content2.append(line.split(" "))

y2 = []
for i in range(0, len(content2)):
    for j in range(0, len(content2[i]) // 2):
        y2.append(float(content2[i][2 * j]))
        y2.append(float(content2[i][2 * j + 1]))

x = range(0, len(y1))
plt.figure(figsize=(10,7))
plt.title("16QAM, SNR = 10dB")
plt.ylabel("Amplitude")
plt.axhline(y=0, color="k", lw="0.4")
plt.grid(True, ls = ":", alpha=.4)
plt.xlim((100, 500))
plt.plot(x, y1, "k", lw="0.9", alpha=0.7, label="sended")
plt.plot(x, y2, "r", lw="0.9", alpha=0.7, label="received")
plt.legend(loc="upper right")
plt.savefig("fig.png")
