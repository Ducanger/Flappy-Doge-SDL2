#### Mục lục
1. [Giới thiệu](#introduction)
2. [Tính năng](#feature)
3. [Hướng dẫn chơi](#play)
4. [Cài đặt](#installation)

# Giới thiệu <a name="introduction"></a>

* Game được lấy cảm hứng từ chú chó [Kabosu](https://vi.wikipedia.org/wiki/Doge_(meme)) - một trong những meme hot nhất từ năm 2013 cho đến tận bây giờ và [Flappy Bird](https://vi.wikipedia.org/wiki/Flappy_Bird) - tựa game Việt nổi tiếng do Nguyễn Hà Đông phát triển vào năm 2013.
* Flappy Doge được viết bằng thư viện [SDL2](https://www.libsdl.org/download-2.0.php) và ngôn ngữ C++.

<p align="center">
<img width="640" height="480" alt="balltze" src="https://i.pinimg.com/originals/02/98/fa/0298fa4e7f8b0495169b2e964f06d7f2.jpg">
</p>

# Tính năng <a name="feature"></a>

**1. Gameplay**
* Xử lí va chạm giữa nhân vật và ống, mặt đất, viền trên cửa sổ.
* Mặt đất, nhân vật chuyển động giúp game chân thực hơn.
* Giới hạn FPS để có tương thích với mọi thiết bị (nếu không giới hạn thì khi chạy game trên máy cấu hình cao, hình ảnh sẽ bị render quá nhanh, gây ra hiện ứng "tua nhanh")

**2. TabPause**
* Bật/Tắt tiếng game.
* Giao diện Sáng/Tối (thay đổi ngay sau khi chọn).
* Xem điểm hiện tại, điểm cao nhất.
* Biểu tượng chơi tiếp.

**3. TabGameOver**
* Hiển thị huân chương tương ứng với số điểm (Gold > 50, Silver > 20, Honor <= 20).
* Xem điểm hiện tại, điểm cao nhất.
* Biểu tượng chơi tiếp.

# Hướng dẫn chơi <a name="play"></a>
* Click chuột/ phím SPACE/ phím UP để chơi.
* Nhấn phím ESC để tạm dừng.

# Cài đặt <a name="installation"></a>

Sau khi cài đặt [Mingw64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download), [SDL2](https://www.libsdl.org/download-2.0.php), [SDL_Image](https://www.libsdl.org/projects/SDL_image), [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf), và [SDL_Mixer](https://www.libsdl.org/projects/SDL_mixer), chạy file **.exe** tại đường dẫn ./x64/Debug.




