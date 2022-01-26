f = open("puzzles/medium_3.txt", "r")
a = f.read()
f.close()

f = open("puzzles/medium_3.txt", "w")
b = " ".join(a)
f.write(b)

print(b)