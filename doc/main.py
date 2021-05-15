card=[0]*7
data = open("./winddata14.txt", 'w+')
print("麻将数据文件\n", file=data)
sum=0
for card[0] in range(0,5):
    for card[1] in range(0, 5):
        for card[2] in range(0, 5):
            for card[3] in range(0, 5):
                for card[4] in range(0, 5):
                    for card[5] in range(0, 5):
                        for card[6] in range(0, 5):
                            for i in range(0,7):
                                sum=card[i]+sum
                            if sum==14:
                                string=str(card)
                                print(string, file=data)
                            sum=0
data.close()

