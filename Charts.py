import matplotlib.pyplot as plt

RANDOM_TAG = "_r"

time_e1 = []
time_e2 = []
time_e3 = []
size_e = []

pathOfFile1 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/veb_ir" + RANDOM_TAG + ".time"
pathOfFile2 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/os_ir" + RANDOM_TAG + ".time"
pathOfFile3 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/us_ir" + RANDOM_TAG + ".time"
file1 = open(pathOfFile1, 'r')
file2 = open(pathOfFile2, 'r')
file3 = open(pathOfFile3, 'r')
stringsOfFiles1 = file1.readlines()
stringsOfFiles2 = file2.readlines()
stringsOfFiles3 = file3.readlines()
for strOfFile in range(0, len(stringsOfFiles1)):
    uSize = pow(2, strOfFile + 2)
    time = 0
    j = 0
    for i in stringsOfFiles1[strOfFile].split():
        if j % (uSize * 2) < uSize:
            time += int(i)
        j += 1
    time_e1.append(time / 1000000)
    time = 0
    j = 0
    for i in stringsOfFiles2[strOfFile].split():
        if j % (uSize * 2) < uSize:
            time += int(i)
        j += 1
    time_e2.append(time / 1000000)
    time = 0
    j = 0
    for i in stringsOfFiles3[strOfFile].split():
        if j % (uSize * 2) < uSize:
            time += int(i)
        j += 1
    time_e3.append(time / 1000000)
    size_e.append(strOfFile + 2)
file1.close()
file2.close()

plt.xlabel("k, где 2^k = universeSize")
plt.ylabel("Время работы (ns)")
plt.xlim([1, 22])
plt.locator_params(axis='x', nbins=40)
plt.plot(size_e, time_e1, label='vEB дерево', color="blue", marker="o")
plt.plot(size_e, time_e2, label='ordered set', color="red", marker="o")
plt.plot(size_e, time_e3, label='unordered set', color="gray", marker="o")
plt.title("Операция Insert")
plt.legend()
plt.savefig("C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Images/Charts/Insert" + RANDOM_TAG + ".png")
plt.show()

time_e1 = []
time_e2 = []
time_e3 = []
size_e = []

pathOfFile1 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/veb_ir" + RANDOM_TAG + ".time"
pathOfFile2 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/os_ir" + RANDOM_TAG + ".time"
pathOfFile3 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/us_ir" + RANDOM_TAG + ".time"
file1 = open(pathOfFile1, 'r')
file2 = open(pathOfFile2, 'r')
file3 = open(pathOfFile3, 'r')
stringsOfFiles1 = file1.readlines()
stringsOfFiles2 = file2.readlines()
stringsOfFiles3 = file3.readlines()
for strOfFile in range(0, len(stringsOfFiles1)):
    uSize = pow(2, strOfFile + 2)
    time = 0
    j = 0
    for i in stringsOfFiles1[strOfFile].split():
        if j % (uSize * 2) >= uSize:
            time += int(i)
        j += 1
    time_e1.append(time / 1000000)
    time = 0
    j = 0
    for i in stringsOfFiles2[strOfFile].split():
        if j % (uSize * 2) >= uSize:
            time += int(i)
        j += 1
    time_e2.append(time / 1000000)
    time = 0
    j = 0
    for i in stringsOfFiles3[strOfFile].split():
        if j % (uSize * 2) >= uSize:
            time += int(i)
        j += 1
    time_e3.append(time / 1000000)
    size_e.append(strOfFile + 2)
file1.close()
file2.close()

plt.xlabel("k, где 2^k = universeSize")
plt.ylabel("Время работы (ns)")
plt.xlim([1, 22])
plt.locator_params(axis='x', nbins=40)
plt.plot(size_e, time_e1, label='vEB дерево', color="blue", marker="o")
plt.plot(size_e, time_e2, label='ordered set', color="red", marker="o")
plt.plot(size_e, time_e3, label='unordered set', color="gray", marker="o")
plt.title("Операция Remove")
plt.legend()
plt.savefig("C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Images/Charts/Remove" + RANDOM_TAG + ".png")
plt.show()

time_e1 = []
time_e2 = []
time_e3 = []
size_e = []

pathOfFile1 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/veb_f" + RANDOM_TAG + ".time"
pathOfFile2 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/os_f" + RANDOM_TAG + ".time"
pathOfFile3 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/us_f" + RANDOM_TAG + ".time"
file1 = open(pathOfFile1, 'r')
file2 = open(pathOfFile2, 'r')
file3 = open(pathOfFile3, 'r')
stringsOfFiles1 = file1.readlines()
stringsOfFiles2 = file2.readlines()
stringsOfFiles3 = file3.readlines()
for strOfFile in range(0, len(stringsOfFiles1)):
    time = 0
    for i in stringsOfFiles1[strOfFile].split():
        time += int(i)
    time_e1.append(time / 1000000)
    time = 0
    for i in stringsOfFiles2[strOfFile].split():
        time += int(i)
    time_e2.append(time / 1000000)
    time = 0
    for i in stringsOfFiles3[strOfFile].split():
        time += int(i)
    time_e3.append(time / 1000000)
    size_e.append(strOfFile + 2)
file1.close()
file2.close()
file3.close()

plt.xlabel("k, где 2^k = universeSize")
plt.ylabel("Время работы (ns)")
plt.xlim([1, 22])
plt.locator_params(axis='x', nbins=40)
plt.plot(size_e, time_e1, label='vEB дерево', color="blue", marker="o")
plt.plot(size_e, time_e2, label='ordered set', color="red", marker="o")
plt.plot(size_e, time_e3, label='unordered set', color="gray", marker="o")
plt.title("Операция Find")
plt.legend()
plt.savefig("C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Images/Charts/Find" + RANDOM_TAG + ".png")
plt.show()

time_e1 = []
time_e2 = []
size_e = []

pathOfFile1 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/veb_s" + RANDOM_TAG + ".time"
pathOfFile2 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/os_s" + RANDOM_TAG + ".time"
file1 = open(pathOfFile1, 'r')
file2 = open(pathOfFile2, 'r')
stringsOfFiles1 = file1.readlines()
stringsOfFiles2 = file2.readlines()
for strOfFile in range(0, len(stringsOfFiles1)):
    time = 0
    for i in stringsOfFiles1[strOfFile].split():
        time += int(i)
    time_e1.append(time / 1000000)
    time = 0
    for i in stringsOfFiles2[strOfFile].split():
        time += int(i)
    time_e2.append(time / 1000000)
    size_e.append(strOfFile + 2)
file1.close()
file2.close()

plt.xlabel("k, где 2^k = universeSize")
plt.ylabel("Время работы (ns)")
plt.xlim([1, 22])
plt.locator_params(axis='x', nbins=40)
plt.plot(size_e, time_e1, label='vEB дерево', color="blue", marker="o")
plt.plot(size_e, time_e2, label='ordered set', color="red", marker="o")
plt.title("Операция Successor")
plt.legend()
plt.savefig("C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Images/Charts/Successor.png")
plt.show()

time_e1 = []
time_e2 = []
size_e = []

pathOfFile1 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/veb_p" + RANDOM_TAG + ".time"
pathOfFile2 = "C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Generated tests/os_p" + RANDOM_TAG + ".time"
file1 = open(pathOfFile1, 'r')
file2 = open(pathOfFile2, 'r')
stringsOfFiles1 = file1.readlines()
stringsOfFiles2 = file2.readlines()
for strOfFile in range(0, len(stringsOfFiles1)):
    time = 0
    for i in stringsOfFiles1[strOfFile].split():
        time += int(i)
    time_e1.append(time / 1000000)
    time = 0
    for i in stringsOfFiles2[strOfFile].split():
        time += int(i)
    time_e2.append(time / 1000000)
    size_e.append(strOfFile + 2)
file1.close()
file2.close()

plt.xlabel("k, где 2^k = universeSize")
plt.ylabel("Время работы (ns)")
plt.xlim([1, 22])
plt.locator_params(axis='x', nbins=40)
plt.plot(size_e, time_e1, label='vEB дерево', color="blue", marker="o")
plt.plot(size_e, time_e2, label='ordered set', color="red", marker="o")
plt.title("Операция Predecessor")
plt.legend()
plt.savefig("C:/Users/Roman/CLionProjects/Van EmdeBoas tree/Images/Charts/Predecessor.png")
plt.show()