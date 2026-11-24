#include "ProjectDefines.h"
#include "Timer.h"
#include "Uart.h"
#include "ExtInt.h"
#include "RingBuffer.h"
#include "driver/ssd1306.h"  

uint32_t EEMEM ee_minutter = 0;

static void skriv_display_linje(uint8_t linje, const char* tekst) {
    SSD1306_SetPosition(0, linje);
    SSD1306_DrawString((char*)tekst, NORMAL); 
}

int main(void) {
    uint32_t gemte_minutter = eeprom_read_dword(&ee_minutter);
    if (gemte_minutter == 0xFFFFFFFF) {
        gemte_minutter = 0;
        eeprom_update_dword(&ee_minutter, 0);
    }
    uint32_t total_sekunder = gemte_minutter * 60UL;
    uint8_t sek_taeller_til_minut = 0;  

    rb_init();
    start_timer();
    start_uart();
    start_ext_int0();

    SSD1306_Init(0x3C);
    SSD1306_ClearScreen();

    char linje_buf[25];
    skriv_display_linje(0, "# DOWN INT: 0       ");
    skriv_display_linje(1, "# UP INT: 0         ");
    sprintf(linje_buf, "TIME: %lu S         ", total_sekunder);
    skriv_display_linje(2, linje_buf);
    skriv_display_linje(3, "000 000 000 000 000 ");
    sprintf(linje_buf, "EEPROM MIN: %lu      ", gemte_minutter);
    skriv_display_linje(4, linje_buf);
    skriv_display_linje(5, "STATUS: INIT        ");
    skriv_display_linje(6, "USER: Shakespear    ");
    skriv_display_linje(7, "EMBEDDED STYRER !!! ");  

    sei(); 

    while (1) {
        rb_behandel();

        if (knap_aendret == 1) {
            knap_aendret = 0;
            sprintf(linje_buf, "# DOWN INT: %u       ", down_int_count);
            skriv_display_linje(0, linje_buf);
            sprintf(linje_buf, "# UP INT: %u         ", up_int_count);
            skriv_display_linje(1, linje_buf);
        }

        if (sekund_flag == 1) {
            sekund_flag = 0;
            total_sekunder++;
            sek_taeller_til_minut++;

            if (sek_taeller_til_minut >= 60) {
                sek_taeller_til_minut = 0;
                gemte_minutter++;
                eeprom_update_dword(&ee_minutter, gemte_minutter);
                sprintf(linje_buf, "EEPROM MIN: %lu      ", gemte_minutter);
                skriv_display_linje(4, linje_buf);
            }

            sprintf(linje_buf, "TIME: %lu S         ", total_sekunder);
            skriv_display_linje(2, linje_buf);

            uint8_t s5[5];
            rb_hent_sidste_5(s5);
            sprintf(linje_buf, "%03u %03u %03u %03u %03u ", s5[0], s5[1], s5[2], s5[3], s5[4]);
            skriv_display_linje(3, linje_buf);

            if (rb_er_aktiv()) {
                skriv_display_linje(5, "STATUS: RINGBUF RUN ");
            } else {
                skriv_display_linje(5, "STATUS: INIT        ");
            }
        }
    }
}