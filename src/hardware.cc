#include "ruby.h"
#include "ofMain.h"
#include "zajal.h"

/* global hardware module */
VALUE zj_mHardware;

VALUE zj_cArduino;
VALUE zj_cSerial;

VALUE zj_enumerate_serial_devices(bool arduino_only=false) {
  ofSerial* ser = new ofSerial();
  vector<ofSerialDeviceInfo> devices = ser->getDeviceList();
  
  VALUE devices_ary = rb_ary_new();
  for(vector<ofSerialDeviceInfo>::iterator dev = devices.begin(); dev != devices.end(); ++dev) {
    if(arduino_only && ((strstr(dev->getDeviceName().c_str(), "usbserial") == NULL) && (strstr(dev->getDeviceName().c_str(), "usbmodem") == NULL)) )
      continue;
    
    rb_ary_push(devices_ary, rb_str_new2(dev->getDevicePath().c_str()));
  }
  
  delete ser;
  return devices_ary;
}

VALUE zj_arduino_devices(VALUE klass) {
  return zj_enumerate_serial_devices(true);
}

void zj_arduino_dealloc(void* arduino) {
  ((ofArduino*)arduino)->disconnect();
  delete (ofArduino*)arduino;
}

VALUE zj_arduino_new(int argc, VALUE* argv, VALUE klass) {
  VALUE device = Qnil, baud = Qnil;
  VALUE connect = Qtrue;
  bool hash_given = (argc > 0 && TYPE(argv[argc-1]) == T_HASH);
  

  /* scan for normal args, ignore hash if given */
  VALUE device_baud;
  rb_scan_args(hash_given ? argc-1 : argc, argv, "02", &device_baud, &baud);

  if(!NIL_P(device_baud)) {
    if(TYPE(device_baud) == T_STRING) {
      device = device_baud;

    } else {
      baud = device_baud;

    }
  }
  

  /* if last arg is options hash, extract local variables */
  if(hash_given) {
    HASH_EXTRACT(argv[argc-1], device);
    HASH_EXTRACT(argv[argc-1], baud);
    HASH_EXTRACT(argv[argc-1], connect);
  }

  if(NIL_P(baud)) baud = INT2FIX(57600);

  if(NIL_P(device)) {
    // no device specified, try and get first arduino
    VALUE arduinos_ary = zj_enumerate_serial_devices(true);
    if(RARRAY_LEN(arduinos_ary) > 0) {
      device = RARRAY_PTR(arduinos_ary)[0];

    } else {
      // no arduino, raise an error
      rb_raise(rb_eRuntimeError, "No Arduinos found on this computer!");

    }
  }
  
  VALUE arduino = rb_hash_aref(INTERNAL_GET(zj_mHardware, arduino_hash), device);
  
  
  if(NIL_P(arduino)) {
    /* arduino device never used before, create it, cache it */
    ofArduino* arduino_ptr = new ofArduino();
  
    arduino = Data_Wrap_Struct(klass, 0, zj_arduino_dealloc, arduino_ptr);

    rb_iv_set(arduino, "@device", device);
    rb_iv_set(arduino, "@baud", baud);
    rb_iv_set(arduino, "@digital_pin_names", rb_hash_new());
    rb_iv_set(arduino, "@analog_pin_names", rb_hash_new());
    rb_iv_set(arduino, "@setup_proc", Qnil);

    /* TODO remove me */
    rb_iv_set(arduino, "@did_setup", Qfalse);
    
    /* connect right away unless user set connect: false hash key */
    if(RTEST(connect)) rb_funcall(arduino, rb_intern("connect"), 0);

    rb_hash_aset(INTERNAL_GET(zj_mHardware, arduino_hash), device, arduino);
  }
  
  return arduino;
}

VALUE zj_arduino_initialize(int argc, VALUE* argv, VALUE self) {
  
}

/* 
 * Connect to the Arduino
 */
VALUE zj_arduino_connect(VALUE self) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);
  
  VALUE device = rb_iv_get(self, "@device");
  VALUE baud = rb_iv_get(self, "@baud");
  
  if( !arduino_ptr->connect(RSTRING_PTR(device), FIX2INT(baud)) )
    rb_raise(rb_eRuntimeError, "Could not connect to Arduino on port %s", RSTRING_PTR(device));
  
  return Qnil;
}

/* 
 * Disconnect from the Arduino
 * 
 * @todo This should be managed internally on exit
 */
VALUE zj_arduino_disconnect(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  arduino_ptr->disconnect();
  
  return Qnil;
}

/* 
 * Update the Arduino
 */
VALUE zj_arduino_update(VALUE self) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);
  if(!arduino_ptr->isArduinoReady()) return Qnil;

  arduino_ptr->update();
  
  return Qnil;
}

/* 
 * Is the Arduino initialized?
 * 
 * @todo Whats the difference between this and #ready? ?
 */
VALUE zj_arduino_initialized_p(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  return arduino_ptr->isInitialized() ? Qtrue : Qfalse;
}

/* 
 * Is the Arduino ready?
 * 
 * @return [Boolean]
 */
VALUE zj_arduino_ready_p(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);
  
  return arduino_ptr->isArduinoReady() ? Qtrue : Qfalse;
}

/* 
 * Get firmware name
 */
VALUE zj_arduino_firmware(VALUE self) {
  ofArduino* arduino_ptr;
  Data_Get_Struct(self, ofArduino, arduino_ptr);

  return rb_str_new2(arduino_ptr->getFirmwareName().c_str());
}

// VALUE zj_arduino_digital(VALUE self, VALUE pin, VALUE val) {
//   INIT_DATA_PTR(ofArduino, arduino_ptr);
//   
//   arduino_ptr->sendDigital(NUM2INT(pin), NUM2INT(val));
//   
//   return Qnil;
// }

VALUE zj_arduino_pwm(VALUE self, VALUE pin, VALUE val) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);
  
  arduino_ptr->sendPwm(NUM2INT(pin), NUM2INT(val));
  
  return Qnil;
}

VALUE zj_arduino_servo(VALUE self, VALUE pin, VALUE val) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);
  
  arduino_ptr->sendServo(NUM2INT(pin), NUM2INT(val));
  
  return Qnil;
}

VALUE zj_arduino_set_pin_mode(VALUE self, VALUE pinrb, VALUE mode) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);

  ID modeid = SYM2ID(mode);
  int pin = FIX2INT(pinrb);
  
  if(modeid == rb_intern("input")) {
    if((pin>=2 && pin<=13) || (pin>=16 && pin<=21)) {
      arduino_ptr->sendDigitalPinMode(pin, ARD_INPUT);
    } else {
      rb_raise(rb_eArgError, "Can't set pin %d mode to input! Only pins 2-13, 16-21 supported.", pin);
    }
    
  } else if(modeid == rb_intern("output")) {
    if((pin>=2 && pin<=13) || (pin>=16 && pin<=21)) {
      arduino_ptr->sendDigitalPinMode(pin, ARD_OUTPUT);
    } else {
      rb_raise(rb_eArgError, "Can't set pin %d mode to output! Only pins 2-13, 16-21 supported.", pin);
    }
    
  } else if(modeid == rb_intern("pwm")) {
    if(pin==3 || pin==5 || pin==6 || pin==8 || pin==10 || pin==11) {
      arduino_ptr->sendDigitalPinMode(pin, ARD_PWM);
    } else {
      rb_raise(rb_eArgError, "Can't set pin %d mode to pwm! Only pins 3, 5, 6, 9, 10 and 11 supported.", pin);
    }
    
  } else if(modeid == rb_intern("servo")) {
    if(pin==9 || pin==10) {
      arduino_ptr->sendServoAttach(pin);
    } else {
      rb_raise(rb_eArgError, "Can't set pin %d mode to servo! Only pins 9 and 10 supported.", pin);
    }
    
  } else {
    rb_raise(rb_eArgError, "Unexpected pin mode!");
    
  }
  
  return Qnil;
}

VALUE zj_arduino_get_pin_mode(VALUE self, VALUE pinrb) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);
  
  int pin = FIX2INT(pinrb);
  int pin_mode = arduino_ptr->getDigitalPinMode(pin);
  
  switch(pin_mode) {
    case ARD_INPUT: return SYM("input"); break;
    case ARD_OUTPUT: return SYM("output"); break;
    case ARD_PWM: return SYM("pwm"); break;
    case ARD_SERVO: return SYM("servo"); break;
    case ARD_ANALOG: return SYM("analog"); break;
    default: rb_raise(rb_eRuntimeError, "Unknown pin mode %d on pin %d", pin_mode, pin);
  }
  
  return Qnil;
}

VALUE zj_arduino_setup_digital(int argc, VALUE* argv, VALUE self) {
  VALUE pin, mode, name;
  rb_scan_args(argc, argv, "21", &pin, &mode, &name);
  
  if(!NIL_P(name)) rb_hash_aset(rb_iv_get(self, "@digital_pin_names"), name, pin);
  
  zj_arduino_set_pin_mode(self, pin, mode);
  
  return Qnil;
}

VALUE zj_arduino_send_digital_value(VALUE self, VALUE pin, VALUE value) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);

  int cpin = INT2FIX(pin);
  int cvalue = INT2FIX(value);
  
  arduino_ptr->sendDigitalPinMode(cpin, ARD_OUTPUT);

  switch(arduino_ptr->getDigitalPinMode(cpin)) {
    case ARD_INPUT:
    case ARD_OUTPUT:
      arduino_ptr->sendDigital(cpin, cvalue);
      break;
      
    case ARD_PWM:
      arduino_ptr->sendPwm(cpin, cvalue);
      break;
      
    case ARD_SERVO:
      arduino_ptr->sendServo(cpin, cvalue);
      break;
  }
  
  return Qnil;
}

VALUE zj_arduino_read_digital_pin(VALUE self, VALUE pin) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);

  int cpin = FIX2INT(pin);

  // printf("Reading from pin %d, mode %d", cpin, arduino_ptr->getDigitalPinMode(cpin));

  arduino_ptr->sendDigitalPinMode(cpin, ARD_INPUT);
  switch(arduino_ptr->getDigitalPinMode(cpin)) {
    case ARD_OUTPUT:
    case ARD_INPUT:
      return arduino_ptr->getDigital(cpin) == 1 ? Qtrue : Qfalse;
      break;
    
    case ARD_PWM:
      return INT2FIX(arduino_ptr->getPwm(cpin));
      break;
    
    case ARD_SERVO:
      return INT2FIX(arduino_ptr->getServo(cpin));
      break;
  }
  
  return Qnil;
}


VALUE zj_arduino_digital(int argc, VALUE* argv, VALUE self) {
  VALUE pin, value;
  rb_scan_args(argc, argv, "11", &pin, &value);
  
  switch(argc) {
    /* called with one argument, return pin mode */
    case 1: return zj_arduino_read_digital_pin(self, FIX2INT(pin)); break;
    
    /* called with two arguments, send value to pin */
    case 2: return zj_arduino_send_digital_value(self, FIX2INT(pin), NUM2INT(value));
  }
  
  return Qnil;
}

VALUE zj_arduino_setup_analog(int argc, VALUE* argv, VALUE self) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);

  VALUE pin, mode, pin_mode, name;
  rb_scan_args(argc, argv, "11", &pin_mode, &name);
  
  if(TYPE(pin_mode) == T_SYMBOL) {
    pin = Qnil;
    mode = pin_mode;
  } else {
    pin = pin_mode;
    mode = Qnil;
  }
  
  if(!NIL_P(mode)) {
    ID modeid = SYM2ID(mode);
    
    if(modeid == rb_intern("all_digital")) {
      for(int i = 0; i < 6; i++) {
        arduino_ptr->sendAnalogPinReporting(i, ARD_OFF);
        arduino_ptr->sendDigitalPinMode(16+i, ARD_INPUT);
      }
      
    } else if(modeid == rb_intern("all_analog")) {
      for(int i = 0; i < 6; i++) {
        arduino_ptr->sendAnalogPinReporting(i, ARD_ON);
      }
      
    } else {
      rb_raise(rb_eArgError, "Unrecognized analog pin mode!");
      
    }
    
  } else if(!NIL_P(pin) && !NIL_P(name)) {
    rb_hash_aset(rb_iv_get(self, "@analog_pin_names"), name, pin);
    
  }
  
  
  return Qnil;
}

VALUE zj_arduino_analog(VALUE self, VALUE pin) {
  INIT_DATA_PTR(ofArduino, arduino_ptr);
  
  return INT2FIX(arduino_ptr->getAnalog(pin));
}

VALUE zj_arduino_setup(VALUE self) {
  /* store setup block to be invoked when arduino is ready */
  if(rb_block_given_p()) rb_iv_set(self, "@setup_proc", rb_block_proc());

  return Qnil;
}

VALUE zj_serial_devices(VALUE klass) {
  return zj_enumerate_serial_devices();
}

void zj_serial_dealloc(void* serial) {
  ((ofSerial*)serial)->close();
  delete (ofSerial*)serial;
}

VALUE zj_serial_new(int argc, VALUE* argv, VALUE klass) {
  ofSerial* serial_ptr = new ofSerial();
  
  VALUE serial = Data_Wrap_Struct(klass, 0, zj_serial_dealloc, serial_ptr);
  rb_obj_call_init(serial, argc, argv);
  
  return serial;
}

VALUE zj_serial_initialize(int argc, VALUE* argv, VALUE self) {
  VALUE device = Qnil, baud = Qnil;
  VALUE connect = Qtrue;
  bool hash_given = (argc > 0 && TYPE(argv[argc-1]) == T_HASH);
  
  /* scan for normal args, ignore hash if given */
  VALUE device_baud;
  rb_scan_args(hash_given ? argc-1 : argc, argv, "02", &device_baud, &baud);
  
  if(!NIL_P(device_baud)) {
    if(TYPE(device_baud) == T_STRING) {
      device = device_baud;
      
    } else {
      baud = device_baud;
      
    }
  }
  
  /* if last arg is options hash, extract local variables */
  if(hash_given) {
    HASH_EXTRACT(argv[argc-1], device);
    HASH_EXTRACT(argv[argc-1], baud);
    HASH_EXTRACT(argv[argc-1], connect);
  }
  
  if(NIL_P(baud)) {
    baud = INT2FIX(9600);
  }
  
  if(NIL_P(device)) {
    // no device specified, try and get first arduino
    VALUE arduinos_ary = zj_enumerate_serial_devices(true);
    if(RARRAY_LEN(arduinos_ary) > 0) {
      device = RARRAY_PTR(arduinos_ary)[0];
      
    } else {
      // no arduino, just get first serial device
      VALUE serial_ary = zj_enumerate_serial_devices(false);
      if(RARRAY_LEN(serial_ary) > 0) {
        device = RARRAY_PTR(serial_ary)[0];
        
      } else {
        // no serial device found at all, error out
        rb_raise(rb_eRuntimeError, "No serial devices found on this computer!");
        
      }
    }
    
  }
  
  rb_iv_set(self, "@baud", baud);
  rb_iv_set(self, "@device", device);
  
  /* connect right away unless user set connect: false hash key */
  if(RTEST(connect)) rb_funcall(self, rb_intern("connect"), 0);
  
  return self;
}

/* 
 * Connect to the serial port
 * 
 * Uses the baud and device information provided to the constructor
 */
VALUE zj_serial_connect(VALUE self) {
  INIT_DATA_PTR(ofSerial, serial_ptr);
  
  VALUE device = rb_iv_get(self, "@device");
  VALUE baud = rb_iv_get(self, "@baud");
  bool connected;
  
  if(NIL_P(device)) {
    connected = serial_ptr->setup();
  } else {
    connected = serial_ptr->setup(RSTRING_PTR(device), FIX2INT(baud));
  }
  
  if(!connected) {
    rb_raise(rb_eRuntimeError, "Could not connect to serial port %s@%d", RSTRING_PTR(device), FIX2INT(baud));
  }
  
  return Qnil;
}

/* 
 * Disconnect from the serial port
 * 
 * You generally do not need to call this method, as Zajal manages port
 * connectivity automatically
 */
VALUE zj_serial_disconnect(VALUE self) {
  INIT_DATA_PTR(ofSerial, serial_ptr);
  
  serial_ptr->close();
  
  return Qnil;
}

/* 
 * Get the number of bytes available from the serial port
 * 
 * @return [Fixnum] The number of bytes available from the serial port
 */
VALUE zj_serial_available(VALUE self) {
  INIT_DATA_PTR(ofSerial, serial_ptr);
  
  return INT2FIX(serial_ptr->available());
}

/* 
 * @return [true] There are bytes to read on the serial port
 * @return [false] There are no bytes to read on the serial port
 */
VALUE zj_serial_available_p(VALUE self) {
  INIT_DATA_PTR(ofSerial, serial_ptr);
  
  return serial_ptr->available() > 0 ? Qtrue : Qfalse;
}

/* 
 * Read data from the serial port
 * 
 * @overload read
 *   Reads all the data available
 *   @return [String] The data that was read
 * 
 * @overload read length
 *   Reads at most +length+ bytes of the available data
 *   @param [Fixnum] length The number of bytes to read from the serial port
 *   @return [String] The data that was read
 */
VALUE zj_serial_read(int argc, VALUE* argv, VALUE self) {
  INIT_DATA_PTR(ofSerial, serial_ptr);
  
  VALUE length;
  rb_scan_args(argc, argv, "01", &length);
  int clength = NIL_P(length) ? serial_ptr->available() : FIX2INT(length);
  
  unsigned char* buffer = (unsigned char*)calloc(sizeof(unsigned char), clength);
  serial_ptr->readBytes(buffer, clength);
  
  VALUE bytes_read = rb_str_new((const char*)buffer, strlen((const char*)buffer));
  free(buffer);
  
  return bytes_read;
}

/* 
 * Write data to the serial port
 * 
 * @param [#to_s] data The data to write to the serial port
 * @return [Fixnum] The number of bytes written
 */
VALUE zj_serial_write(VALUE self, VALUE data) {
  INIT_DATA_PTR(ofSerial, serial_ptr);
  
  VALUE data_str = rb_funcall(data, rb_intern("to_s"), 0);
  char* data_ptr = RSTRING_PTR(data_str);
  int length = RSTRING_LEN(data_str);
  
  int bytes_written = serial_ptr->writeBytes((unsigned char*)data_ptr, length);
  
  return INT2FIX(bytes_written);
}

void Init_Hardware() {
  zj_mHardware = rb_define_module_under(zj_mZajal, "Hardware");
  rb_define_module_under(zj_mHardware, "Internals");
  /* TODO these should be part of their respective classes, e.g. Arduino.cache */
  INTERNAL_SET(zj_mHardware, arduino_hash, rb_hash_new());
  INTERNAL_SET(zj_mHardware, arduino_ary, rb_ary_new());
  
  INTERNAL_SET(zj_mHardware, serial_hash, rb_hash_new());
  INTERNAL_SET(zj_mHardware, serial_ary, rb_ary_new());
  
  zj_cArduino = rb_define_class_under(zj_mHardware, "Arduino", rb_cObject);
  rb_define_singleton_method(zj_cArduino, "new", RUBY_METHOD_FUNC(zj_arduino_new), -1);
  rb_define_singleton_method(zj_cArduino, "devices", RUBY_METHOD_FUNC(zj_arduino_devices), 0);
  rb_define_method(zj_cArduino, "initialize", RUBY_METHOD_FUNC(zj_arduino_initialize), -1);
  rb_define_method(zj_cArduino, "connect", RUBY_METHOD_FUNC(zj_arduino_connect), 0);
  rb_define_method(zj_cArduino, "disconnect", RUBY_METHOD_FUNC(zj_arduino_disconnect), 0);
  rb_define_method(zj_cArduino, "update", RUBY_METHOD_FUNC(zj_arduino_update), 0);
  rb_define_method(zj_cArduino, "initialized?", RUBY_METHOD_FUNC(zj_arduino_initialized_p), 0);
  rb_define_method(zj_cArduino, "ready?", RUBY_METHOD_FUNC(zj_arduino_ready_p), 0);
  rb_define_method(zj_cArduino, "firmware", RUBY_METHOD_FUNC(zj_arduino_firmware), 0);
  
  rb_define_method(zj_cArduino, "setup", RUBY_METHOD_FUNC(zj_arduino_setup), 0);
  
  rb_define_method(zj_cArduino, "setup_digital", RUBY_METHOD_FUNC(zj_arduino_setup_digital), -1);
  rb_define_method(zj_cArduino, "read_digital", RUBY_METHOD_FUNC(zj_arduino_read_digital_pin), 1);
  rb_define_method(zj_cArduino, "write_digital", RUBY_METHOD_FUNC(zj_arduino_send_digital_value), 2);

  rb_define_method(zj_cArduino, "setup_analog", RUBY_METHOD_FUNC(zj_arduino_setup_analog), -1);
  rb_define_method(zj_cArduino, "read_analog", RUBY_METHOD_FUNC(zj_arduino_analog), 1);
 
  rb_define_method(zj_cArduino, "set_pin_mode", RUBY_METHOD_FUNC(zj_arduino_set_pin_mode), 2);
  
  // rb_define_method(zj_cArduino, "more_digital_pins", RUBY_METHOD_FUNC(zj_arduino_pin_mode), -1);
  // rb_define_method(zj_cArduino, "pin_mode", RUBY_METHOD_FUNC(zj_arduino_pin_mode), -1);
  // rb_define_method(zj_cArduino, "digital", RUBY_METHOD_FUNC(zj_arduino_digital), 2);
  // rb_define_method(zj_cArduino, "pwm", RUBY_METHOD_FUNC(zj_arduino_pwm), 2);
  // rb_define_method(zj_cArduino, "servo", RUBY_METHOD_FUNC(zj_arduino_servo), 2);
  
  zj_cSerial = rb_define_class_under(zj_mHardware, "Serial", rb_cObject);
  rb_define_singleton_method(zj_cSerial, "devices", RUBY_METHOD_FUNC(zj_serial_devices), 0);
  rb_define_singleton_method(zj_cSerial, "new", RUBY_METHOD_FUNC(zj_serial_new), -1);
  rb_define_method(zj_cSerial, "initialize", RUBY_METHOD_FUNC(zj_serial_initialize), -1);
  rb_define_method(zj_cSerial, "connect", RUBY_METHOD_FUNC(zj_serial_connect), 0);
  rb_define_method(zj_cSerial, "disconnect", RUBY_METHOD_FUNC(zj_serial_disconnect), 0);
  
  rb_define_method(zj_cSerial, "available?", RUBY_METHOD_FUNC(zj_serial_available_p), 0);
  rb_define_method(zj_cSerial, "available", RUBY_METHOD_FUNC(zj_serial_available), 0);
  
  rb_define_method(zj_cSerial, "read", RUBY_METHOD_FUNC(zj_serial_read), -1);
  rb_define_method(zj_cSerial, "write", RUBY_METHOD_FUNC(zj_serial_write), 1);
  // rb_define_method(zj_cSerial, "flush", RUBY_METHOD_FUNC(zj_serial_flush), 0);
}