import os

for i in range(1, 254):
    ip = "169.254.247.{}".format(i)
    response = os.system("ping -c 1 {}".format(ip))
    if response == 0:
        print('{} is up!'.format(ip))
    # else:
        # print('{} is down!'.format(ip))