#include "ProjectDefines.h"
#include "RingBuffer.h"
#include "Uart.h"

typedef enum {
    RB_VENTER_PAA_KOLON,      // Venter på ':' for at sende :Shakespear:
    RB_VENTER_PAA_SEMIKOLON,  // Venter på ';' for at starte ringbuffer
    RB_KOERER                 // Aktiv: modtager 0-255 bytes i ringbuffer
} RbTilstand_t;

static volatile RbTilstand_t rb_tilstand = RB_VENTER_PAA_KOLON;

static volatile uint8_t buffer[RINGBUFFER_SIZE];
static volatile uint8_t head = 0; // Skrive-indeks (hoved)
static volatile uint8_t tail = 0; // Læse-indeks (hale)

static volatile uint8_t sidste_5[5] = {0, 0, 0, 0, 0};
static volatile uint8_t overrun_flag = 0;
static volatile uint8_t mistet_tal = 0;

void rb_init(void) {
    head = 0;
    tail = 0;
    overrun_flag = 0;
    rb_tilstand = RB_VENTER_PAA_KOLON;
}

uint8_t rb_er_aktiv(void) {
    return (rb_tilstand == RB_KOERER);
}

// Kaldes direkte fra UART0 RX Interrupt når der kommer en byte ind
void rb_modtag_byte(uint8_t data) {
    // Krav 5 & 7: Hvis modsatte part sender '_' eller '-', gå tilbage i init-tilstand
    if (rb_tilstand == RB_KOERER && (data == '_' || data == '-')) {
        rb_init();
        return;
    }

    if (rb_tilstand == RB_VENTER_PAA_KOLON) {
        if (data == ':') {
            uart1_send_tekst(BRUGERNAVN_STR); // Krav 2: Send ":Shakespear:" på UART1
            rb_tilstand = RB_VENTER_PAA_SEMIKOLON;
        }
    } 
    else if (rb_tilstand == RB_VENTER_PAA_SEMIKOLON) {
        if (data == ';') {
            head = 0;
            tail = 0;
            rb_tilstand = RB_KOERER; // Krav 2: Start ringbuffer-funktionalitet
        }
    } 
    else if (rb_tilstand == RB_KOERER) {
        // Gem altid de 5 seneste modtagne tal til visning på display (Krav 15)
        for (int i = 0; i < 4; i++) {
            sidste_5[i] = sidste_5[i + 1];
        }
        sidste_5[4] = data;

        // Beregn næste plads for hovedet (wrap around med modulo)
        uint8_t naeste_head = (head + 1) % RINGBUFFER_SIZE;

        // Krav 6: Tjek om hovedet overhaler halen (Buffer Overrun)
        if (naeste_head == tail) {
            mistet_tal = data; // Ignorer det nye tal og gem det til fejlrapport
            overrun_flag = 1;
        } else {
            buffer[head] = data;
            head = naeste_head;
        }
    }
}

// Kaldes løbende i main(): Tømmer ringbufferen fra hale til hoved
void rb_behandel(void) {
    // Krav 6: Rapporter Buffer Overrun på UART1 i formatet ";mistet_tal;"
    if (overrun_flag == 1) {
        overrun_flag = 0;
        char fejl_tekst[16];
        sprintf(fejl_tekst, ";%u;", mistet_tal);
        uart1_send_tekst(fejl_tekst);
    }

    // Krav 4: Tag værdier fra halen indtil vi når hovedet, og send på UART1
    while (tail != head) {
        uint8_t val = buffer[tail];
        tail = (tail + 1) % RINGBUFFER_SIZE;
        uart1_send_byte(val);
    }
}

void rb_hent_sidste_5(uint8_t dest[5]) {
    cli(); // Slå interrupts kort fra mens vi kopierer de 5 bytes sikkert
    for (int i = 0; i < 5; i++) {
        dest[i] = sidste_5[i];
    }
    sei();
}