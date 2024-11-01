import sensor, image, time, lcd

# LCDの初期化
lcd.init(freq=15000000)
lcd.rotation(2)  # 必要に応じて調整してください

# カメラの設定
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)

clock = time.clock()

while True:
    clock.tick()
    img = sensor.snapshot()

    # 赤色三角形の検出
    red_threshold = (30, 100, 30, 127, 127, 255)
    for blob in img.find_blobs([red_threshold], merge=True):
        if blob.roundness() < 0.7:  # 三角形と認識
            img.draw_rectangle(blob.rect(), color=(255, 0, 0))
            img.draw_string(blob.x(), blob.y(), "Red Triangle", color=(255, 0, 0))

    # 緑色三角形の検出
    green_threshold = (30, 100, -64, -8, -32, 32)
    for blob in img.find_blobs([green_threshold], merge=True):
        if blob.roundness() < 0.7:  # 三角形と認識
            img.draw_rectangle(blob.rect(), color=(0, 255, 0))
            img.draw_string(blob.x(), blob.y(), "Green Triangle", color=(0, 255, 0))

    # 銀色テープの検出
    silver_threshold = (0, 100, -20, 20, 20, 127)
    for blob in img.find_blobs([silver_threshold], merge=True):
        if blob.roundness() > 0.7:
            img.draw_rectangle(blob.rect(), color=(192, 192, 192))
            img.draw_string(blob.x(), blob.y(), "Silver Tape", color=(192, 192, 192))

    # 黒色テープの検出
    black_threshold = (0, 30, -20, 20, -20, 20)
    for blob in img.find_blobs([black_threshold], merge=True):
        if blob.roundness() > 0.7:
            img.draw_rectangle(blob.rect(), color=(0, 0, 0))
            img.draw_string(blob.x(), blob.y(), "Black Tape", color=(0, 0, 0))

    # 銀色の球の検出
    for blob in img.find_blobs([silver_threshold], merge=True, margin=10):
        if blob.roundness() > 0.85:
            img.draw_circle(blob.cx(), blob.cy(), int(blob.w()/2), color=(192, 192, 192))
            img.draw_string(blob.cx(), blob.cy(), "Silver Ball", color=(192, 192, 192))

    # 黒色の球の検出
    for blob in img.find_blobs([black_threshold], merge=True, margin=10):
        if blob.roundness() > 0.85:
            img.draw_circle(blob.cx(), blob.cy(), int(blob.w()/2), color=(0, 0, 0))
            img.draw_string(blob.cx(), blob.cy(), "Black Ball", color=(0, 0, 0))

    # LCDに画像を表示
    lcd.display(img)

    print("FPS:", clock.fps())
