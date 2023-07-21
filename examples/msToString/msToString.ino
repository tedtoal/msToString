#include <Arduino.h>
#include <msToString.h>
#include <monitor_printf.h>

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
  monitor.printf("Expect XX             %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 2));
  monitor.printf("Expect X              %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 1));
  monitor.printf("Expect XX.XXXX        %s\n", msToString(123*3600000UL+45678UL*36, S, n, true, false, false, 2, 4));

  monitor.printf("MM\n");
  monitor.printf("Expect 123            %s\n", msToString(123*60000UL, S, n, false, true, false));
  monitor.printf("Expect 12345.678      %s\n", msToString(12345*60000UL+678UL*60, S, n, false, true, false, 0, 3));
  monitor.printf("Expect XXXX           %s\n", msToString(12345*60000UL+678UL*60, S, n, false, true, false, 4));
  monitor.printf("Expect XXXX.XXXX      %s\n", msToString(12345*60000UL+678UL*60, S, n, false, true, false, 4, 4));

  monitor.printf("SS\n");
  monitor.printf("Expect 123            %s\n", msToString(123*1000UL, S, n, false, false, true));
  monitor.printf("Expect 12345.678      %s\n", msToString(12345*1000UL+678UL, S, n, false, false, true, 0, 3));
  monitor.printf("Expect XXXX           %s\n", msToString(12345*1000UL+678UL, S, n, false, false, true, 4));
  monitor.printf("Expect XXXX.XXXX      %s\n", msToString(12345*1000UL+678UL, S, n, false, false, true, 4, 4));

  monitor.printf("HH:MM\n");
  monitor.printf("Expect 12:34          %s\n", msToString(12*3600000UL+34*60000UL, S, n, true, true, false));
  monitor.printf("Expect 123:45         %s\n", msToString(123*3600000UL+45*60000UL, S, n, true, true, false));
  monitor.printf("Expect X:XX           %s\n", msToString(12*3600000UL+34*60000UL, S, n, true, true, false, 1));
  monitor.printf("Expect XX:XX          %s\n", msToString(123*3600000UL+45*60000UL, S, n, true, true, false, 2));
  monitor.printf("Expect 123:45.670     %s\n", msToString(123*3600000UL+45*60000UL+67UL*600, S, n, true, true, false, 0, 3));

  monitor.printf("HH:(MM):SS\n");
  monitor.printf("Expect 12:34:56       %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, false, true));
  monitor.printf("Expect 123:45:32      %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, false, true));
  monitor.printf("Expect X:XX:XX        %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, false, true, 1));
  monitor.printf("Expect XX:XX:XX       %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, false, true, 2));
  monitor.printf("Expect 123:45:32.678  %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL+678UL, S, n, true, false, true, 0, 3));

  monitor.printf("HH:MM:SS\n");
  monitor.printf("Expect 12:34:56       %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, true, true));
  monitor.printf("Expect 123:45:32      %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, true, true));
  monitor.printf("Expect X:XX:XX        %s\n", msToString(12*3600000UL+34*60000UL+56*1000UL, S, n, true, true, true, 1));
  monitor.printf("Expect XX:XX:XX       %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL, S, n, true, true, true, 2));
  monitor.printf("Expect 123:45:32.678  %s\n", msToString(123*3600000UL+45*60000UL+32*1000UL+678UL, S, n, true, true, true, 0, 3));

  monitor.printf("MM:SS\n");
  monitor.printf("Expect 12:34          %s\n", msToString(12*60000UL+34*1000UL, S, n, false, true, true));
  monitor.printf("Expect 123:45         %s\n", msToString(123*60000UL+45*1000UL, S, n, false, true, true));
  monitor.printf("Expect X:XX           %s\n", msToString(12*60000UL+34*1000UL, S, n, false, true, true, 1));
  monitor.printf("Expect XX:XX          %s\n", msToString(123*60000UL+45*1000UL, S, n, false, true, true, 2));
  monitor.printf("Expect 123:45.670     %s\n", msToString(123*60000UL+45*1000UL+670UL, S, n, false, true, true, 0, 3));
}

void loop() {
  delay(1000);
}
