/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1827
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#define     Motor_IN1           LATBbits.LATB3
#define     Motor_IN2           LATBbits.LATB4
#define     Motor_IN3           LATBbits.LATB7
#define     Motor_IN4           LATBbits.LATB6
#define     CW                  1
#define     CCW                 0
#define     STOP                2
#define     Sensor_MID          PORTBbits.RB0
#define     Sensor_LEFT         PORTAbits.RA0
#define     Sensor_RIGHT        PORTAbits.RA1
#define     Trang               0 // 2 LED sáng
#define     Den                 1 // 1 LED sáng
#define     Tien                300
#define     BanhTrai            500
#define     BanhPhai            490
#define     Lui                 480
#define     Sensor_Distance     PORTBbits.RB5
#define     Servo               LATAbits.LATA7
#define     _XTAL_FREQ          4000000
unsigned char CMD[10] = {0,0,0,0,0,0,0,0};
unsigned char CMD1[10] = {0,0,0,0,0,0,0,0};
unsigned int speed = 0;
unsigned char value =0;
unsigned int dem = 0;
unsigned int state1 = 0;
void MotorRight_set_direction(unsigned char dir){
    if (dir == 0){
        Motor_IN1 = 1;
        Motor_IN2 = 0;
    }
    else if (dir ==1){
        Motor_IN1 = 0;
        Motor_IN2 = 1;
    }
    else if (dir ==2){
        Motor_IN1 = 1;
        Motor_IN2 = 1;
    }
}
void MotorLeft_set_direction(unsigned char dir){
    if (dir == 0){
        Motor_IN3 = 1;
        Motor_IN4 = 0;
    }
    else if (dir ==1){
        Motor_IN3 = 0;
        Motor_IN4 = 1;
    }
    else if (dir ==2){
        Motor_IN3 = 1;
        Motor_IN4 = 1;
    }
}
void Servo_Motion_CW(){
    for(int i=0;i<50;i++){
        Servo = 1;
        __delay_ms(1.5);
        Servo = 0;
        __delay_ms(18.5);
    }
}
void Servo_Motion_CCW(){
    for(int i=0;i<50;i++){
        Servo = 1;
        __delay_ms(0.5);
        Servo = 0;
        __delay_ms(19.5);
    }
}
void Dilui(){
    MotorLeft_set_direction(CCW);
    MotorRight_set_direction(CCW);
    PWM3_LoadDutyValue(Lui);
    PWM4_LoadDutyValue(Lui);
}
void Retrai(){
    MotorLeft_set_direction(STOP);
    MotorRight_set_direction(CW);
    PWM3_LoadDutyValue(BanhPhai);
    PWM4_LoadDutyValue(0);
}
void Rephai(){
    MotorRight_set_direction(STOP); 
    MotorLeft_set_direction(CW);
    PWM3_LoadDutyValue(0);
    PWM4_LoadDutyValue(BanhTrai);
}
void Dithang(){
    MotorLeft_set_direction(CW);
    MotorRight_set_direction(CW);
    PWM3_LoadDutyValue(BanhPhai);
    PWM4_LoadDutyValue(BanhTrai);
}
void Dithang1(){
    MotorLeft_set_direction(CW);
    MotorRight_set_direction(CW);
    PWM3_LoadDutyValue(BanhPhai);
    PWM4_LoadDutyValue(BanhTrai);
}
void Dunglai(){
    MotorLeft_set_direction(STOP);
    MotorRight_set_direction(STOP);
    PWM3_LoadDutyValue(0);
    PWM4_LoadDutyValue(0);
}
void Bluetooth(){
    while (EUSART_is_rx_ready() == 1){
        CMD[0] = EUSART_Read();
        if(CMD[0] == '1')               speed = 10;
        else if(CMD[0] == '2')          speed = 20;
        else if(CMD[0] == '3')          speed = 30;    
        else if(CMD[0] == '4')          speed = 40;
        else if(CMD[0] == '5')          speed = 50;
        else if(CMD[0] == '6')          speed = 60;
        else if(CMD[0] == '7')          speed = 70;
        else if(CMD[0] == '8')          speed = 80;
        else if(CMD[0] == '9')          speed = 90;
        else if(CMD[0] == 'q')          speed = 90;         
        else if(CMD[0] == 'F'){
            Dithang();     
        }
        else if(CMD[0] == 'B'){
            Dilui();
        }
        else if(CMD[0] == 'L'){
            Retrai();
        }
        else if(CMD[0] == 'R'){
            Rephai();
        }
        else if(CMD[0] == 'S'){
            Dunglai();
        }
        else if(CMD[0] == 'W'){
            Servo_Motion_CCW();
        }
    }
}
void Doline_Cong(){
    if((Sensor_LEFT == Den)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Trang)){
        Retrai(); 
    }
    else if((Sensor_LEFT == Trang)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Den)){
        Rephai();
    }
    else if((Sensor_LEFT == Trang)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Trang)){
        Dithang();
    }
    else if((Sensor_LEFT == Den)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Den)){
        Retrai();
    }
    else if((Sensor_LEFT == Trang)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Den)){
        Rephai();
    }
    else if((Sensor_LEFT == Den)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Trang)){
        Retrai();
    }
    else if((Sensor_LEFT == Den)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Den)){
        Dilui();
    }
    else if((Sensor_LEFT == Trang)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Trang)){
        Dilui();
    }
}
void Kep(){
    Dunglai();
    Servo_Motion_CW();
    dem = dem +1;
}
void Doline_Thang(){
    while ((Sensor_LEFT == Trang)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Trang)&&(dem == 1)){
        Dilui();
    }
    while ((Sensor_LEFT == Den)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Trang)&&(dem == 1)){
        Retrai(); 
    }
    while ((Sensor_LEFT == Trang)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Den)&&(dem == 1)){
        Rephai();
    }
    while ((Sensor_LEFT == Trang)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Trang)&&(dem == 1)){
        Dithang();
    }
    while ((Sensor_LEFT == Trang)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Den)&&(dem == 1)){
        Rephai();
    }
    while ((Sensor_LEFT == Den)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Trang)&&(dem == 1)){
        Retrai();
    }
    while ((Sensor_LEFT == Den)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Den)&&(dem == 1)){
        Dilui();
    }
    while ((Sensor_LEFT == Den)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Den)&&(dem == 1)){
        Rephai();
        if ((Sensor_LEFT == Trang)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Trang)&&(dem == 1))
            Dilui();
        else if ((Sensor_LEFT == Den)&&(Sensor_MID == Trang)&&(Sensor_RIGHT == Den)&&(dem == 1))
            dem = dem + 1;
        else if ((Sensor_LEFT == Trang)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Den)&&(dem == 1))
            dem = dem + 1;
    }
}
void Diquavach(){
    Dithang();
    if ((Sensor_LEFT == Trang)&&(Sensor_MID == Den)&&(Sensor_RIGHT == Trang)&&(dem == 0))
        dem = dem + 1;
}
void main(void){
    SYSTEM_Initialize();
    while (1){
        while (dem==0){
            Dithang();
            __delay_ms(100);
            dem = dem +1;
        }
        while ((Sensor_Distance == 1)&&(dem == 1)){
            Doline_Cong();
        }
        if (Sensor_Distance == 0){
            Kep();
        }
        while (dem == 2){
            Bluetooth();
        }
    }
}