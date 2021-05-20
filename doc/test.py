#coding=utf-8
import cv2
import os
import threading
from PIL import ImageTk
import glob as gb
from PIL import Image, ImageDraw
import matplotlib.pyplot as plt
import PIL
import time
import numpy as np
from tkinter import *
from tkinter import ttk
from tkinter import filedialog
majhong_card=[
    0.07679912603595122,#1m
    0.25425848412274993,  # 2m
    0.15332400645267413,#3m
    1.154129585225993,#4m
    0.8784323264602181,#5m
    0.7823518300019805,#6m
    0.636489537567171,#7m
    0.7218712833213605,#8m
    0.620235217309573,#9m
    0.17839187642455834,#1p
    0.17252139265752264,#2p
    1.4547654672911814,#3p
    1.0571839184900955,#4p
    0.8233857885266119,#5p
    0.7382587097886307,#6p
    0.7733703150062248,#7p
    0.6950453795563498,#8p
    0.5964907998141747,#9p
    0.0019272203102393111,#1s
    0.16233055465664528,#2s
    1.2946866108399782,#3s
    0.9782296430236469,#4s
    0.7589633506129907,#5s
    0.6842594663068071,#6s
    0.7626039967175585,#7s
    0.6656529164285019,#8s
    0.5726563726567631,#9s
    0.48401596697609084,#dong
    0.4791585543527155,#nan
    0.39018317439249356,#xi
    0.5001939424807404,#bei
    0.3558422879142452,#zhong
    0.5475388129307024,#bai
    0.44524662849691593,]#fa
mahjong=['1m','2m','3m','4m','5m','6m','7m','8m','9m',
         '1p','2p','3p','4p','5p','6p','7p','8p','9p',
         '1s','2s','3s','4s','5s','6s','7s','8s','9s',
         '1z','2z','3z','4z','5z','6z','7z']
mahjong_re=[[0 for x in range(34)] for y in range(4)]
mahjong_ju=[[0 for x in range(15)] for y in range(34)]
mahjong_path='.\pic\*.png'
card_width=60
card_height=100
threshold = 170
table = []
for i in range(256):
    if i < threshold:
        table.append(0)
    else:
        table.append(1)
def card_find(img_card,plot_x,plot_y):
    list=[0 for x in range(15)]
    img_card = img_card.convert('L')
    # img_card = img_card.point(table, '1')
    for x_card in range(0, 3):
        for y_card in range(0, 5):
            for z_card in range(0, 100):
                if img_card.getpixel((plot_x+x_card * 10 + (z_card / 10), plot_y+y_card * 10 + (z_card % 10)))>threshold:
                    list[x_card*5+y_card]+=1
    return list
def mahjong_get():
    i=0
    sam=0#相似性
    sam_max=0
    dif_max=100
    dif=0
    # img_display = PIL.ImageGrab.grab()
    img_display = PIL.Image.open('test.jpg')
    width= img_display.width
    height= img_display.height
    print(width,height)
    for x in range(0,(int(width/30)-1)):
        for y in range(0,(int(height/50)-1)):
            card_org=card_find(img_display,x*30,y*50)
            if card_org.count(0)<5:
                print("这可能是是一张麻将牌")
                card_pro=img_display.crop((x*30,y*50,x*30+card_width,y*50+card_height))
                card_pro.save("test.png")
                i=0
                sam = 0  # 相似性
                sam_max = 0
                dif_max = 100
                dif = 0
                print(card_org)
                print(x*30,y*50)
                check_path=os.path.abspath(mahjong_path)
                img_path = gb.glob(check_path)
                for check_path in img_path:
                    img_card = PIL.Image.open(check_path)
                    mahjong_ju[i]=card_find(img_card,0,0)
                    for x in range(0, 15):
                        if abs((mahjong_ju[i][x]-card_org[x]))<=3:
                            sam+=1
                        elif abs((mahjong_ju[i][x] - card_org[x])) >10:
                            dif+=(abs((mahjong_ju[i][x] - card_org[x]))/10)
                    if sam>dif:
                        sam=sam-dif
                    else:
                        sam=0
                    if (sam>sam_max or (sam==sam_max and dif<dif_max)) and sam!=0:
                        sam_max=sam
                        dif_max=dif
                        print(check_path)
                        print(sam)
                    sam=0
                    dif=0
                    i += 1
                if sam_max!=0:
                    print(sam_max)
                    PIL.ImageDraw.Draw(img_display).rectangle((x*30,y*50,x*30+card_width,y*50+card_height), outline='black', width=3)
                    img_display.show()

def mahjong_analysis():
    pass

def threading_all():#程序线程
    try:
        mythread1 = threading.Thread(target=mahjong_get)
        mythread2 = threading.Thread(target=mahjong_analysis)
        mythread1.start()
        mythread2.start()
    except:
        print ("Error: 无法启动线程")

threading_all()
