filename = "test/small_2.txt"
f = open(filename, "r")
a = f.read()
f.close()

f = open(filename, "w")
b = " ".join(a)
f.write(b)

print(b)