import os

ips = []

for i in range(0, 256):
    ip = "169.254.247.{}".format(i)
    command = "ping -c 2 -W 1 -i 0.5 {}".format(ip)
    print(command)
    response = os.system(command)
    if response == 0:
        ips.append(ip)
        print('{} is up!'.format(ip))
    # else:
        # print('{} is down!'.format(ip))

print()
print()
print()
print()
print()
print()

[ print(ip) for ip in ips ]