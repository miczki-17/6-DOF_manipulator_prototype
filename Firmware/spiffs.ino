#if CONTROLLER_TYPE == ESP32

  void initSPIFFS( void ) {
  if ( !SPIFFS.begin( true ) ) {
    
    #ifdef BAUD
      Serial.println( "An error with SPIFFS" );
    #endif
    
    return;
  }
}

#endif
