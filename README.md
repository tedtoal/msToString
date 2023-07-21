# msToString

## Library for converting a number of milliseconds into a time string such as "HH:MM:SS"

This library provides a C code function named msToString() that converts a long integer (uint32_t type) value that represents a number of milliseconds into a string that takes one of the forms "HH", "HH:MM", "HH:MM:SS", "MM", "MM:SS", "SS", or any of those followed by a decimal point and fractional digits. The string could be printed to a device such as the serial monitor port or a display, for example.

## Example usage

Here is sample code showing how to use the `msToString()` function. It also uses the `monitor_printf` library to printf to the serial monitor window.

```
#include <msToString.h>
#include <monitor_printf.h>

uint32_t MS;
char S[20];
const char n = sizeof(S);

void setup() {
  monitor.begin(&Serial, 115200);
  MS = 0;
  monitor.printf("Initial elapsed time is %s\n", msToString(MS, S, n));
}

void loop() {
  delay(1000);
  MS += 1000;
  monitor.printf("Current elapsed time is %s\n", msToString(MS, S, n));
}
```

The string output from msToString() above is of the form "HHH:MM:SS" giving the number of hours, minutes, and seconds that MS milliseconds equates to, ignoring extra milliseconds short of a full second.

Note that the colon character, ":", is currently fixed and cannot be changed to a different character.

## msToString() declaration

The `msToString()` function has this declaration:

```
char* msToString(uint32_t MS, char* S, size_t n, bool hours=true,
  bool minutes=true, bool seconds=true, int numDigitsFN=0, int digitsAfterDP=0,
  bool* exceededMax=NULL);
```

The arguments are:

> **MS:** the long integer (uint32_t type) value that is the number of milliseconds to convert to a string.

> **S:** a character buffer in which to place the result, must be at least as long as the longest expected result.

> **n:** sizeof(S), the number of characters in the character buffer S. Result is truncated beyond this.

> **hours:** true to show hours in the result, false to omit hours, default is true.

> **minutes:** true to show minutes in the result, false to omit minutes, default is true.

> **seconds:** true to show seconds in the result, false to omit seconds, default is true.

> **numDigitsFN:** number of digits to show for the first number (whether it be hours, minutes, or seconds), default is 0. If 0, there is no limit on the number of digits to show. Otherwise, if the value of MS gives a first number with more digits than this, the entire result is shown with "X"'s instead of digits, to indicate overflow of result. Or, if MS gives a value with fewer digits than this, leading 0's are included to fill out the length of the first number to equal this. For example, if numDigitsFN is 3 and the first number is "4", it will be filled out with two leading zeroes to give "004" with 3 digits total.

> **digitsAfterDP:** number of digits to show after a decimal point at the end of the string, default is 0. If 0, no decimal point and additional digits are shown. Otherwise, whatever number of milliseconds remain beyond what is shown by the hours, minutes, and/or seconds shown are displayed as a fraction of the last number shown. For example, if digitsAfterDP is 2 and hours and minutes are shown but seconds are not, then if 6000 milliseconds are left over after computing the hours and minutes numbers, then ".10" would appear after the "HH:MM" numbers, for example "2:45.10".

> **exceededMax:** is normally NULL, which is its default value. If not NULL, it is a pointer to a bool variable, and on return from this function that variable is set *false* if the first number did not exceed the limit of digits given by numDigitsFN, or *true* if it did exceed that. If numDigitsFN=0 the variable will always be *false*.

The function returns the value of `S`, which allows a call to the function to be used as an argument to a function, such as for a printf %s-specifier's value as in the example where monitor.printf() uses a "%s" specifier and its value is then provided by calling msToString().

## Example of HH:MM or MM:SS

As an example of using the *hours*, *minutes*, and *seconds* arguments, if you wanted to only show hours and minutes, you would use a call like this, with *seconds=false*:

```
  monitor.printf("Elapsed time in HH:MM is %s\n", msToString(MS, S, n, true, true, false));
```

Or, if you wanted to only show minutes and seconds, you would use a call like this, with *hours=false*:

```
  monitor.printf("Elapsed time in MM:SS is %s\n", msToString(MS, S, n, false, true, true));
```

It makes no sense to call for HH:SS form, so if *hours=seconds=true* and *minutes=false*, this is treated the same as if *minutes* were also true.

You can also set just one of *hours*, *minutes*, and *seconds* true and the other two false, to show only the number of hours, or minutes, or seconds, as a single integer value. For example:

```
  monitor.printf("Elapsed time in minutes is %s\n", msToString(MS, S, n, false, true, false));
```

## Example where first number is a fixed length

Often you want to force the first number of the result to be a fixed length, usually 2 characters, since clock time is usually shown using two digits. This is done by setting *numDigitsFN* to the number of digits desired for the first number. For example:

```
  monitor.printf("Elapsed time in HH:MM:SS is %s\n", msToString(MS, S, n, true, true, true, 2));
```

If the first number has fewer digits, leading 0's are inserted to make it have exactly *numDigitsFN* digits. For example, if MS equated to "1:45" in the previous example, it would instead print "01:45".

Setting numDigitsFN to a number other than 0 also has the effect of forcing digits to be replaced with X's when the first number has *more than numDigitsFN digits*. For example, if MS equated to "187:45" in the previous example, it would instead print "XX:XX".

## Including a decimal fraction in the result

Sometimes you may want to have a resulting string that includes a decimal point and fractional value. This is done by setting *digitsAfterDP* to the number of digits desired after the decimal point. The interpretation of the fraction as fractional hours, fractional minutes, or fractional seconds depends on what the last number before the decimal point is. For example:

```
  monitor.printf("Elapsed time in HH:MM.MMM is %s\n", msToString(MS, S, n, true, true, false, 2, 3));
```

In that example the last number before the decimal point is *minutes*, so the fraction part represents fractional minutes.

Note that rounding *is not done* on the final digit.

The decimal point character, ".", is currently fixed, it cannot be changed to a different character.

# Using false for hours, minutes, and seconds

You can also set all three of *hours*, *minutes*, and *seconds* to false. This causes conversion of MS to an integer string, ignoring *digitsAfterDP* but honoring *numDigitsFN* (which can be used to insert leading 0's to pad the result to a specific length and replace digits with 'X's if there are more than that many digits). It is not expected that the user will use this, but you could. It is used internally by msToString() in recursive calls to itself to convert each of the hours, minutes, and seconds values.

## Contact

If you find a problem, please submit an issue report [here](https://github.com/tedtoal/msToString/issues/new/choose).

You can contact me (the author) at [ted@tedtoal.net](ted@tedtoal.net)
