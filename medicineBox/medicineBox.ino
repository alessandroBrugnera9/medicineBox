#include <arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <vector.h>
#include <virtuabotixRTC.h>


// --- Mapeamento de Hardware ---
#define   clk   6
#define   dat   7
#define   rst   8


// ========================================================================================================
// --- Constantes Auxiliares ---
#define   segL       15
#define   minL       32
#define   horL       11
#define   d_semL      4
#define   d_mesL     18
#define   mesL        4
#define   anoL     2025


// ========================================================================================================
// --- Declaração de Objetos ---
virtuabotixRTC   myRTC(clk, dat, rst);         //declara objeto para o RTC
using namespace std;

//Remedios
struct medicine {
    char name[40];
    int place;
    int stock;
    int dose[2];
};
int nextDose;
int led;
class running {
    int daily;
    int takenTilNow;
public:
    int getDaily() const;

    void setDaily(int daily);

    int getTakenTilNow() const;

    void setTakenTilNow(int takenTilNow);
};



Vector<int> scheduleHours;
Vector<int> scheduleMinutes;
Vector<int> scheduleMedicine;
int daily;
int takenTilNow;


// watchdog interrupt
ISR (WDT_vect) {
        wdt_disable();  // disable watchdog

}  // end of WDT_vect

//--------------------Auxiliares-----------------
int currentTime[2] () {
    myRTC.updateTime();
    int time[2] = {myRTC.hours, myRTC.minutes};
    return time;
}

int getNextDose(int daily, int ) { //TODO arrumar essa funcao
    int time [2] = currentTime();
    if (takenTilNow<daily) { //calcula quantos rests o atmega deve fazer ate proximo remedio
        int difference= 60*(scheduleHours[takenTilNow]-nowHour) + scheduleMinutes[takenTilNow]-nowMinute;
        nextDose= 60*difference/8;
    }
    else {
        nextDose=0;
    }
    return nextDose;
}

void setup () {
    int daily= scheduleHours.size();
    for (int i=0; schduleHours[i]<nowHour && scheduleMinutes[i]<nowMinute; i++) { //ve quantos remedios ja deveriam ter sido tomados ate agr
        takenTilNow=i;
    }

    int nextDose = getnextDose;
}

void loop ()
{
    int nextDose=nextDose-1;
    if (takenTilNow<daily) {
        if (nextdose=0) {
            led=true; //TODO melhorar logicA
            while (led) { //verficar se vale como boolean
                //setar led high
                if () { //botao apertado
                    nextDose=
                }
            }
        }
    }
    else {
        nextDose=;
    }



    // disable ADC
    ADCSRA = 0;

    // clear various "reset" flags
    MCUSR = 0;
    // allow changes, disable reset
    WDTCSR = bit (WDCE) | bit (WDE);
    // set interrupt mode and an interval
    WDTCSR = bit (WDIE) | bit (WDP3) | bit (WDP0);    // set WDIE, and 8 seconds delay
    wdt_reset();  // pat the dog

    set_sleep_mode (SLEEP_MODE_PWR_DOWN);
    noInterrupts ();           // timed sequence follows
    sleep_enable();

    // turn off brown-out enable in software
    MCUCR = bit (BODS) | bit (BODSE);
    MCUCR = bit (BODS);
    interrupts ();             // guarantees next instruction executed
    sleep_cpu ();

    // cancel sleep as a precaution
    sleep_disable();

}
