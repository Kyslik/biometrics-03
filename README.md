# biometrics-03

Biometrics assignment 03 2016 SS.

---

To get data into one folder (from iris.zip) use BASH

```
cd iris
find . -iname '*.bmp' -exec mv {} . \;
rm -R -- */
```