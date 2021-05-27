import matplotlib.pyplot as plt

content1 = []
with open("error_QPSK.txt", "r") as fileRead:
    for line in fileRead:
        content1.append(line.strip("\n").split(" "))

x1, y1 = [], []
for i in range(0, len(content1)):
    for j in range(0, len(content1[i])):
        x1.append(float(content1[i][0]))
        y1.append(float(content1[i][1]))
content2 = []
with open("error_16QAM.txt", "r") as fileRead:
    for line in fileRead:
        content2.append(line.strip("\n").split(" "))

x2, y2 = [], []
for i in range(0, len(content2)):
    for j in range(0, len(content2[i])):
        x2.append(float(content2[i][0]))
        y2.append(float(content2[i][1]))
plt.figure(figsize=(10,7))
plt.axhline(y=0, color="k", lw=0.4)
plt.axvline(x=0, color="k", lw=0.4)
plt.grid(True, ls = ":", alpha=.4)
plt.plot(x1, y1, "b", lw="0.7", marker="o", markersize="3", alpha=0.4, label="QPSK")
plt.plot(x2, y2, "r", lw="0.7", marker="x", markersize="3", alpha=0.7, label="16QAM")
plt.legend()
plt.semilogy()
plt.semilogx()
plt.ylim((1e-6, 1))
plt.xlim((1, 30))
plt.title("Symbol Error Rate")
plt.xlabel("${E_s}/ {N_o}$ (dB)")
plt.ylabel("BER (logscale)")
plt.savefig("fig.png")
