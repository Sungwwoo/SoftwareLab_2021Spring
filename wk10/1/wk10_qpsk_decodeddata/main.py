import matplotlib.pyplot as plt

content = []
with open("decoded_0.txt", "r") as fileRead:
    for line in fileRead:
        content.append(line.strip("\n").split(" "))

x, y = [], []
for i in range(0, len(content)):
    for j in range(100, 10000):
        x.append(float(content[i][2 * j]))
        y.append(float(content[i][2 * j + 1]))
print(len(content), len(content[0]))
plt.title("QPSK, SNR = 0dB")
plt.axhline(y=0, color="k", lw=0.4)
plt.axvline(x=0, color="k", lw=0.4)
plt.xlim((-2,2))
plt.ylim((-2,2))
plt.grid(True, ls = ":", alpha=.4)
plt.scatter(x, y, s=1, color="b")
plt.savefig("snr_0.png")
