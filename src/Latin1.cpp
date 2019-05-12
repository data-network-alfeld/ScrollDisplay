#include "Latin1.h"

String Latin1::utf8tolatin1(String utf8) {
    String output = "";
    const uint16_t error = 0xFFFD;
    uint16_t partial = 0;
    uint16_t count = 0;
    for (int i=0; i<utf8.length(); i++) {
        uint16_t next = utf8.charAt(i);
        switch (count) {
            case 0:
                if ((next & 0x80) == 0) {
                    partial = next;
                } else if ((next & 0xE0) == 0xC0) {
                    partial |= (next & 0x1F) << 6;
                    count = 1;
                } else if ((next & 0xF0) == 0xE0) {
                    partial |= (next & 0x0F) << 12;
                    count = 2;
                } else {
                    partial = error;
                }
                break;
            case 1:
                if ((next & 0xC0) == 0x80) {
                    partial |= next & 0x3F;;
                    count = 0;
                } else {
                    partial = error;
                    count = 0;
                }
                break;
            case 2:
                if ((next & 0xC0) == 0x80) {
                    partial |= (next & 0x3F) << 6;
                    count = 1;
                } else {
                    partial = error;
                    count = 0;
                }
                break;
        }
        if (count == 0) {
            output += (char)partial;
            partial = 0;
        }
    }
    return output;
    // if (count != 0) incomplete code
}