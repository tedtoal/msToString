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
  @param    maxDigitsFN     Maximum number of digits in the first number, or 0
                            to allow it to have any number of digits. For
                            example, if hours=true and maxDigitsFN=2, then if MS
                            is more than 99 hours, XX hours is shown and the
                            other values if any are also X's.
  @param    digitsAfterDP   Number of digits to include a decimal point and this
                            many digits after it. The decimal point follows the
                            last number, whether it be hours, minutes, or
                            seconds as selected by previous three arguments.
  @param    exceededMax     If not NULL, *exceededMax is set true if the number
                            of digits in the first number exceeded maxDigitsFN,
                            or is set false if not (or if maxDigitsFN=0).
  @returns                  S.
  @note     A leading zero is included if number of hours, minutes, and/or
            seconds is < 10.
  @note     If all of 'hours', 'minutes', 'seconds' are false, MS is converted
            into string representing number of milliseconds, and digitsAfterDP
            is ignored. maxDigitsFN is still honored. Thus 'milliseconds' is
            irrelevant, MS is simply an integer to be converted to a string.
  @note     If the resulting string is longer than n-1 characters, the remaining
            characters are discarded and not stored in S.
  @note     When digitsAfterDP > 0, the final digit is NOT ROUNDED.
*/
/**************************************************************************/
extern char* msToString(uint32_t MS, char* S, size_t n, bool hours=true,
  bool minutes=true, bool seconds=true, int maxDigitsFN=0, int digitsAfterDP=0,
  bool* exceededMax=NULL);

#endif // msToString_h
