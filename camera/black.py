import sensor, lcd, time
sensor.reset()
sensor.set_pixformat(sensor.RGB565) 
sensor.set_framesize(sensor.QVGA)    
sensor.skip_frames(time=2000)        
lcd.init()

threshold_black = (0, 10) 

while True:
    img = sensor.snapshot()  
    blobs = img.find_blobs([threshold_black], pixels_threshold=200, area_threshold=200)
    for blob in blobs:
        if 0.8 < blob.w() / blob.h() < 1.2: 
            img.draw_circle(blob.cx(), blob.cy(), blob.w()//2, color=(255, 0, 0))  
            print("黒のボール発見！ 座標:", blob.cx(), blob.cy())
            break  
    lcd.display(img)
