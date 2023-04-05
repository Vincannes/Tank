from ctypes import cdll

example = cdll.LoadLibrary("D:\\Desk\\python\\Tank\\cpp\\lib\\Debug\\TankLib.dll")

print(dir(example))

# result = example.add(1, 2)
# print(result) # Output: 3
