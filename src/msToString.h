/*
  msToString.h - A function to convert a number of milliseconds into a time
  string of the form (HH)(:MM)(:SS)(.##) in a buffer.
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
#ifndef msToString_h
#define msToString_h

#include <Arduino.h>

/**************************************************************************/
/*!
  @brief    Convert a number of milliseconds into a string.
  @param    MS        A count of a number of milliseconds.
  @param    S         Result buffer of a size large enough to hold the result.
  @param    n         sizeof(S).
  @param    hours     true to include hours in string, false for not.
  @param    minutes   true to include minutes in string, false for not. Ignored
                      and taken as true if 'hours' and 'minutes' are both true.
  @param    seconds   true to include seconds in string, false for not.
  @param    numDigits Determines whether LEADING ZEROES are used for the first
                      number (hours, minutes, or seconds depending on previous
                      arguments) and the other numbers (minutes and/or seconds).
                      Possible values:
                        > 0: the first number has numDigits digits and the
                             others have 2 digits. E.g. 2 means all numbers have
                             exactly 2 digits, while 3 means the first number
                             has 3 digits and the others have 2 digits.
                        0:   leading zeroes are only used for numbers after the
                             first. The first number has any number of digits,
                             while the others have exactly 2 digits since they
                             range from 0 to 59.
                      For example, if all three numbers are shown and numDigits
                      is 2, then if MS is less than 100 hours, the output string
                      will be of the form ##:##:## with leading zeroes used when
                      necessary to make 2 digits. However, if MS is >= 100 hours
                      then the output string will be "XX:XX:XX", with X's used
                      to indicate overflow beyond the desired 2 digits.
  @param    digitsAfterDP   Number of digits to include after a decimal point
                            following the last number. If 0, no decimal point is
                            included. The final digit is NOT ROUNDED.
  @param    exceededMax     If not nullptr, *exceededMax is set true if the
                            number of digits in the first number exceeded
                            numDigits, or is set false if not (or if
                            numDigits=0).
  @returns                  S.
  @note     If the resulting string is longer than n-1 characters, the remaining
            characters are discarded and not stored in S.
  @note     If all of 'hours', 'minutes', 'seconds' are false, MS is converted
            into string representing number of milliseconds, and digitsAfterDP
            is ignored. numDigits is still honored. Thus 'milliseconds' is
            irrelevant, MS is simply an integer to be converted to a string.
  @note     The colon character, ":", is used to separate hours from minutes
            from seconds and is currently fixed, it cannot be changed to a
            different character.
  @note     The decimal point character, ".", used when digitsAfterDP > 0, is
            currently fixed, it cannot be changed to a different character.
*/
/**************************************************************************/
extern char* msToString(uint32_t MS, char* S, size_t n, bool hours=true,
  bool minutes=true, bool seconds=true, int numDigits=0, int digitsAfterDP=0,
  bool* exceededMax=nullptr);

#endif // msToString_h
