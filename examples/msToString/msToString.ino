/*
  msToString.ino - A program to test and demonstrate use of msToString().
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
#include <msToString.h>
#include <monitor_printf.h>

uint32_t MS;
char S[20];
const char n = sizeof(S);

void setup() {
  char S[30];
  char n = sizeof(S);
  monitor.begin(&Serial, 115200);

  monitor.printf("Expect 12:34:56       %s\n", msToString((((12*60)+34)*60+56)*1000, S, n));

  monitor.printf("hours=minutes=seconds=false\n");
  monitor.printf("Expect 1234567890     %s\n", msToString(1234567890UL, S, n, false, false, false));

  monitor.printf("HH\n");
  monitor.printf("Expect 123            %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false));
  monitor.printf("Expect 123.45678      %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 0, 5));
  monitor.printf("Expect 123.456        %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 0, 3));
  monitor.printf("Expect 0123.456       %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 4, 3));
  monitor.printf("Expect XX             %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 2));
  monitor.printf("Expect X              %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 1));
  monitor.printf("Expect XX.XXXX        %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 2, 4));

  monitor.printf("MM\n");
  monitor.printf("Expect 123            %s\n", msToString(123*60000UL, S, n, false, true, false));
  monitor.printf("Expect 00123          %s\n", msToString(123*60000UL, S, n, false, true, false, 5));
  monitor.printf("Expect 12345.678      %s\n", msToString(12345*60000UL+678UL*60, S, n, false, true, false, 0, 3));
  monitor.printf("Expect XXXX           %s\n", msToString(12345*60000UL+678UL*60, S, n, false, true, false, 4));
  monitor.printf("Expect XXXX.XXXX      %s\n", msToString(12345*60000UL+678UL*60, S, n, false, true, false, 4, 4));

  monitor.printf("SS\n");
  monitor.printf("Expect 123            %s\n", msToString(123*1000UL, S, n, false, false, true));
  monitor.printf("Expect 0123           %s\n", msToString(123*1000UL, S, n, false, false, true, 4));
  monitor.printf("Expect 12345.678      %s\n", msToString(12345*1000UL+678UL, S, n, false, false, true, 0, 3));
  monitor.printf("Expect XXXX           %s\n", msToString(12345*1000UL+678UL, S, n, false, false, true, 4));
  monitor.printf("Expect XXXX.XXXX      %s\n", msToString(12345*1000UL+678UL, S, n, false, false, true, 4, 4));

  monitor.printf("HH:MM\n");
  monitor.printf("Expect 12:34          %s\n", msToString(12*3600000UL+34*60000UL, S, n, true, true, false));
  monitor.printf("Expect 123:45         %s\n", msToString(123*3600000UL+45*60000UL, S, n, true, true, false));
  monitor.printf("Expect 1:23           %s\n", msToString(1*3600000UL+23UL*60000, S, n, true, false, false));
  monitor.printf("Expect 01:23          %s\n", msToString(1*3600000UL+23UL*60000, S, n, true, false, false, 2));
  monitor.printf("Expect X:XX           %s\n", msToString(12*3600000UL+34*60000UL, S, n, true, true, false, 1));
  monitor.printf("Expect XX:XX          %s\n", msToString(123*3600000UL+45*60000UL, S, n, true, true, false, 2));
  monitor.printf("Expect 123:45.670     %s\n", msToString(123*3600000UL+45*60000UL+67UL*600, S, n, true, true, false, 0, 3));

  monitor.printf("HH:(MM):SS\n");
  monitor.printf("Expect 12:34:56       %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, false, true));
  monitor.printf("Expect 123:45:32      %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, false, true));
  monitor.printf("Expect 1:23:45        %s\n", msToString(1*3600000UL+23*60000UL+45*1000UL, S, n, true, false, true));
  monitor.printf("Expect 01:23:45       %s\n", msToString(1*3600000UL+23*60000UL+45*1000UL, S, n, true, false, true, 2));
  monitor.printf("Expect X:XX:XX        %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, false, true, 1));
  monitor.printf("Expect XX:XX:XX       %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, false, true, 2));
  monitor.printf("Expect 123:45:32.678  %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL+678UL, S, n, true, false, true, 0, 3));

  monitor.printf("HH:MM:SS\n");
  monitor.printf("Expect 12:34:56       %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, true, true));
  monitor.printf("Expect 123:45:32      %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, true, true));
  monitor.printf("Expect 1:23:45        %s\n", msToString(1*3600000UL+23*60000UL+45*1000UL, S, n, true, true, true));
  monitor.printf("Expect 01:23:45       %s\n", msToString(1*3600000UL+23*60000UL+45*1000UL, S, n, true, true, true, 2));
  monitor.printf("Expect X:XX:XX        %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, true, true, 1));
  monitor.printf("Expect XX:XX:XX       %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, true, true, 2));
  monitor.printf("Expect 123:45:32.678  %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL+678UL, S, n, true, true, true, 0, 3));

  monitor.printf("MM:SS\n");
  monitor.printf("Expect 12:34          %s\n", msToString(12*60000UL+34*1000UL, S, n, false, true, true));
  monitor.printf("Expect 123:45         %s\n", msToString(123*60000UL+45*1000UL, S, n, false, true, true));
  monitor.printf("Expect 1:23           %s\n", msToString(1*60000UL+23*1000UL, S, n, false, true, true));
  monitor.printf("Expect 01:23          %s\n", msToString(1*60000UL+23*1000UL, S, n, false, true, true, 2));
  monitor.printf("Expect 12:34          %s\n", msToString(12*60000UL+34*1000UL, S, n, false, true, true));
  monitor.printf("Expect X:XX           %s\n", msToString(12*60000UL+34*1000UL, S, n, false, true, true, 1));
  monitor.printf("Expect XX:XX          %s\n", msToString(123*60000UL+45*1000UL, S, n, false, true, true, 2));
  monitor.printf("Expect 123:45.670     %s\n", msToString(123*60000UL+45*1000UL+670UL, S, n, false, true, true, 0, 3));

  MS = 0;
  monitor.printf("Initial elapsed time is %s\n", msToString(MS, S, n));
}

void loop() {
  delay(1000);
  MS += 1000;
  monitor.printf("Current elapsed time is %s\n", msToString(MS, S, n));
}
