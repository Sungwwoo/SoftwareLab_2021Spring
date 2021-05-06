import matplotlib.pyplot as plt

content = []
with open("decoded_20.txt", "r") as fileRead:
    for line in fileRead:
        content.append(line.strip("\n").split(" "))

x, y = [], []
for i in range(0, len(content)):
    for j in range(100, 10000):
        x.append(float(content[i][2 * j]))
        y.append(float(content[i][2 * j + 1]))

plt.title("16QAM, SNR = 20dB")
plt.xlim((-4,4))
plt.ylim((-4,4))
plt.axhline(y=0, color="k", lw=0.4)
plt.axvline(x=0, color="k", lw=0.4)
plt.grid(True, ls = ":", alpha=.4)
plt.scatter(x, y, s=1, color="b")
plt.savefig("snr_20.png")
