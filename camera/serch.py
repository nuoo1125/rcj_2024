import sensor, image, lcd, time

# カメラとLCDの初期化
lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)  # グレースケールモードに設定
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)  # 自動ゲインをオフにする
sensor.set_auto_whitebal(False)  # 自動ホワイトバランスをオフにする

# グレースケールしきい値の設定
threshold = (180, 255)  # 銀色のボールを認識するための輝度範囲

# メインループ
while(True):
    img = sensor.snapshot()  # カメラ画像をキャプチャ

    # しきい値に基づいてバイナリイメージを作成
    binary_img = img.binary([threshold])

    # 輪郭を探す
    blobs = binary_img.find_blobs([threshold], pixels_threshold=200, area_threshold=200, merge=True)

    # 検出された領域を描画
    for blob in blobs:
        # バウンディングボックスを描画
        img.draw_rectangle(blob.rect(), color=127)  # グレースケールなので127(中間色)で描画
        # 中心点を描画
        img.draw_cross(blob.cx(), blob.cy(), color=127)
        print("Blob detected: x={}, y={}, w={}, h={}".format(blob.x(), blob.y(), blob.w(), blob.h()))

    # 画像をLCDに表示
    lcd.display(img)

