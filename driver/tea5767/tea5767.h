#ifndef __TEA5767_H
#define __TEA5767_H
#include <stdint.h>

#define ADD_TEA5767  (0x60)

/* 1st data byte*/
#define TEA5767_DEFAULT_MASK                  0x3F // No Mute and no Search mode            
#define TEA5767_MUTE_MASK                     0x80 // Mute output
#define TEA5767_SEARCH_MASK                   0x40 // Search mode
/* 3rd data byte */
#define TEA5767_SEARCH_UP_MASK                0x80 // Search UP (frequency increase)
#define TEA5767_SEARCH_DOWN_MASK              0x00 // Search DOWN (frequency decrease)
#define TEA5767_SEARCH_STOP_HIGH_MASK         0x60 // Search stop level: High (ADC = 10)
#define TEA5767_SEARCH_STOP_MID_MASK          0x40 // Search stop level: Mid (ADC = 7)
#define TEA5767_SEARCH_STOP_LOW_MASK          0x20 // Search stop level: Low (ADC = 5)
#define TEA5767_HI_INJECTION_MASK             0x10 // HLSI=1 (HI side injection)
#define TEA5767_LO_INJECTION_MASK             0x00 // HLSI=0 (LO side injection)
#define TEA5767_MONO_MASK                     0x08 // Force mono mode
#define TEA5767_STEREO_MASK                   0x00 // Enable stereo
#define TEA5767_MUTE_RIGHT_MASK               0x04 // Mute right channel
#define TEA5767_MUTE_LEFT_MASK                0x02 // Mute left channel
/* 4rd data byte */
#define TEA5767_STANDBY_MASK                  0x40 // Standby mode
#define TEA5767_JAPAN_BAND_MASK               0x20 // Japanese FM band (76MHz to 91MHz)
#define TEA5767_EUROPE_BAND_MASK              0x00 // Europe FM band (87.5MHz to 108MHz)
#define TEA5767_XTAL_MASK                     0x10 // Clock freq = 32.768kHz
#define TEA5767_SOFT_MUTE_MASK                0x08 // Soft mute
#define TEA5767_HCC_MASK                      0x04 // High Cut Control on  (HCC bit = 1)
#define TEA5767_HCC_OFF_MASK                  0x00 // High Cut Control off (HCC bit = 0)
#define TEA5767_SNC_MASK                      0x02 // Stereo Noise Cancelling is on  (SNC bit = 1)
#define TEA5767_SNC_OFF_MASK                  0x00 // Stereo Noise Cancelling is off (SNC bit = 0)

void setFrequency(float frequency,uint32_t statusMute);
void muteVolume(float freq);
void scanFrequency(uint8_t scanDirection);
#endif /*__TEA5767_H*/