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
    blobs = binary_img.find_blobs([threshold], pixels_threshold=10, area_threshold=10, merge=True)

    # 複数の小さな点が集まっているところを囲む
    if len(blobs) > 0:
        # 複数のブロブを一つにまとめる
        # x, y, w, hをそれぞれ合計することで囲む範囲を決定
        min_x = min([blob.x() for blob in blobs])
        min_y = min([blob.y() for blob in blobs])
        max_x = max([blob.x() + blob.w() for blob in blobs])
        max_y = max([blob.y() + blob.h() for blob in blobs])

        # 集まっている領域を囲むバウンディングボックスを描画
        img.draw_rectangle((min_x, min_y, max_x - min_x, max_y - min_y), color=(255, 0, 0))  # 赤色で描画

        # 座標を表示
        print("Region detected: top-left=({}, {}), bottom-right=({}, {})".format(min_x, min_y, max_x, max_y))

    # 画像をLCDに表示
    lcd.display(img)
