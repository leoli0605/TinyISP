# cImage

目的是使用 C 語言建立一個跨平台的圖像處理函式庫，並且可以很輕易地使用 `git submodule` 等方式來應用於任何需要的地方。
透過完成此專案，期望學習到：

1. 如何使用 CMake 來建立跨平台的專案
1. 各種常用的圖像格式 / 元數據的讀寫
1. 各種常用的圖像處理演算法

### Documents

- TIFF

  - [TIFF 6.0 Specification](http://partners.adobe.com/public/developer/en/tiff/TIFF6.pdf),(http://www.npes.org/pdf/TIFF-v6.pdf)
  - [TIFF Supplement 1](http://partners.adobe.com/public/developer/en/tiff/TIFFPM6.pdf)
  - [TIFF Supplement 2](http://partners.adobe.com/public/developer/en/tiff/TIFFphotoshop.pdf)
  - [TIFF Supplement 3](http://chriscox.org/TIFFTN3d1.pdf)
  - [TIFF-F/FX Extension (RFC2301)](http://www.ietf.org/rfc/rfc2301.txt)
  - [TIFF/EP Extension (Wikipedia)](https://en.wikipedia.org/wiki/TIFF/EP)
  - [Adobe TIFF Pages](http://partners.adobe.com/public/developer/tiff/index.html)
  - [Unofficial TIFF FAQ](http://www.awaresystems.be/imaging/tiff/faq.html)
  - [CCITT T.4 Compression](https://www.itu.int/rec/T-REC-T.4-198811-S/_page.print)
  - [CCITT T.6 Compression](https://www.itu.int/rec/T-REC-T.6/en)

- DNG

  - [Adobe DNG Pages](https://helpx.adobe.com/photoshop/digital-negative.html)

- Metadata (EXIF)

  - [EXIF 2.3 Specification](http://www.cipa.jp/std/documents/e/DC-008-2012_E.pdf)
  - [EXIF 2.32 Specification](https://www.cipa.jp/std/documents/e/DC-X008-Translation-2019-E.pdf)

- Metadata (XMP)
  - [Adobe XMP Pages](http://www.adobe.com/products/xmp.html)
  - [Adobe XMP Developer Center](http://www.adobe.com/devnet/xmp.html)

### References

- [Magick.NET](https://github.com/dlemstra/Magick.NET)
- [ImageSharp](https://github.com/SixLabors/ImageSharp)

### TODO

- [ ] Formats/TIFF
- [ ] Formats/DNG
- [ ] Metadata/EXIF
- [ ] Metadata/XMP
- [ ] Formats/BMP
- [ ] Formats/JPEG
- [ ] Formats/PNG
- [ ] Formats/SVG
- [ ] Formats/HEIC
- [ ] Formats/WEBP
