rotation = m % 8;  // Muutetaan modulo 8 jotta lisätään peilikuvat

writecommand(TFT_MADCTL);
switch (rotation) {
    case 0: // Portrait
      writedata(TFT_MAD_BGR);
      _width  = _init_width;
      _height = _init_height;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 2;
        rowstart = 1;
      }
#endif    
      break;
    case 1: // Landscape (Portrait + 90)
      writedata(TFT_MAD_MX | TFT_MAD_MV | TFT_MAD_BGR);
      _width  = _init_height;
      _height = _init_width;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 1;
        rowstart = 2;
      }
#endif
      break;
    case 2: // Inverted portrait
      writedata(TFT_MAD_MX | TFT_MAD_MY | TFT_MAD_BGR);
      _width  = _init_width;
      _height = _init_height;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 2;
        rowstart = 1;
      }
#endif
      break;
    case 3: // Inverted landscape
      writedata(TFT_MAD_MV | TFT_MAD_MY | TFT_MAD_BGR);
      _width  = _init_height;
      _height = _init_width;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 1;
        rowstart = 2;
      }
#endif
      break;
    case 4: // Portrait mirrored
      writedata(TFT_MAD_MX | TFT_MAD_BGR);  
      _width  = _init_width;
      _height = _init_height;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 2;
        rowstart = 1;
      }
#endif
      break;
    case 5: // Landscape mirrored
      writedata(TFT_MAD_MV | TFT_MAD_BGR);  
      _width  = _init_height;
      _height = _init_width;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 1;
        rowstart = 2;
      }
#endif
      break;
    case 6: // Inverted portrait mirrored
      writedata(TFT_MAD_MY | TFT_MAD_BGR);   peilaus
      _width  = _init_width;
      _height = _init_height;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 2;
        rowstart = 1;
      }
#endif
      break;
    case 7: // Inverted landscape mirrored
      writedata(TFT_MAD_MX | TFT_MAD_MV | TFT_MAD_MY | TFT_MAD_BGR);  
      _width  = _init_height;
      _height = _init_width;
#ifdef CGRAM_OFFSET
      if (_init_width == 128) {
        colstart = 1;
        rowstart = 2;
      }
#endif
      break;
}
