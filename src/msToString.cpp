/*
  msToString.h - A function to convert a number of milliseconds into a time
  string of the form HH(.##) or HH:MM(.##) or HH:MM:SS(.##) in a buffer.
  Created by Ted Toal, July 19, 2023.
  Released into the public domain.


  Software License Agreement (BSD License)

  Copyright (c) 2023 Ted Toal
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  3. Neither the name of the copyright holders nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <msToString.h>
#include <monitor_printf.h>

char* msToString(uint32_t MS, char* S, size_t n, bool hours, bool minutes,
  bool seconds, int maxDigitsFN, int digitsAfterDP, bool* exceededMax) {

  bool _exceededMax = false;
  size_t len;
  char* p = S;
  uint32_t div = 0;

  // hours=minutes=seconds=false
  // Plain conversion of MS to an integer string, honoring maxDigitsFN.
  if (!hours && !minutes && !seconds) {
    if (maxDigitsFN > 0) {
      int Ndigits = 1;
      for (uint32_t V = 10; MS >= V && V != 1000000000; V *= 10)
        if (++Ndigits > maxDigitsFN) {
          _exceededMax = true;
          break;
        }
      }
    if (!_exceededMax)
      snprintf(p, n, "%02ld", MS);
    else {
      while (maxDigitsFN > 0 && n > 0) {
        *p++ = 'X';
        n--;
        maxDigitsFN--;
      }
      *p = 0;
    }
  }

  // hours=true
  if (hours) {
    div = 3600000UL; // That many milliseconds in an hour.
    uint16_t hours = (uint16_t) (MS / div);
    MS %= div;
    // Use recursive call with hours=minutes=seconds=false to convert hours to
    // a string, honoring maxDigitsFN.
    msToString(hours, p, n, false, false, false, maxDigitsFN, 0, &_exceededMax);
    maxDigitsFN = 0;
    len = strlen(p);
    p = p + len;
    n -= len;
  }

  // minutes=true OR hours=seconds=true
  if (minutes || (hours && seconds)) {
    if (p != S && n > 0) {
      *p++ = ':';
      *p = 0;
      n--;
    }
    if (_exceededMax) {
      strncpy(p, "XX", n);
      p[n] = 0;
    } else {
      div = 60000U; // That many milliseconds in a minute.
      uint32_t minutes = MS / div;
      MS %= div;
      msToString(minutes, p, n, false, false, false, maxDigitsFN, 0, &_exceededMax);
      maxDigitsFN = 0;
    }
    len = strlen(p);
    p = p + len;
    n -= len;
  }

  // seconds=true
  if (seconds) {
    if (p != S && n > 0) {
      *p++ = ':';
      *p = 0;
      n--;
    }
    if (_exceededMax) {
      strncpy(p, "XX", n);
      p[n] = 0;
    } else {
      div = 1000U; // That many milliseconds in a second.
      uint32_t seconds = MS / div;
      MS %= div;
      msToString(seconds, p, n, false, false, false, maxDigitsFN, 0, &_exceededMax);
      maxDigitsFN = 0;
    }
    len = strlen(p);
    p = p + len;
    n -= len;
  }

  // If requested, add decimal point and following digits.
  if (digitsAfterDP > 0 && div > 0 && n > 0) {
    *p++ = '.';
    *p = 0;
    n--;
    // We need to compute the first digitsAfterDP of MS/div.
    while (digitsAfterDP-- && n > 0) {
      if (_exceededMax) {
        *p++ = 'X';
        *p = 0;
      } else {
        MS *= 10;
        int digit = (int) (MS/div);
        MS %= div;
        sprintf(p++, "%d", digit);
      }
      n--;
    }
  }

  if (exceededMax != NULL)
    *exceededMax = _exceededMax;
  return(S);
}

// -------------------------------------------------------------------------
