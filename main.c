#include <16F887.h>
#use delay(clock=4000000)                             // 4Mhz
#byte portb = 0x6
#byte portc = 0x7
#byte portd = 0x8
#bit rs = portc.0 
#bit en = portc.1
#bit up1 = portb.2    // khai báo nút nh?n 1 v?i c?ng portb.2 ch?nh gi?
#bit up2 = portb.3    // khai báo nút nh?n 2 v?i c?ng portb. ch?nh phút
#bit up3 = portb.4    // khai báo nút nh?n 3 v?i c?ng portb. ch?nh ngày
#bit up4 = portb.5    // khai báo nút nh?n 4 v?i c?ng portb. ch?nh tháng
#bit up5 = portb.6    // khai báo nút nh?n 5 v?i c?ng portb. ch?nh n?m
#bit up6 = portb.7    // khai báo nút nh?n 6 v?i c?ng portb. ch?nh th?
int8 sec, min, hour, day, date, month, year, dem;
int8 ch_sec, ch_min, ch_hour, ch_date, ch_month, ch_year;
int8 dv_sec, dv_min, dv_hour, dv_date, dv_month, dv_year;
#int_TIMER0
void TIMER0_isr(void) 
{
   dem++;
   if(dem==15){   // Tdelay = 1s v?i Prescale = 64 và F = Fosc/2 = 4 Mhz thì PRx= 62500
      dem=0;
      sec++;
   if(sec>59){
      sec=0;      // reset sec v? 0 khi ??m ??n 60
      min++;
   if(min>59){
      min=0;      // reset min v? 0 khi ??m ??n 60
      hour++;
   if(hour>23){
      hour=0;      // reset hour v? 0 khi ??m ??n 24
      day++;
   if(day>7){
      day=1;      // reset day v? 0 khi ??m ??n 8
    }
   date++;
   if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
      if(date>31)
   {
      date=1;
      month++;   // tháng 1,3,5,7,8,10,12 có 31 ngày
    if(month>12)
   {
      month=1;
      year++;      // month > 12 c?ng year lên 1
      }
   }
}
   else if(month==4||month==6||month==9||month==11){
      if(date>30) {
         date=1;
         month++;      // tháng 4,6,9,11 có 30 ngày
         if(month>12){
            month=1;
            year++;
      }
   }
}
   else {
      if((year%4)==0){
         if(date>29){
            date=1; 
            month++;   // n?m % 4 == 0 thì tháng 2 có 29 ngày
            if(month>12){
               month=1;      
               year++;
         }
     }
 }
   else{
      if(date>28){
         date=1;
         month++;   // tháng 2 == 28 ngày
         if(month>12){
            month=1;
            year++;
                     }
                  }
               }
            }
         }
      }
   }
}
}
   void lcd_writec(int8 command)    
{
   rs = 0;
   portd = command;
   en = 1;
   en = 0;
   delay_ms(10);          // en = 1, en = 0 t?t b?t nhanh ?? vi?t l?i s?
}
void lcd_writed(int8 data) 
{
   rs = 1;
   portd = data;
   en = 1;
   en = 0;
   delay_ms(10);
}
void lcd_start()
{
   lcd_writec(0x38);   // 111000
   lcd_writec(0x0c);   // 1100
   lcd_writec(0x06);   // 110
   lcd_writec(0x01);   // 1
}
void lcd_clear()
{
   lcd_writec(0x01);
}
void lcd_cursor(int8 hang,int8 cot)
{
   int8 vitri;
   switch(hang)
   {
   case 1: vitri = cot + 0x80;
   break;
   case 2: vitri = cot + 0xc0;
    break;
   };
   lcd_writec(vitri);
}
void hienthi()
{
   lcd_cursor(1,0);         // dòng 1
   lcd_writed('T');
   lcd_writed(':');
   lcd_writed(' ');
   lcd_writed(ch_hour);    // hi?n th? hàng ch?c c?a gi? 
   lcd_writed(dv_hour);    // hi?n th? hàng ??n v? c?a gi? 
   lcd_writed(':');
   lcd_writed(ch_min);      // hi?n th? phút
   lcd_writed(dv_min);
   lcd_writed(':');
   lcd_writed(ch_sec);      // hi?n th? giây
   lcd_writed(dv_sec);
   lcd_writed(' ');
   lcd_writed(' ');
   lcd_writed('2');
   lcd_writed('4');
   lcd_writed('h');
   lcd_cursor(2,0);         // dòng 2
   lcd_writed('D');
   lcd_writed(':');
   lcd_writed(' ');
   switch(day)                       // xét day, day = 1 = sunday, day = 2 = monday, ...
   {
      case 1: lcd_writed('S');
      lcd_writed('u'); 
      lcd_writed('n'); 
      break;
      case 2: lcd_writed('M');
      lcd_writed('o'); 
      lcd_writed('n'); 
      break; 
      case 3: lcd_writed('T');
      lcd_writed('u'); 
      lcd_writed('e'); 
      break; 
      case 4: lcd_writed('W');
      lcd_writed('e'); 
      lcd_writed('d'); 
      break; 
      case 5: lcd_writed('T');
      lcd_writed('h'); 
      lcd_writed('u'); 
      break; 
      case 6: lcd_writed('F');
      lcd_writed('r'); 
      lcd_writed('i'); 
      break; 
      case 7: lcd_writed('S');
      lcd_writed('a'); 
      lcd_writed('t');
      break; 
   }
   lcd_writed(' ');
   lcd_writed(' ');
   lcd_writed(ch_month);
   lcd_writed(dv_month);
   lcd_writed('/');
   lcd_writed(ch_date);
   lcd_writed(dv_date);
   lcd_writed('/');
   lcd_writed(ch_year);
   lcd_writed(dv_year);
   }
void giaima(){                  // ch phía tr??c là hàng ch?c c?a giá tr? th?i gian, dv là hàng ??n v?, vd: 23h => 23 / 10 = 2 là hàng ch?c, 23 % 10 = 3 là ??n v?
   ch_sec = sec/10 + 0x30;        
   ch_min = min/10 + 0x30;         
   ch_hour = hour/10 + 0x30;
   ch_date = date/10 + 0x30;
   ch_month = month/10 + 0x30;    
   ch_year = year/10 + 0x30;      
   dv_sec = sec%10 + 0x30;         
   dv_min = min%10 + 0x30;
   dv_hour = hour%10 + 0x30;
   dv_date = date%10 + 0x30;
   dv_month = month%10 + 0x30;
   dv_year = year%10 + 0x30;
}
void up_hour()
{
   delay_ms(300);         
   hour++;
   if(hour >23) hour = 0;
}
void up_min()
{
   delay_ms(300);
   min++;
   if(min > 59) min = 0;
}
void up_day()
{ 
   delay_ms(300);
   day++;
   if(day>7) day = 1;
}
void up_date()
{
   delay_ms(300);
   date++;
   day++;
   if(day>7){
      day=1;
}
   if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
   {
      if(date>31)
      date = 1;
   }
      if(month==4 || month==6 || month==9 || month==11)
   {
      if(date>30) 
      date = 1;
   }
      if(month==2)
   {
      if((year%4)==0)
   {
      if(date>29) date=1;
   }
   else
   {
   if(date>28) date=1; 
   }
   }
   }
void up_month()
{ 
   delay_ms(300);
   month++;
   if(month>12) month = 1;
}
void up_year()
{
   delay_ms(300);
   year++;
   if(year>99) year = 0;
}
void main()
{
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   set_tris_a(0x00);
   set_tris_b(0xff);
   set_tris_c(0x00);
   set_tris_d(0x00);
   lcd_start();          
   dem=0;             // khai báo 1 th?i gian nào ?ó t? ??t
   sec=5;
   min=57;
   hour=20;
   date=27;
   month=2;
   day=1;
   year=3;
   while(1)
   {
      giaima();
      hienthi();
      if(up1==0) {   // nút ??u tiên ???c nh?n 
      up_hour();  // g?i hàm này
      }
      if(up2==0) {
      up_min();
      }
      if(up3==0) {
      up_date();
      }
      if(up4==0) {
      up_month();
      }
      if(up5==0) {
      up_year();
      }
      if(up6==0) {
      up_day();
      }
 
   }
 
}
