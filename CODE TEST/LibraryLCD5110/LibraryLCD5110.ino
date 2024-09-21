#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>


Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 8);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!


static const unsigned char PROGMEM trun[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00001100, B01100000,
  B00011110, B11110000,
  B00011111, B11110000,
  B00011111, B11110000,
  B00001111, B11100000,
  B00000111, B11000000,
  B00000011, B10000000,
  B00000001, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000 };
static const unsigned char PROGMEM viettel[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000001, B00000000,
  B00000101, B00000000,
  B00010101, B00000000,
  B01010101, B00000000,
  B01010101, B00000000,
  B01010101, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000 };


void setup()   {
  Serial.begin(9600);
  display.begin();// KHỞI TẠO
  display.clearDisplay();
  display.setContrast(50); // ĐỘ TƯƠNG PHẢN
  // logo();
  // delay(500);
  display.clearDisplay();
     //display.invertDisplay(true); // đảo ngược màn hình?

}
void logo(){
      display.drawBitmap(5, 5,  trun, 16, 16, 1); // vẽ logo
      display.display();
 
}
int i=0,h,w;
void loop(){
  w= display.width();   //lấy chiều rộng
  h= display.height();  //lấy chiều cao màn hình
  display.clearDisplay();     // xóa màn hình
  // display.fillRect(0, 0, 83, 47, BLACK); // vẽ nền đen
  // display.setRotation(1);     // xoay 90 độ, chọn 1,2,3
  display.setTextSize(1);     // đặt kích cỡ
  display.setTextColor(WHITE);//chọn màu chữ BLACK hoặc WHITE
  display.setCursor(28,1);     //chọn vị trí
 display.println("MENU");//in kí tự ra màn hình

  // display.setCursor(27,10);     //chọn vị trí
  // display.println(i);//in kí tự ra màn hình
  display.drawFastHLine(0,10,83,BLACK); // vẽ nhanh đường thẳng
  //Màn hình kích thước 84x48. Nhưng bắt đầu từ 0 nên 84-1 x 48-1 ~ 83x47
  // display.drawLine(0, 0, 83, 0, BLACK); //vẽ đường (x1,y1,x2,y2,BLACK). Trong tọa độ O(x,y): x- chiều rộng=83, y- chiều cao =47
  // display.drawLine(0, 0, 0, 47, BLACK);
  // display.drawLine(0, 47, 83, 47, BLACK);
  // display.drawLine(83, 0, 83, 47, BLACK);

  // display.drawLine(3, 3, 80, 3, WHITE); //vẽ đường (x1,y1,x2,y2,WHITE). Trong tọa độ O(x,y): x- chiều rộng=80, y- chiều cao =47
  // display.drawLine(3, 3, 3, 44, WHITE);
  // display.drawLine(3, 44, 80, 44, WHITE);
  // display.drawLine(80, 3, 80, 44, WHITE);

  // display.drawTriangle(display.width()/2, display.height()/2-i,
  //                    display.width()/2-i, display.height()/2+i,
  //                    display.width()/2+i, display.height()/2+i, WHITE); //Vẽ hình tam giác: tọa độ (đỉnh, đỉnh trái, đỉnh phải,WHITE);
  /*
  Hàm vẽ hình: display.draw + hình: Rect, Circle, Triangle (Vuông, tròn, tam giác)
  Đổ màu vào hình. display.fill+ hình.(Tọa độ):
  Hình vuông: lấy tọa độ đường chéo. (x1, y1, w, h, BLACK)
        //display.drawRect(65,20,4,4,BLACK);//(Tọa độ x,y, kích thước 4x4, BLACK);
  Hình tròn: lấy tọa độ tâm. và bán kính R. (x1, y1, R, BLACK)
  Hình tam giác: lấy tọa độ 3 đỉnh. (x1, y1, x2, y2, x3, y3, BLACK)
  
  */

   display.drawRoundRect(0, 0, 83, 47, 10, BLACK);// vẽ hình bo góc (tọa độ đầu, chiều rộng, chiều dài, bo góc,BLACK)
  // display.fillTriangle(display.width()/2, display.height()/2-i,
  //                    display.width()/2-i, display.height()/2+i,
  //                    display.width()/2+i, display.height()/2+i, WHITE);

  // display.fillRect(0, 0, 83, 23, 1); // vẽ nền đen
  //display.drawCircle(w/2, h/2, 40, BLACK); // Vẽ vòng tròn, với i là kích thước
  // display.setTextSize(2);
  // display.println("KMA UNIVERSITY");
  display.display();          //bắt buộc sau mỗi lần hiển thị
  i++;
  

  delay(200);

}


